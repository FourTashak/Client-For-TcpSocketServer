#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#include <msclr\marshal_cppstd.h>
#include <vector>
#include <sstream>
#include <iomanip>
#include <random>
#include <Windows.h>

#pragma comment (lib, "Ws2_32.lib")

using namespace System::Net::Sockets;
using namespace System::Net;
using namespace System::Text;
using namespace System;
using namespace msclr::interop;

bool AuthLog(Socket^ clientsocket)
{
    IPAddress^ ipaddress = IPAddress::Parse("192.168.1.10");
    IPEndPoint^ serverendpoint = gcnew IPEndPoint(ipaddress, 12345);


    clientsocket->Connect(serverendpoint);
    if (clientsocket->Connected)
    {
        return true;
    }
    else
    {
        System::Windows::Forms::MessageBox::Show("Error Connecting To Server");
        return false;
    }
}

bool Loggin(Socket^ clientsocket,System::String^ Username, System::String^ Password)
{
    System::String^ Data = "1" + Username + "$" + Password + "$";
    array<Byte>^ LoginString = Encoding::ASCII->GetBytes(Data);
    clientsocket->Send(LoginString);

    array<Byte>^ buffer;
    System::Array::Resize(buffer, 32);
    int recCount = clientsocket->Receive(buffer, sizeof(buffer), System::Net::Sockets::SocketFlags::None);
    if (buffer[0] == (Byte)'1')
    {
        return true;
    }
    else if (buffer[0] == (Byte)'0')
    {
        return false;
    }
}

bool EstablishConnection()
{
    WSADATA wsaData;
    int iresult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iresult != 0)
    {
        return false;
    }
}

struct Stonks
{
    std::string Name;
    float price;

    Stonks()
    {

    }

    Stonks(std::string name, float Price)
    {
        Name = name;
        price = Price;
    }
};

struct Shares
{
    std::string Share_Name;
    int Share_Quantity;
    Shares()
    {

    }
    Shares(std::string Name, int Quantity)
    {
        Share_Name = Name;
        Share_Quantity = Quantity;
    }
};

struct Customer
{
    int id;
    std::string Name;
    std::string password;
    float Balance;

    std::vector<Shares> Customershares;
};

std::vector<Stonks>Market;

template<typename t>System::String^ intToCString(t Integer)
{
    std::string theString = std::to_string(Integer);
    System::String^ bunga = gcnew System::String(theString.c_str());

    return bunga;
}

std::string Cstring_to_String(System::String^ str)
{
    using namespace msclr::interop;
    std::string newStr = marshal_as<std::string>(str);
    return newStr;
}

System::String^ StdStringToCString(std::string Str)
{
    System::String^ str = gcnew System::String(Str.c_str());
    return str;
}

void IRec(Socket^ clientsocket)
{
    array<Socket^>^ readSockets = gcnew array<Socket^>(1);
    {
        System::Array::Clear(readSockets, 0, readSockets->Length);
        readSockets[0] = clientsocket;
        Socket::Select(safe_cast<System::Collections::IList^>(readSockets), nullptr, nullptr, 100000);
        if (clientsocket->Available > 0)
        {
            array<Byte>^ Buffer;
            std::string rec;
            System::Array::Resize(Buffer, 1024);
            int result = clientsocket->Receive(Buffer, Buffer->Length, System::Net::Sockets::SocketFlags::None);
            int pos = 0;
            if (Buffer[0] == (BYTE)'4')
            {
                for (int i = 1; i < result; i++)
                {
                    if (Buffer[i] != (BYTE)'$')
                    {
                        rec += Buffer[i];
                    }
                    else
                    {
                        Market[pos].price = std::stoi(rec);
                        if (pos == (Market.size() - 1))
                            break;
                        pos++;
                        rec.clear();
                    }
                }
            }
            else if (Buffer[0] == (BYTE)'1')
            {
                System::Windows::Forms::MessageBox::Show("Transaction Successful");
            }
            else if (Buffer[0] == (BYTE)'0')
            {
                System::Windows::Forms::MessageBox::Show("Transaction Failed");
            }
        }
    }
}

