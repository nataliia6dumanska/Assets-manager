#pragma once
#include "Investor.h"
#include <vector>
#include <string>
namespace Kursovawin {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Windows::Forms::DataVisualization::Charting;

	/// <summary>
	/// Summary for Visualization
	/// </summary>
	public ref class Visualization : public System::Windows::Forms::Form
	{
	private: Investor* User1Optimized;
	public: System::Windows::Forms::TextBox^ textBox1;
	private:
	private: Investor* User1;
	public:
		Visualization(Investor* inv1, Investor* inv2, const string& title)
		{
			InitializeComponent();
			User1Optimized = inv2;
			User1 = inv1;
			this->Text = gcnew System::String(title.c_str());
			drawCharts();
			printInvestor(textBox1);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Visualization()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chartRisk;
	protected:
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chartReturn;

	private: System::Windows::Forms::Button^ buttonApply;

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
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea9 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend9 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series9 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea10 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend10 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series10 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->chartRisk = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->chartReturn = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->buttonApply = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chartRisk))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chartReturn))->BeginInit();
			this->SuspendLayout();
			// 
			// chartRisk
			// 
			chartArea9->Name = L"ChartArea1";
			this->chartRisk->ChartAreas->Add(chartArea9);
			legend9->Name = L"Legend1";
			this->chartRisk->Legends->Add(legend9);
			this->chartRisk->Location = System::Drawing::Point(444, 360);
			this->chartRisk->Name = L"chartRisk";
			series9->ChartArea = L"ChartArea1";
			series9->Legend = L"Legend1";
			series9->Name = L"Series1";
			this->chartRisk->Series->Add(series9);
			this->chartRisk->Size = System::Drawing::Size(719, 334);
			this->chartRisk->TabIndex = 12;
			this->chartRisk->Text = L"chartRisk";
			// 
			// chartReturn
			// 
			this->chartReturn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			chartArea10->Name = L"ChartArea1";
			this->chartReturn->ChartAreas->Add(chartArea10);
			legend10->Name = L"Legend1";
			this->chartReturn->Legends->Add(legend10);
			this->chartReturn->Location = System::Drawing::Point(444, 12);
			this->chartReturn->Name = L"chartReturn";
			series10->ChartArea = L"ChartArea1";
			series10->Legend = L"Legend1";
			series10->Name = L"Series1";
			this->chartReturn->Series->Add(series10);
			this->chartReturn->Size = System::Drawing::Size(719, 320);
			this->chartReturn->TabIndex = 11;
			this->chartReturn->Text = L"chart1";
			// 
			// buttonApply
			// 
			this->buttonApply->Font = (gcnew System::Drawing::Font(L"Yu Gothic", 10.2F));
			this->buttonApply->Location = System::Drawing::Point(1200, 637);
			this->buttonApply->Name = L"buttonApply";
			this->buttonApply->Size = System::Drawing::Size(163, 57);
			this->buttonApply->TabIndex = 14;
			this->buttonApply->Text = L"Apply  weights";
			this->buttonApply->UseVisualStyleBackColor = true;
			this->buttonApply->Click += gcnew System::EventHandler(this, &Visualization::buttonApply_Click);
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Yu Gothic", 10.2F));
			this->textBox1->Location = System::Drawing::Point(37, 12);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox1->Size = System::Drawing::Size(374, 682);
			this->textBox1->TabIndex = 15;
			// 
			// Visualization
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::AliceBlue;
			this->ClientSize = System::Drawing::Size(1391, 725);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->buttonApply);
			this->Controls->Add(this->chartRisk);
			this->Controls->Add(this->chartReturn);
			this->Name = L"Visualization";
			this->Text = L"Optimize Portfolio";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chartRisk))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chartReturn))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
		private: void drawCharts(); // Вивід інформації про інвестора та портфоліо
		private: void printInvestor(TextBox^ textBox1); // Вивід графіків
#pragma endregion
		private: System::Void buttonApply_Click(System::Object^ sender, System::EventArgs^ e); //Обробка кнопки Apply

};
	
}
