#pragma once
#include "Investor.h"
#include "ManageOptimization.h"
namespace Kursovawin {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Windows::Forms::DataVisualization::Charting;

	/// <summary>
	/// Summary for Recommendations
	/// </summary>
	public ref class Recommendations : public System::Windows::Forms::Form
	{
	private: Investor* User;
	public:
		Recommendations(Investor* inv)
		{
			InitializeComponent();
			User = inv;
			printRecomendations(textBox1);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Recommendations()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ buttonOK;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chartRisk;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chartReturn;
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
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->buttonOK = (gcnew System::Windows::Forms::Button());
			this->chartRisk = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->chartReturn = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chartRisk))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chartReturn))->BeginInit();
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Yu Gothic", 10.2F));
			this->textBox1->Location = System::Drawing::Point(29, 69);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(677, 556);
			this->textBox1->TabIndex = 0;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Yu Gothic", 10.2F));
			this->label1->Location = System::Drawing::Point(26, 29);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(156, 22);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Recommendations";
			// 
			// buttonOK
			// 
			this->buttonOK->Font = (gcnew System::Drawing::Font(L"Yu Gothic", 10.2F));
			this->buttonOK->Location = System::Drawing::Point(1254, 649);
			this->buttonOK->Name = L"buttonOK";
			this->buttonOK->Size = System::Drawing::Size(163, 57);
			this->buttonOK->TabIndex = 15;
			this->buttonOK->Text = L"OK";
			this->buttonOK->UseVisualStyleBackColor = true;
			this->buttonOK->Click += gcnew System::EventHandler(this, &Recommendations::buttonOK_Click);
			// 
			// chartRisk
			// 
			chartArea1->Name = L"ChartArea1";
			this->chartRisk->ChartAreas->Add(chartArea1);
			legend1->Name = L"Legend1";
			this->chartRisk->Legends->Add(legend1);
			this->chartRisk->Location = System::Drawing::Point(763, 347);
			this->chartRisk->Name = L"chartRisk";
			series1->ChartArea = L"ChartArea1";
			series1->Legend = L"Legend1";
			series1->Name = L"Series1";
			this->chartRisk->Series->Add(series1);
			this->chartRisk->Size = System::Drawing::Size(611, 278);
			this->chartRisk->TabIndex = 17;
			this->chartRisk->Text = L"chartRisk";
			// 
			// chartReturn
			// 
			this->chartReturn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			chartArea2->Name = L"ChartArea1";
			this->chartReturn->ChartAreas->Add(chartArea2);
			legend2->Name = L"Legend1";
			this->chartReturn->Legends->Add(legend2);
			this->chartReturn->Location = System::Drawing::Point(763, 63);
			this->chartReturn->Name = L"chartReturn";
			series2->ChartArea = L"ChartArea1";
			series2->Legend = L"Legend1";
			series2->Name = L"Series1";
			this->chartReturn->Series->Add(series2);
			this->chartReturn->Size = System::Drawing::Size(611, 278);
			this->chartReturn->TabIndex = 16;
			this->chartReturn->Text = L"chart1";
			// 
			// Recommendations
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::AliceBlue;
			this->ClientSize = System::Drawing::Size(1439, 718);
			this->Controls->Add(this->chartRisk);
			this->Controls->Add(this->chartReturn);
			this->Controls->Add(this->buttonOK);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Name = L"Recommendations";
			this->Text = L"Recommendations";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chartRisk))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chartReturn))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void buttonOK_Click(System::Object^ sender, System::EventArgs^ e); // обробка кнопки ОК
	private: void printRecomendations(TextBox^ textBox1); // Вивід рекомендації та графіків
};
}
