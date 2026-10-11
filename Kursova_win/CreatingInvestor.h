#pragma once
#include "Investor.h"
#include "Market.h"
namespace Kursovawin {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for CreatingInvestor
	/// </summary>
	public ref class CreatingInvestor : public System::Windows::Forms::Form
	{

	private: System::Windows::Forms::DataGridView^ dataGridView1;
	private: System::Windows::Forms::Button^ buttonAdd;
	private: System::Windows::Forms::Button^ buttonRemove;
	private: System::Windows::Forms::ListBox^ listBoxPortfolio;

	public:
		Market* market; // Вказівник на об'єкт класу Market
		Investor* user; // Вказівник на об'єкт класу user 
		CreatingInvestor(Investor* inUser, Market* inMarket)
		{
			InitializeComponent();
			user = inUser; 
			market = inMarket;
			loadMarketData();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~CreatingInvestor()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ textBox1;
	protected:
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::TextBox^ textBox3;

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;

	private: System::Windows::Forms::Button^ buttonOK;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->buttonOK = (gcnew System::Windows::Forms::Button());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->buttonAdd = (gcnew System::Windows::Forms::Button());
			this->buttonRemove = (gcnew System::Windows::Forms::Button());
			this->listBoxPortfolio = (gcnew System::Windows::Forms::ListBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Yu Gothic", 10.2F));
			this->textBox1->Location = System::Drawing::Point(183, 29);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(293, 51);
			this->textBox1->TabIndex = 0;
			// 
			// textBox2
			// 
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Yu Gothic", 10.2F));
			this->textBox2->Location = System::Drawing::Point(183, 105);
			this->textBox2->Multiline = true;
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(293, 51);
			this->textBox2->TabIndex = 1;
			// 
			// textBox3
			// 
			this->textBox3->Font = (gcnew System::Drawing::Font(L"Yu Gothic", 10.2F));
			this->textBox3->Location = System::Drawing::Point(183, 180);
			this->textBox3->Multiline = true;
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(293, 51);
			this->textBox3->TabIndex = 2;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Yu Gothic", 10.2F));
			this->label1->Location = System::Drawing::Point(38, 49);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(90, 22);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Full name:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Yu Gothic", 10.2F));
			this->label2->Location = System::Drawing::Point(38, 123);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(125, 22);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Risk tolerance:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Yu Gothic", 10.2F));
			this->label3->Location = System::Drawing::Point(38, 200);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(115, 22);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Target return:";
			// 
			// buttonOK
			// 
			this->buttonOK->Font = (gcnew System::Drawing::Font(L"Yu Gothic", 10.2F));
			this->buttonOK->Location = System::Drawing::Point(1287, 789);
			this->buttonOK->Name = L"buttonOK";
			this->buttonOK->Size = System::Drawing::Size(108, 51);
			this->buttonOK->TabIndex = 8;
			this->buttonOK->Text = L"OK";
			this->buttonOK->UseVisualStyleBackColor = true;
			this->buttonOK->Click += gcnew System::EventHandler(this, &CreatingInvestor::buttonOK_Click);
			// 
			// dataGridView1
			// 
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Location = System::Drawing::Point(511, 35);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersWidth = 51;
			this->dataGridView1->RowTemplate->Height = 24;
			this->dataGridView1->Size = System::Drawing::Size(884, 457);
			this->dataGridView1->TabIndex = 9;
			// 
			// buttonAdd
			// 
			this->buttonAdd->Font = (gcnew System::Drawing::Font(L"Yu Gothic", 10.2F));
			this->buttonAdd->Location = System::Drawing::Point(511, 508);
			this->buttonAdd->Name = L"buttonAdd";
			this->buttonAdd->Size = System::Drawing::Size(147, 59);
			this->buttonAdd->TabIndex = 10;
			this->buttonAdd->Text = L"Add";
			this->buttonAdd->UseVisualStyleBackColor = true;
			this->buttonAdd->Click += gcnew System::EventHandler(this, &CreatingInvestor::buttonAdd_Click);
			// 
			// buttonRemove
			// 
			this->buttonRemove->Font = (gcnew System::Drawing::Font(L"Yu Gothic", 10.2F));
			this->buttonRemove->Location = System::Drawing::Point(206, 644);
			this->buttonRemove->Name = L"buttonRemove";
			this->buttonRemove->Size = System::Drawing::Size(147, 59);
			this->buttonRemove->TabIndex = 11;
			this->buttonRemove->Text = L"Remove";
			this->buttonRemove->UseVisualStyleBackColor = true;
			this->buttonRemove->Click += gcnew System::EventHandler(this, &CreatingInvestor::buttonRemove_Click);
			// 
			// listBoxPortfolio
			// 
			this->listBoxPortfolio->Font = (gcnew System::Drawing::Font(L"Yu Gothic", 10.2F));
			this->listBoxPortfolio->FormattingEnabled = true;
			this->listBoxPortfolio->ItemHeight = 22;
			this->listBoxPortfolio->Location = System::Drawing::Point(42, 272);
			this->listBoxPortfolio->Name = L"listBoxPortfolio";
			this->listBoxPortfolio->Size = System::Drawing::Size(311, 356);
			this->listBoxPortfolio->TabIndex = 12;
			// 
			// CreatingInvestor
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::AliceBlue;
			this->ClientSize = System::Drawing::Size(1424, 852);
			this->Controls->Add(this->listBoxPortfolio);
			this->Controls->Add(this->buttonRemove);
			this->Controls->Add(this->buttonAdd);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->buttonOK);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Name = L"CreatingInvestor";
			this->Text = L"CreatingInvestor";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void buttonOK_Click(System::Object^ sender, System::EventArgs^ e); //Обробка кнопки ОК
	private: string toStdString(String^ s); // Перетворення System::String у std::string
	private: void Kursovawin::CreatingInvestor::loadMarketData(); // Завантаження дані з файлу
	private: System::Void buttonAdd_Click(System::Object^ sender, System::EventArgs^ e); // Обробка кнопки Add
	private: System::Void buttonRemove_Click(System::Object^ sender, System::EventArgs^ e); // Обробка кнопки Remove
	};
}
