#pragma once
#include "Investor.h"
namespace Kursovawin {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Windows::Forms::DataVisualization::Charting;

	/// <summary>
	/// Summary for Finance
	/// </summary>
	public ref class Finance : public System::Windows::Forms::Form
	{
	private: Investor* User1; //Вказівник на об	єкт класу Investor
	public:
		
		Finance(void)
		{
			User1 = nullptr;
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Finance()
		{
			if (components)
			{
				delete components;
			}
			if (User1 != nullptr) 
			{
				delete User1;
				User1 = nullptr;
			}
		}
	private: System::Windows::Forms::Button^ buttonCreateInvestor;
	private: System::Windows::Forms::Button^ buttonMarkovits;
	private: System::Windows::Forms::Button^ buttonGreadyAlg;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::Button^ buttonClusteringAlg;
	private: System::Windows::Forms::Button^ buttonMarket;
	private: System::Windows::Forms::Button^ buttonRecomendation;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chartReturn;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chartRisk;
	public: System::Windows::Forms::TextBox^ textBox1;



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
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea5 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend5 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series5 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea6 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend6 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series6 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->buttonCreateInvestor = (gcnew System::Windows::Forms::Button());
			this->buttonMarkovits = (gcnew System::Windows::Forms::Button());
			this->buttonGreadyAlg = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->buttonClusteringAlg = (gcnew System::Windows::Forms::Button());
			this->buttonMarket = (gcnew System::Windows::Forms::Button());
			this->buttonRecomendation = (gcnew System::Windows::Forms::Button());
			this->chartReturn = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->chartRisk = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chartReturn))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chartRisk))->BeginInit();
			this->SuspendLayout();
			// 
			// buttonCreateInvestor
			// 
			this->buttonCreateInvestor->Font = (gcnew System::Drawing::Font(L"Yu Gothic", 10.2F));
			this->buttonCreateInvestor->Location = System::Drawing::Point(1241, 34);
			this->buttonCreateInvestor->Name = L"buttonCreateInvestor";
			this->buttonCreateInvestor->Size = System::Drawing::Size(163, 57);
			this->buttonCreateInvestor->TabIndex = 1;
			this->buttonCreateInvestor->Text = L"Create investor";
			this->buttonCreateInvestor->UseVisualStyleBackColor = true;
			this->buttonCreateInvestor->Click += gcnew System::EventHandler(this, &Finance::buttonCreateInvestor_Click);
			// 
			// buttonMarkovits
			// 
			this->buttonMarkovits->Location = System::Drawing::Point(33, 34);
			this->buttonMarkovits->Name = L"buttonMarkovits";
			this->buttonMarkovits->Size = System::Drawing::Size(163, 57);
			this->buttonMarkovits->TabIndex = 2;
			this->buttonMarkovits->Text = L"Markovitz";
			this->buttonMarkovits->UseVisualStyleBackColor = true;
			this->buttonMarkovits->Click += gcnew System::EventHandler(this, &Finance::buttonMarkovits_Click);
			// 
			// buttonGreadyAlg
			// 
			this->buttonGreadyAlg->Location = System::Drawing::Point(33, 104);
			this->buttonGreadyAlg->Name = L"buttonGreadyAlg";
			this->buttonGreadyAlg->Size = System::Drawing::Size(163, 57);
			this->buttonGreadyAlg->TabIndex = 3;
			this->buttonGreadyAlg->Text = L"Gready algorithm";
			this->buttonGreadyAlg->UseVisualStyleBackColor = true;
			this->buttonGreadyAlg->Click += gcnew System::EventHandler(this, &Finance::buttonGreadyAlg_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->buttonClusteringAlg);
			this->groupBox1->Controls->Add(this->buttonGreadyAlg);
			this->groupBox1->Controls->Add(this->buttonMarkovits);
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"Yu Gothic", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->groupBox1->Location = System::Drawing::Point(1208, 109);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(231, 254);
			this->groupBox1->TabIndex = 4;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Optimization algorithms";
			// 
			// buttonClusteringAlg
			// 
			this->buttonClusteringAlg->Location = System::Drawing::Point(33, 177);
			this->buttonClusteringAlg->Name = L"buttonClusteringAlg";
			this->buttonClusteringAlg->Size = System::Drawing::Size(163, 57);
			this->buttonClusteringAlg->TabIndex = 4;
			this->buttonClusteringAlg->Text = L"Clustering";
			this->buttonClusteringAlg->UseVisualStyleBackColor = true;
			this->buttonClusteringAlg->Click += gcnew System::EventHandler(this, &Finance::buttonClusteringAlg_Click);
			// 
			// buttonMarket
			// 
			this->buttonMarket->Font = (gcnew System::Drawing::Font(L"Yu Gothic", 10.2F));
			this->buttonMarket->Location = System::Drawing::Point(1241, 389);
			this->buttonMarket->Name = L"buttonMarket";
			this->buttonMarket->Size = System::Drawing::Size(163, 57);
			this->buttonMarket->TabIndex = 5;
			this->buttonMarket->Text = L"Market";
			this->buttonMarket->UseVisualStyleBackColor = true;
			this->buttonMarket->Click += gcnew System::EventHandler(this, &Finance::buttonMarket_Click);
			// 
			// buttonRecomendation
			// 
			this->buttonRecomendation->Font = (gcnew System::Drawing::Font(L"Yu Gothic", 10.2F));
			this->buttonRecomendation->Location = System::Drawing::Point(1241, 463);
			this->buttonRecomendation->Name = L"buttonRecomendation";
			this->buttonRecomendation->Size = System::Drawing::Size(163, 57);
			this->buttonRecomendation->TabIndex = 7;
			this->buttonRecomendation->Text = L"Recomendation";
			this->buttonRecomendation->UseVisualStyleBackColor = true;
			this->buttonRecomendation->Click += gcnew System::EventHandler(this, &Finance::buttonRecomendation_Click);
			// 
			// chartReturn
			// 
			this->chartReturn->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			chartArea5->Name = L"ChartArea1";
			this->chartReturn->ChartAreas->Add(chartArea5);
			legend5->Name = L"Legend1";
			this->chartReturn->Legends->Add(legend5);
			this->chartReturn->Location = System::Drawing::Point(472, 34);
			this->chartReturn->Name = L"chartReturn";
			series5->ChartArea = L"ChartArea1";
			series5->Legend = L"Legend1";
			series5->Name = L"Series1";
			this->chartReturn->Series->Add(series5);
			this->chartReturn->Size = System::Drawing::Size(719, 320);
			this->chartReturn->TabIndex = 8;
			this->chartReturn->Text = L"chart1";
			// 
			// chartRisk
			// 
			chartArea6->Name = L"ChartArea1";
			this->chartRisk->ChartAreas->Add(chartArea6);
			legend6->Name = L"Legend1";
			this->chartRisk->Legends->Add(legend6);
			this->chartRisk->Location = System::Drawing::Point(472, 389);
			this->chartRisk->Name = L"chartRisk";
			series6->ChartArea = L"ChartArea1";
			series6->Legend = L"Legend1";
			series6->Name = L"Series1";
			this->chartRisk->Series->Add(series6);
			this->chartRisk->Size = System::Drawing::Size(719, 334);
			this->chartRisk->TabIndex = 9;
			this->chartRisk->Text = L"chartRisk";
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Yu Gothic", 10.2F));
			this->textBox1->Location = System::Drawing::Point(42, 34);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox1->Size = System::Drawing::Size(403, 689);
			this->textBox1->TabIndex = 10;
			// 
			// Finance
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::AliceBlue;
			this->ClientSize = System::Drawing::Size(1451, 794);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->chartRisk);
			this->Controls->Add(this->chartReturn);
			this->Controls->Add(this->buttonRecomendation);
			this->Controls->Add(this->buttonMarket);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->buttonCreateInvestor);
			this->Name = L"Finance";
			this->Text = L"Finance";
			this->groupBox1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chartReturn))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chartRisk))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void buttonCreateInvestor_Click(System::Object^ sender, System::EventArgs^ e); // Обробка кнопки Create investor
	  public: void printInvestor(TextBox^ textBox1); // вивід інформації про інвестора та портфоліо
	  public: void drawCharts(); // Виведення графіків 
private: System::Void buttonMarkovits_Click(System::Object^ sender, System::EventArgs^ e); // Обробка кнопки Markovitz
private: System::Void buttonGreadyAlg_Click(System::Object^ sender, System::EventArgs^ e); // Обробка кнопки Gready
private: System::Void buttonClusteringAlg_Click(System::Object^ sender, System::EventArgs^ e); // Обробка кнопки Clustering
private: System::Void buttonMarket_Click(System::Object^ sender, System::EventArgs^ e); // Обробка кнопки Market
private: System::Void buttonRecomendation_Click(System::Object^ sender, System::EventArgs^ e); // Обробка кнопки Recommendation
};
}
