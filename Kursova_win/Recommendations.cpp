#include "Recommendations.h"
using namespace System::Windows::Forms::DataVisualization::Charting;

// Обробник кнопки "OK" — просто закриває вікно рекомендацій
System::Void Kursovawin::Recommendations::buttonOK_Click(System::Object^ sender, System::EventArgs^ e)
{
    this->Close();
}

/*
    Вивід рекомендацій:
    - створює копії інвестора для трьох стратегій,
    - застосовує кожну стратегію оптимізації,
    - обчислює ризик, дохідність і коефіцієнт Шарпа,
    - відображає результати в текстовому полі,
    - порівнює їх і визначає найкращу стратегію,
    - будує дві діаграми (Risk та Return) у ChartControl.
*/
void Kursovawin::Recommendations::printRecomendations(TextBox^ textBox1)
{
    try
    {
        textBox1->Clear();   // Очищення текстового поля

        // Створюємо 3 копії поточного інвестора
        vector<Investor> CopyUsers(3, *User);
        ManageOptimization manager;

        // Назви стратегій (відображаються у виводі та на графіках)
        vector<string> strategyNames =
        {
            "Markowitz Strategy",
            "Greedy Strategy",
            "Clustering Strategy"
        };

        // Масиви для збирання показників
        vector<double> risks;
        vector<double> returns;
        vector<double> sharpes;

        // Базові показники портфеля користувача
        double baseRisk = User->getPortfolio().calculateRiskPortfolio();
        double baseReturn = User->getPortfolio().calculateExpectedReturnPortfolio();

        // Вивід поточного стану портфеля
        textBox1->AppendText("Current portfolio:\r\n");
        textBox1->AppendText("  Risk: " + baseRisk.ToString("F4") + "\r\n");
        textBox1->AppendText("  Return: " + baseReturn.ToString("F4") + "\r\n\r\n");

        // Цикл по трьох стратегіях
        for (int i = 0; i < CopyUsers.size(); i++)
        {
            // Призначення відповідної стратегії оптимізації
            if (i == 0)
            {
                MarkowitzStrategy m;
                manager.setStrategy(&m);
            }
            else if (i == 1)
            {
                GreedyStrategy g;
                manager.setStrategy(&g);
            }
            else if (i == 2)
            {
                ClusteringStrategy c;
                manager.setStrategy(&c);
            }

            // Оптимізація - отримуємо нові ваги активів
            vector<double> newWeights = manager.optimizePortfolio(CopyUsers[i]);

            // Записуємо нові ваги у портфель
            CopyUsers[i].getPortfolio().setWeights(newWeights);

            // Обчислення показників після оптимізації для обраунку коефіцієнта Шарпа
            double r = CopyUsers[i].getPortfolio().calculateRiskPortfolio();
            double ret = CopyUsers[i].getPortfolio().calculateExpectedReturnPortfolio();
            double sharpe = (r > 0.0) ? ret / r : 0.0;

            risks.push_back(r);
            returns.push_back(ret);
            sharpes.push_back(sharpe);

            // Різниця відносно базового портфеля
            double deltaR = r - baseRisk;
            double deltaRet = ret - baseReturn;

            // Вивід результатів поточної стратегії
            textBox1->AppendText(gcnew System::String(strategyNames[i].c_str()) + ":\r\n");
            textBox1->AppendText("  Risk: " + r.ToString("F4") + " (Diff "
                + (deltaR >= 0 ? "+" : "") + deltaR.ToString("F4") + ")\r\n");
            textBox1->AppendText("  Return: " + ret.ToString("F4") + " (Diff "
                + (deltaRet >= 0 ? "+" : "") + deltaRet.ToString("F4") + ")\r\n");
            textBox1->AppendText("  Sharpe ratio: " + sharpe.ToString("F4") + "\r\n\r\n");
        }

        // Пошук кращого коефіцієнта Шарпа
        int bestSharpeIdx = 0;
        double maxSharpe = sharpes[0];
        for (int i = 1; i < sharpes.size(); i++)
        {
            if (sharpes[i] > maxSharpe)
            {
                maxSharpe = sharpes[i];
                bestSharpeIdx = i;
            }
        }

        // Вивід рекомендації
        textBox1->AppendText("=== Recommendation ===\r\n");
        textBox1->AppendText("Best Sharpe ratio: " + maxSharpe.ToString("F4") + "\r\n");
        textBox1->AppendText("Recommended strategy: " +
            gcnew System::String(strategyNames[bestSharpeIdx].c_str()) + ".\r\n");

        // Перевірка: чи дає нова стратегія покращення
        if (maxSharpe < (baseReturn / baseRisk))
            textBox1->AppendText("None of the optimizations improved Sharpe ratio.\r\n");
        else
            textBox1->AppendText("This strategy provides the best risk-return tradeoff.\r\n");

        // Побудова графіка ризику
        chartRisk->Series->Clear();
        chartReturn->Series->Clear();

        // --- Risk Chart ---
        Series^ riskSeries = gcnew Series("Risk");
        riskSeries->ChartType = SeriesChartType::Column;
        riskSeries->Color = Color::DarkRed;

        // Поточний портфель
        riskSeries->Points->AddXY("Current", baseRisk);

        // Оптимізовані портфелі
        for (int i = 0; i < risks.size(); i++)
            riskSeries->Points->AddXY(gcnew System::String(strategyNames[i].c_str()), risks[i]);

        chartRisk->Series->Add(riskSeries);
        chartRisk->ChartAreas[0]->AxisY->Title = "Risk";
        chartRisk->ChartAreas[0]->AxisX->Title = "Strategy";

        // --- Return Chart ---
        Series^ retSeries = gcnew Series("Return");
        retSeries->ChartType = SeriesChartType::Column;
        retSeries->Color = Color::SteelBlue;

        retSeries->Points->AddXY("Current", baseReturn);
        for (int i = 0; i < returns.size(); i++)
            retSeries->Points->AddXY(gcnew System::String(strategyNames[i].c_str()), returns[i]);

        chartReturn->Series->Add(retSeries);
        chartReturn->ChartAreas[0]->AxisY->Title = "Expected return";
        chartReturn->ChartAreas[0]->AxisX->Title = "Strategy";
    }
    catch (const exception& e)
    {
        // Відображення помилки
        MessageBox::Show(gcnew String(e.what()), "Recomendations Error");
    }
}