void ReceiveCusInfo(Socket^ clientsocket, Customer &Cus)
{
    array<Byte>^ buffer;
    System::Array::Resize(buffer, 1024);
    std::string Name;
    int Quantity;
    std::string buf;
    std::string Pbuf;
    float price;
    int received = clientsocket->Receive(buffer, buffer->Length, System::Net::Sockets::SocketFlags::None);
    int Flag = 0;
    int Pos = 0;
    for (int i = 0; i < received; i++)
    {
        if (buffer[i] != (BYTE)'$' && Flag == 0)
        {
            Name += buffer[i];
        }
        else if (buffer[i] != (BYTE)'$' && Flag == 1)
        {
            buf += buffer[i];
        }
        else if (buffer[i] != (BYTE)'$' && Flag == 2)
        {
            Pbuf += buffer[i];
        }
        else
        {
            Flag++;
            if (Flag == 3)
            {
                Cus.Customershares[Pos].Share_Name = Name;
                Market[Pos].Name = Name;
                Market[Pos].price = std::stof(Pbuf);
                Cus.Customershares[Pos].Share_Quantity = std::stoi(buf);
                
                Name.clear();
                buf.clear();
                Pbuf.clear();
                Pos++;
                Flag = 0;
            }
        }
    }
    buf.clear();
    Array::Clear(buffer,0,buffer->Length);
    received = clientsocket->Receive(buffer, buffer->Length, System::Net::Sockets::SocketFlags::None);
    for (int i = 0; i < received; i++)
    {
        if (buffer[i] != (BYTE)'$')
        {
            buf += buffer[i];
        }
    }
    Cus.Balance = std::stof(buf);
    Market.resize(Pos);
    Cus.Customershares.resize(Pos);
}

System::Object^ stocklist()
{
    array<System::Object^>^ StockArray;
    System::Array::Resize(StockArray, Market.size());
    for (int i = 0; i < Market.size(); i++)
    {
        StockArray[i] = StdStringToCString(Market[i].Name);
    }
    return StockArray;
}

int CstringToInt(System::String^ quantity)
{
    if (quantity != "")
    {
        int newquant = int::Parse(quantity);
        return newquant;
    }
    else
    {
        return 0;
    }
}

float getprice(System::String^ Name, System::String^ Quantity)
{
    if (Quantity != "")
    {
        int quant = int::Parse(Quantity);
        std::string realname = Cstring_to_String(Name);
        for (int i = 0; i < Market.size(); i++)
        {
            if (Market[i].Name == realname)
            {
                return (Market[i].price * quant);
            }
        }
    }
}

bool DoesCustomerHaveShare(System::Object^ Share, System::String^ Quantity, Customer& Auth)
{
    if (Quantity != "")
    {
        std::string Realshare = Cstring_to_String(Share->ToString());
        int realQuant = int::Parse(Quantity);
        for (int i = 0; i < Auth.Customershares.size(); i++)
        {
            if (Auth.Customershares[i].Share_Name == Realshare && Auth.Customershares[i].Share_Quantity >= realQuant && realQuant > 0)
                return true;
        }
    }
    return false;
}

float SellStock(System::String^ Quantity, System::String^ StockName, Customer& Auth)
{
    for (int i = 0; i < Market.size(); i++)
    {
        if (Market[i].Name == Cstring_to_String(StockName))
        {
            for (int j = 0; j < Auth.Customershares.size(); j++)
            {
                if (Auth.Customershares[j].Share_Name == Market[i].Name)
                {
                    int quant = int::Parse(Quantity);
                    Auth.Customershares[j].Share_Quantity -= quant;
                    if (Auth.Customershares[j].Share_Quantity == 0)
                    {
                        Auth.Customershares.erase(Auth.Customershares.begin() + j);
                    }
                    return Auth.Balance += (Market[i].price * quant);
                }
            }
        }
    }
}

float BuyStock(System::String^ Quantity, System::String^ StockName, Customer& Auth)
{
    for (int i = 0; i < Market.size(); i++)
    {
        if (Market[i].Name == Cstring_to_String(StockName))
        {
            for (int j = 0; j < Auth.Customershares.size(); j++)
            {
                if (Auth.Customershares[j].Share_Name == Market[i].Name)
                {
                    int Qant = int::Parse(Quantity);
                    Auth.Customershares[j].Share_Quantity += Qant;
                    return Auth.Balance -= (Market[i].price * Qant);
                }
            }
            int Qant = int::Parse(Quantity);
            Auth.Customershares.push_back(Shares(Cstring_to_String(StockName), Qant));
            return Auth.Balance -= (Market[i].price * Qant);
        }
    }
}

void Login_client(System::String^ Username, System::String^ Password)
{
    using namespace System::IO;
    using namespace System::Net;
    using namespace System::Text;
    using namespace System::Net::Sockets;


    TcpClient^ tcpclnt = gcnew TcpClient();
    tcpclnt->Connect("192.168.1.10", 12345);

    Stream^ stm = tcpclnt->GetStream();
    Sleep(100);
    ASCIIEncoding^ asen = gcnew ASCIIEncoding();
        
    array<System::Byte>^ ba = asen->GetBytes(Username);
    array<System::Byte>^ password = asen->GetBytes(Password);

    stm->Write(ba, 0, ba->Length); //write to server
    stm->Write(password, 0, password->Length);

    array<System::Byte>^ bb;
    System::Array::Resize(bb, 100); 
    int k = stm->Read(bb, 0, 100); //read from server

    System::String^ IP = Encoding::ASCII->GetString(bb,0,k);
    tcpclnt->Close();
}