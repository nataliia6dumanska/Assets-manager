#include "Visualization.h"
#include "Finance.h"
#include "ManageOptimization.h"

/*
	Вивід повної інформації про інвестора та його портфель у TextBox.
	Формує структурований текст: ім'я, толерантність до ризику,
	цільова дохідність, очікувана дохідність, ризик портфеля,
	а також деталі кожного активу.
*/
void Kursovawin::Visualization::printInvestor(TextBox^ textBox1)
{
	try
	{
		// Формування інформації про інвестора та його портфель
		String^ output = "Name: " + gcnew String(User1Optimized->getFullName().c_str()) +
			"\r\nRisk tolerance: " + User1Optimized->getRiskTolerance().ToString("P3") +
			"\r\nTarget Return: " + User1Optimized->getTargetReturn().ToString("P3") +
			"\r\nExpected return: " + User1Optimized->getPortfolio().calculateExpectedReturnPortfolio().ToString("P3") +
			"\r\nRisk: " + User1Optimized->getPortfolio().calculateRiskPortfolio().ToString("P3") +
			"\r\n\r\nPortfolio:\r\n";

		// Отримання портфеля та активів
		Portfolio portfolio = User1Optimized->getPortfolio();
		auto assets = portfolio.getAssets();

		// Вивід кожного активу, його ваги та фінансових характеристик
		for (const auto& pair : assets)
		{
			const Asset& asset = pair.first;

			output += " - " + gcnew String(asset.getName().c_str()) +
				" ( Weight: " + pair.second.ToString("F3") + " )"
				"\r\n   Type: " + gcnew System::String(asset.getType().c_str()) +
				"\r\n   Price: $" + asset.getPrice().ToString("F3") +
				"\r\n   Expected Return: " + asset.calculateExpectedReturn().ToString("P3") +
				"\r\n   Risk: " + asset.calculateRisk().ToString("P3") + "\r\n\r\n";
		}

		// Виведення у TextBox
		textBox1->Text = output;
	}
	catch (const exception& e)
	{
		// Обробка помилок
		MessageBox::Show(gcnew String(e.what()), "Optimization Error");
	}
}

/*
	Побудова графіків до / після оптимізації.
	Перший графік — ваги активів.
	Другий — ризик та дохідність.
 */
void Kursovawin::Visualization::drawCharts()
{
	try
	{
		// Отримання початкового та оптимізованого портфелів
		Portfolio basePortfolio = User1->getPortfolio();
		Portfolio optPortfolio = User1Optimized->getPortfolio();

		auto baseAssets = basePortfolio.getAssets();
		auto optAssets = optPortfolio.getAssets();

		// Очищення попередніх серій
		chartReturn->Series->Clear();
		chartRisk->Series->Clear();

		// Графік 1 – порівняння ваг активів

		chartReturn->ChartAreas[0]->AxisX->Title = "Assets";
		chartReturn->ChartAreas[0]->AxisY->Title = "Weight (%)";

		// Серія до оптимізації
		Series^ baseSeries = gcnew Series("Before Optimization");
		baseSeries->ChartType = SeriesChartType::Column;
		baseSeries->Color = Color::SteelBlue;

		// Серія після оптимізації
		Series^ optSeries = gcnew Series("After Optimization");
		optSeries->ChartType = SeriesChartType::Column;
		optSeries->Color = Color::OrangeRed;

		// Заповнення точок на графіках
		for (int i = 0; i < baseAssets.size(); i++)
		{
			String^ name = gcnew String(baseAssets[i].first.getName().c_str());
			baseSeries->Points->AddXY(name, baseAssets[i].second * 100);
			optSeries->Points->AddXY(name, optAssets[i].second * 100);
		}

		chartReturn->Series->Add(baseSeries);
		chartReturn->Series->Add(optSeries);

		// Графік 2 – ризик та дохідність

		chartRisk->ChartAreas[0]->AxisX->Title = "Metric";
		chartRisk->ChartAreas[0]->AxisY->Title = "Value (%)";

		Series^ beforeSeries = gcnew Series("Before Optimization");
		beforeSeries->ChartType = SeriesChartType::Column;
		beforeSeries->Color = Color::SteelBlue;

		Series^ afterSeries = gcnew Series("After Optimization");
		afterSeries->ChartType = SeriesChartType::Column;
		afterSeries->Color = Color::OrangeRed;

		// Обчислення показників
		double baseReturn = basePortfolio.calculateExpectedReturnPortfolio() * 100;
		double optReturn = optPortfolio.calculateExpectedReturnPortfolio() * 100;

		double baseRisk = basePortfolio.calculateRiskPortfolio() * 100;
		double optRisk = optPortfolio.calculateRiskPortfolio() * 100;

		// Додавання значень на графік
		beforeSeries->Points->AddXY("Expected Return", baseReturn);
		afterSeries->Points->AddXY("Expected Return", optReturn);

		beforeSeries->Points->AddXY("Risk", baseRisk);
		afterSeries->Points->AddXY("Risk", optRisk);

		chartRisk->Series->Add(beforeSeries);
		chartRisk->Series->Add(afterSeries);

		chartRisk->ChartAreas[0]->AxisX->Interval = 1;
		chartRisk->ChartAreas[0]->AxisY->Minimum = 0;
		chartRisk->Legends[0]->Docking = Docking::Top;
	}
	catch (const exception& e)
	{
		MessageBox::Show(gcnew String(e.what()), "Optimization Error");
	}
}

/* 
	Застосування оптимізованих ваг до базового інвестора.
	Оновлює дані у формі Finance та оновлює графіки.
 */
System::Void Kursovawin::Visualization::buttonApply_Click(System::Object^ sender, System::EventArgs^ e)
{
	// Отримуємо оптимальні ваги активів
	vector<double> newWeights = User1Optimized->getPortfolio().getWeights();

	// Застосовуємо їх до базового користувача
	User1->getPortfolio().setWeights(newWeights);

	// Якщо відкривалось як модальне вікно – оновлюємо дані на головній формі
	if (this->Owner != nullptr)
	{
		((Kursovawin::Finance^)this->Owner)->printInvestor(((Kursovawin::Finance^)this->Owner)->textBox1);
		((Kursovawin::Finance^)this->Owner)->drawCharts();
	}

	// Закриваємо вікно оптимізації
	this->Close();
}
