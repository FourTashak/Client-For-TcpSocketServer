#pragma once
#include "Login.h"

#define Buy 0 
#define Sell 1

namespace Stockmarketclient {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Interface
	/// </summary>
	std::string logged_in_username;
	Customer Cus;
	
	public ref class Interface : public System::Windows::Forms::Form
	{
	public:
		Socket^ Realsock;
		Interface(Socket^ Sock)
		{
			InitializeComponent();
			Cus.Customershares.resize(1024);
			Market.resize(1024);
			Realsock = Sock;
			ReceiveCusInfo(Sock,Cus);
			Stock_ComboBox->Items->AddRange((array<System::Object^>^)stocklist());
			LoginWorker->RunWorkerAsync();
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Interface()
		{
			exit(0);
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ComboBox^ Buy_Sell;
	private: System::Windows::Forms::ComboBox^ Stock_ComboBox;
	private: System::Windows::Forms::Button^ Trade_button;
	private: System::Windows::Forms::Label^ Balance;
	private: System::Windows::Forms::RichTextBox^ Account_stock_List;
	private: System::ComponentModel::BackgroundWorker^ LoginWorker;
	private: System::Windows::Forms::TextBox^ quantity_txtbox;
	private: System::Windows::Forms::RichTextBox^ Market_Stock_List;
	private: System::Windows::Forms::Button^ Refresh_Btn;
	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::IContainer^ components;


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->Buy_Sell = (gcnew System::Windows::Forms::ComboBox());
			this->Stock_ComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->Trade_button = (gcnew System::Windows::Forms::Button());
			this->Balance = (gcnew System::Windows::Forms::Label());
			this->Account_stock_List = (gcnew System::Windows::Forms::RichTextBox());
			this->LoginWorker = (gcnew System::ComponentModel::BackgroundWorker());
			this->quantity_txtbox = (gcnew System::Windows::Forms::TextBox());
			this->Market_Stock_List = (gcnew System::Windows::Forms::RichTextBox());
			this->Refresh_Btn = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// Buy_Sell
			// 
			this->Buy_Sell->FormattingEnabled = true;
			this->Buy_Sell->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Buy", L"Sell" });
			this->Buy_Sell->Location = System::Drawing::Point(309, 12);
			this->Buy_Sell->Name = L"Buy_Sell";
			this->Buy_Sell->Size = System::Drawing::Size(93, 21);
			this->Buy_Sell->TabIndex = 2;
			this->Buy_Sell->Text = L"Buy/Sell";
			this->Buy_Sell->SelectedIndexChanged += gcnew System::EventHandler(this, &Interface::comboBox1_SelectedIndexChanged);
			// 
			// Stock_ComboBox
			// 
			this->Stock_ComboBox->FormattingEnabled = true;
			this->Stock_ComboBox->Location = System::Drawing::Point(12, 12);
			this->Stock_ComboBox->Name = L"Stock_ComboBox";
			this->Stock_ComboBox->Size = System::Drawing::Size(96, 21);
			this->Stock_ComboBox->TabIndex = 4;
			this->Stock_ComboBox->Text = L"Stock";
			this->Stock_ComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &Interface::comboBox3_SelectedIndexChanged);
			// 
			// Trade_button
			// 
			this->Trade_button->Location = System::Drawing::Point(12, 172);
			this->Trade_button->Name = L"Trade_button";
			this->Trade_button->Size = System::Drawing::Size(390, 48);
			this->Trade_button->TabIndex = 5;
			this->Trade_button->Text = L"Trade";
			this->Trade_button->UseVisualStyleBackColor = true;
			this->Trade_button->Click += gcnew System::EventHandler(this, &Interface::Trade_button_Click);
			// 
			// Balance
			// 
			this->Balance->AutoSize = true;
			this->Balance->Location = System::Drawing::Point(179, 74);
			this->Balance->Name = L"Balance";
			this->Balance->Size = System::Drawing::Size(46, 13);
			this->Balance->TabIndex = 6;
			this->Balance->Text = L"Balance";
			this->Balance->Click += gcnew System::EventHandler(this, &Interface::Balance_Click);
			// 
			// Account_stock_List
			// 
			this->Account_stock_List->Location = System::Drawing::Point(12, 103);
			this->Account_stock_List->Name = L"Account_stock_List";
			this->Account_stock_List->ReadOnly = true;
			this->Account_stock_List->Size = System::Drawing::Size(183, 63);
			this->Account_stock_List->TabIndex = 7;
			this->Account_stock_List->Text = L"";
			this->Account_stock_List->TextChanged += gcnew System::EventHandler(this, &Interface::richTextBox1_TextChanged);
			// 
			// LoginWorker
			// 
			this->LoginWorker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Interface::LoginWorker_DoWork);
			// 
			// quantity_txtbox
			// 
			this->quantity_txtbox->Location = System::Drawing::Point(12, 39);
			this->quantity_txtbox->Name = L"quantity_txtbox";
			this->quantity_txtbox->Size = System::Drawing::Size(390, 20);
			this->quantity_txtbox->TabIndex = 8;
			this->quantity_txtbox->TextChanged += gcnew System::EventHandler(this, &Interface::quantity_txtbox_TextChanged);
			// 
			// Market_Stock_List
			// 
			this->Market_Stock_List->Location = System::Drawing::Point(220, 103);
			this->Market_Stock_List->Name = L"Market_Stock_List";
			this->Market_Stock_List->ReadOnly = true;
			this->Market_Stock_List->Size = System::Drawing::Size(182, 63);
			this->Market_Stock_List->TabIndex = 9;
			this->Market_Stock_List->Text = L"";
			// 
			// Refresh_Btn
			// 
			this->Refresh_Btn->Location = System::Drawing::Point(173, 4);
			this->Refresh_Btn->Name = L"Refresh_Btn";
			this->Refresh_Btn->Size = System::Drawing::Size(61, 34);
			this->Refresh_Btn->TabIndex = 10;
			this->Refresh_Btn->Text = L"Refresh";
			this->Refresh_Btn->UseVisualStyleBackColor = true;
			this->Refresh_Btn->Click += gcnew System::EventHandler(this, &Interface::Refresh_Btn_Click);
			// 
			// Interface
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(414, 230);
			this->Controls->Add(this->Refresh_Btn);
			this->Controls->Add(this->Market_Stock_List);
			this->Controls->Add(this->quantity_txtbox);
			this->Controls->Add(this->Account_stock_List);
			this->Controls->Add(this->Balance);
			this->Controls->Add(this->Trade_button);
			this->Controls->Add(this->Stock_ComboBox);
			this->Controls->Add(this->Buy_Sell);
			this->Name = L"Interface";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &Interface::MyForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void comboBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
	{

	}
	private: System::Void comboBox3_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
	{

	}
	private: System::Void richTextBox1_TextChanged(System::Object^ sender, System::EventArgs^ e)
	{

	}
	private: System::Void Trade_button_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (Buy_Sell->SelectedIndex == Buy)
		{
			if (Cus.Balance >= getprice(Stock_ComboBox->SelectedItem->ToString(), quantity_txtbox->Text) && CstringToInt(quantity_txtbox->Text) > 0)
			{
				Cus.Balance = BuyStock(quantity_txtbox->Text, Stock_ComboBox->SelectedItem->ToString(), Cus);

				System::String^ Dat = "2";
				Dat += Stock_ComboBox->SelectedItem->ToString() + "$" + quantity_txtbox->Text + "$";
				array<BYTE>^ Buf = Encoding::ASCII->GetBytes(Dat);
				Realsock->Send(Buf);
			}

			else
				MessageBox::Show("Insufficient balance");	
		}
	
		if (Buy_Sell->SelectedIndex == Sell)
		{
			if (DoesCustomerHaveShare(Stock_ComboBox->SelectedItem,quantity_txtbox->Text,Cus))
			{
				Cus.Balance = SellStock(quantity_txtbox->Text, Stock_ComboBox->SelectedItem->ToString(),Cus);
				System::String^ Dat = "3";
				Dat += Stock_ComboBox->SelectedItem->ToString() + "$" + quantity_txtbox->Text + "$";
				array<BYTE>^ Buf = Encoding::ASCII->GetBytes(Dat);
				Realsock->Send(Buf);
			}
			else
				MessageBox::Show("You do not have enough shares");
		}
	}
	private: System::Void Balance_Click(System::Object^ sender, System::EventArgs^ e)
	{

	}
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e)
	{

	}

	private: void Setbalance() //sets the balance seen in the UI according to the customers balance
	{
		Balance->Text = "Balance " + Convert::ToString(Cus.Balance);
	}

	private: void CreateMarketList()
	{
		for (int i = 0; i < Market.size(); i++)
		{
			Market_Stock_List->Text += StdStringToCString(Market[i].Name) + " " + intToCString(Market[i].price) + "\n";
		}
	}

	private: void CreateAuthShareList()
	{
		System::String^ Stocks;
		for (int i = 0; i < Cus.Customershares.size(); i++)
		{
			Stocks += StdStringToCString(Cus.Customershares[i].Share_Name) + " " + intToCString(Cus.Customershares[i].Share_Quantity) + "\n";
		}
		Account_stock_List->Text = Stocks;
	}

	private: System::Void LoginWorker_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e)
	{
		if (Market_Stock_List->InvokeRequired)
			this->Invoke(gcnew MethodInvoker(this, &Interface::CreateMarketList));
		else
			CreateMarketList();

		while (true)
		{
			IRec(Realsock);
			if (Account_stock_List->InvokeRequired)
				this->Invoke(gcnew MethodInvoker(this, &Interface::CreateAuthShareList));
			else
				CreateAuthShareList();

			if (Balance->InvokeRequired)
				this->Invoke(gcnew MethodInvoker(this, &Interface::Setbalance));
			else
				Setbalance();

			Sleep(100);
		}
	}

	private: System::Void quantity_txtbox_TextChanged(System::Object^ sender, System::EventArgs ^e) 
	{
		
	}
	private: System::Void quantity_textbox_Keypress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e)
	{
		//only accepts numbers
		if (!(e->KeyChar == 8 || (e->KeyChar >= 48 && e->KeyChar <= 57)))
			e->Handled = true;
	}
	private: System::Void Refresh_Btn_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		//sends '4' to the server meaning it is requesting the latest stock prices
		array<Byte>^ req = Encoding::ASCII->GetBytes("4");
		Realsock->Send(req);
	}
};
};