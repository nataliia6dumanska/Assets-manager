#include "Finance.h"
#include "CreatingInvestor.h"
#include "Exception.h"
#include "ManageOptimization.h"
#include "Visualization.h"
#include "Market.h"
#include "Recommendations.h"

/*
    Вивід повної інформації про інвестора та його портфель у TextBox.
    Формує структурований текст: ім'я, толерантність до ризику,
    цільова дохідність, очікувана дохідність, ризик портфеля,
    а також деталі кожного активу.
*/
void Kursovawin::Finance::printInvestor(TextBox^ textBox1)
{
    try
    {
        if (User1->getPortfolio().getAssets().empty())
            throw ExceptionInvalidInvestor();
        // Формування інформації про інвестора та його портфель
        String^ output = "Name: " + gcnew String(User1->getFullName().c_str()) +
            "\r\nRisk tolerance: " + User1->getRiskTolerance().ToString("P3") +
            "\r\nTarget Return: " + User1->getTargetReturn().ToString("P3") +
            "\r\nExpected return: " + User1->getPortfolio().calculateExpectedReturnPortfolio().ToString("P3") +
            "\r\nRisk: " + User1->getPortfolio().calculateRiskPortfolio().ToString("P3") +
            "\r\n\r\nPortfolio:\r\n";

        Portfolio portfolio = User1->getPortfolio();
        auto assets = portfolio.getAssets();

        // Вивід кожного активу, його ваги та фінансових характеристик
        for (const auto& pair : assets)
        {
            const Asset& asset = pair.first;
            output += " - " + gcnew String(asset.getName().c_str()) +
                " ( Weight: " + pair.second.ToString("F3") + " )"
                "\r\n   Type: " + gcnew String(asset.getType().c_str()) +
                "\r\n   Price: $" + asset.getPrice().ToString("F3") +
                "\r\n   Expected Return: " + asset.calculateExpectedReturn().ToString("P3") +
                "\r\n   Risk: " + asset.calculateRisk().ToString("P3") + "\r\n\r\n";
        }

        // Виведення у TextBox
        textBox1->Text = output;
        drawCharts();
    }
    catch (const exception& e)
    {
        // Обробка помилок
        MessageBox::Show(gcnew String(e.what()), "Error while printing investor");
    }
}

/*
    Побудова графіків до / після оптимізації.
    Перший графік — історія доходів кожного активу
    Другий — ризик та дохідність
 */
void Kursovawin::Finance::drawCharts()
{
    try
    {
        // Отримання портфеля
        Portfolio portfolio = User1->getPortfolio();
        auto assets = portfolio.getAssets();

        // Очищення попередніх серій
        chartReturn->Series->Clear();
        chartRisk->Series->Clear();

        // Графік 1 — історія доходів кожного активу
        chartReturn->ChartAreas[0]->AxisX->Title = "Period";
        chartReturn->ChartAreas[0]->AxisY->Title = "Profitability (%)";

        //вивід історії доходів 
        for (const auto& pair : assets)
        {
            const Asset& asset = pair.first;
            String^ name = gcnew String(asset.getName().c_str());
            vector<double> returns = asset.getHistoricalReturns();

            Series^ s = gcnew Series(name);
            s->ChartType = SeriesChartType::Line;
            s->BorderWidth = 2;
            s->IsValueShownAsLabel = false;

            for (int i = 0; i < returns.size(); i++)
            {
                s->Points->AddXY(i + 1, returns[i] * 100.0);
            }

            chartReturn->Series->Add(s);
        }
        
        chartRisk->ChartAreas[0]->AxisX->Title = "Asset";
        chartRisk->ChartAreas[0]->AxisY->Title = "Value";

        // Графік 2 - ризик і дохідність
        Series^ returnSeries = gcnew Series("Expected return");
        Series^ riskSeries = gcnew Series("Risk");

        returnSeries->ChartType = SeriesChartType::Column;
        riskSeries->ChartType = SeriesChartType::Column;

        // Виводимо ризик і дохідність кожного активу
        for (const auto& pair : assets)
        {
            const Asset& asset = pair.first;
            String^ name = gcnew String(asset.getName().c_str());
            double expectedReturn = asset.calculateExpectedReturn() * 100.0;
            double risk = asset.calculateRisk() * 100.0;

            returnSeries->Points->AddXY(name, expectedReturn);
            riskSeries->Points->AddXY(name, risk);
        }

        chartRisk->Series->Add(returnSeries);
        chartRisk->Series->Add(riskSeries);
    }
    catch (const exception& e) // Обробка помилок
    {
        MessageBox::Show(gcnew String(e.what()), "Error while drawing charts");
    }
}

// Оптимізація за моделлю Марковіца
System::Void Kursovawin::Finance::buttonMarkovits_Click(System::Object^ sender, System::EventArgs^ e)
{
    try
    {
        if (User1 == nullptr)
            throw ExceptionInvalidInvestor();  // Помилка: інвестор не ініціалізований

        // Створюємо копію інвестора для безпечної оптимізації
        Investor* optimizedInvestor = new Investor(*User1);

        ManageOptimization manager; // Менеджер стратегій
        MarkowitzStrategy strategy;  // Стратегія Марковіца
        manager.setStrategy(&strategy);                

        // Оптимізуємо ваги портфеля
        optimizedInvestor->getPortfolio().setWeights(manager.optimizePortfolio(*optimizedInvestor));

        // Відкриваємо форму візуалізації
        Visualization^ form = gcnew Visualization
        (
            User1,                   
            optimizedInvestor,        
            "Markowitz Strategy"     
        );
        form->Owner = this; // Встановлюємо батьківську форму
        form->Show();                 
    }
    catch (const exception& e)
    {
        // Обробка всіх помилок
        MessageBox::Show(gcnew String(e.what()), "Optimization Error (Markowitz)");
    }
}

