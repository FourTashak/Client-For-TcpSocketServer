#pragma once
#include "Functions.h"
#include "Interface.h"

namespace Stockmarketclient {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Login
	/// </summary>
	
	public ref class Login : public System::Windows::Forms::Form
	{
	public:
		Socket^ clientsocket;
		Login()
		{
			clientsocket = gcnew Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
			InitializeComponent();
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Login()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ Login_button;
	private: System::Windows::Forms::TextBox^ Username_txtbox;
	private: System::Windows::Forms::TextBox^ password_txtbox;
	private: System::Windows::Forms::Label^ username_lbl;
	private: System::Windows::Forms::Label^ password_lbl;

	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->Login_button = (gcnew System::Windows::Forms::Button());
			this->Username_txtbox = (gcnew System::Windows::Forms::TextBox());
			this->password_txtbox = (gcnew System::Windows::Forms::TextBox());
			this->username_lbl = (gcnew System::Windows::Forms::Label());
			this->password_lbl = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// Login_button
			// 
			this->Login_button->Location = System::Drawing::Point(92, 170);
			this->Login_button->Name = L"Login_button";
			this->Login_button->Size = System::Drawing::Size(103, 41);
			this->Login_button->TabIndex = 0;
			this->Login_button->Text = L"Login";
			this->Login_button->UseVisualStyleBackColor = true;
			this->Login_button->Click += gcnew System::EventHandler(this, &Login::Login_button_Click);
			// 
			// Username_txtbox
			// 
			this->Username_txtbox->Location = System::Drawing::Point(12, 59);
			this->Username_txtbox->Name = L"Username_txtbox";
			this->Username_txtbox->Size = System::Drawing::Size(260, 20);
			this->Username_txtbox->TabIndex = 1;
			// 
			// password_txtbox
			// 
			this->password_txtbox->Location = System::Drawing::Point(12, 121);
			this->password_txtbox->Name = L"password_txtbox";
			this->password_txtbox->Size = System::Drawing::Size(260, 20);
			this->password_txtbox->TabIndex = 2;
			// 
			// username_lbl
			// 
			this->username_lbl->AutoSize = true;
			this->username_lbl->Location = System::Drawing::Point(12, 43);
			this->username_lbl->Name = L"username_lbl";
			this->username_lbl->Size = System::Drawing::Size(55, 13);
			this->username_lbl->TabIndex = 3;
			this->username_lbl->Text = L"Username";
			// 
			// password_lbl
			// 
			this->password_lbl->AutoSize = true;
			this->password_lbl->Location = System::Drawing::Point(14, 105);
			this->password_lbl->Name = L"password_lbl";
			this->password_lbl->Size = System::Drawing::Size(53, 13);
			this->password_lbl->TabIndex = 4;
			this->password_lbl->Text = L"Password";
			// 
			// Login
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->password_lbl);
			this->Controls->Add(this->username_lbl);
			this->Controls->Add(this->password_txtbox);
			this->Controls->Add(this->Username_txtbox);
			this->Controls->Add(this->Login_button);
			this->Name = L"Login";
			this->Text = L"Login";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Login_button_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		if (AuthLog(clientsocket))
		{
			if (Loggin(clientsocket,Username_txtbox->Text,password_txtbox->Text))
			{
				Interface^ form2 = gcnew Interface(clientsocket);
				form2->Show();
				this->Hide();
			}
			else
			{
				MessageBox::Show("Wrong username or password");
				clientsocket->Close();
			}
		}
		else
		{
			clientsocket->Close();
		}
	}
};
}