// Жадібний алгоритм
System::Void Kursovawin::Finance::buttonGreadyAlg_Click(System::Object^ sender, System::EventArgs^ e)
{
    try
    {
        if (User1 == nullptr)
            throw ExceptionInvalidInvestor(); // Помилка: інвестор не ініціалізований
        // Створюємо копію інвестора для безпечної оптимізації
        Investor* optimizedInvestor = new Investor(*User1);  // Копіюємо інвестора

        ManageOptimization manager;    // Менеджер стратегій
        GreedyStrategy strategy;       // Жадібна стратегія
        manager.setStrategy(&strategy);

        optimizedInvestor->getPortfolio().setWeights(manager.optimizePortfolio(*optimizedInvestor));

        // Відкриваємо форму візуалізації
        Visualization^ form = gcnew Visualization(User1, optimizedInvestor, "Greedy Strategy");
        form->Owner = this; // Встановлюємо батьківську форму
        form->Show();
    }
    catch (const exception& e)
    {
        // Обробка всіх помилок
        MessageBox::Show(gcnew String(e.what()), "Optimization Error (Greedy)");
    }
}

// Кластериація за кореляціями
System::Void Kursovawin::Finance::buttonClusteringAlg_Click(System::Object^ sender, System::EventArgs^ e)
{
    try
    {
        if (User1 == nullptr)
            throw ExceptionInvalidInvestor(); // Помилка: інвестор не ініціалізований
        // Створюємо копію інвестора для безпечної оптимізації
        Investor* optimizedInvestor = new Investor(*User1);

        ManageOptimization manager; // Менеджер стратегій
        ClusteringStrategy strategy; // Стратегія кластеризації за кореляціями                        
        manager.setStrategy(&strategy);

        optimizedInvestor->getPortfolio().setWeights(manager.optimizePortfolio(*optimizedInvestor));

        // Відкриваємо форму візуалізації
        Visualization^ form = gcnew Visualization(User1, optimizedInvestor, "Clustering Strategy");
        form->Owner = this; // Встановлюємо батьківську форму
        form->Show();
    }
    catch (const exception& e)
    {
        // Обробка всіх помилок
        MessageBox::Show(gcnew String(e.what()), "Optimization Error (Clustering)");
    }
}

// Симуляція ринкових сценаріїв
System::Void Kursovawin::Finance::buttonMarket_Click(System::Object^ sender, System::EventArgs^ e)
{
    try
    {
        if (User1 == nullptr)
            throw ExceptionInvalidInvestor();

        Market market;

        //Застосовуємо випадковий сценарій (криза, ріст, стабільність)
        string type = market.simulateMarketScenario(User1->getPortfolio().getAssets());

        //Оновлюємо інтерфейс
        printInvestor(textBox1);  

        //Повідомляємо користувача
        MessageBox::Show(gcnew String(type.c_str()), "Market");
    }
    catch (const exception& e)
    {
        // Обробка всіх помилок
        MessageBox::Show(gcnew String(e.what()), "Market Error");
    }
}

// Рекомендації
System::Void Kursovawin::Finance::buttonRecomendation_Click(System::Object^ sender, System::EventArgs^ e)
{
    try
    {
        if (User1 == nullptr)
            throw ExceptionInvalidInvestor();

        // Відкриваємо форму з рекомендаціями 
        Recommendations^ form = gcnew Recommendations(User1);
        form->Owner = this;
        form->Show();
    }
    catch (const exception& e)
    {
        // Обробка всіх помилок
        MessageBox::Show(gcnew String(e.what()), "Recommendation Error");
    }
}

// Створення інвестора
System::Void Kursovawin::Finance::buttonCreateInvestor_Click(System::Object^ sender, System::EventArgs^ e)
{
    try
    {
        // Якщо інвестор ще не створено
        User1 = new Investor();

        //Завантажуємо ринок з файлу
        Market* market = new Market();
        market->loadFromFile("Text.txt");  // Формат: name,type,price,r1,r2,...

        //Відкриваємо діалог створення інвестора
        CreatingInvestor^ creatingForm = gcnew CreatingInvestor(User1, market);
        System::Windows::Forms::DialogResult result = creatingForm->ShowDialog();

        //Якщо користувач скасував — виходимо
        if (result != System::Windows::Forms::DialogResult::OK)
            return;

        // Перевірка: чи вибрав хоча б один актив
        if (User1->getPortfolio().getAssets().empty())
            throw ExceptionEmptyPortfolio();  // Помилка: портфель порожній

        // Оновлюємо інтерфейс
        printInvestor(textBox1);
    }
    catch (const exception& e)
    {
        // Обробка всіх помилок
        MessageBox::Show(gcnew String(e.what()), "Creating Error");
    }
}