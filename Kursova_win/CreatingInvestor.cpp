#include "CreatingInvestor.h"
#include <msclr/marshal_cppstd.h>
#include "Exception.h"
using namespace msclr::interop;

// Конвертація System::String у string.
string Kursovawin::CreatingInvestor::toStdString(String^ s)
{
    marshal_context context;
    return context.marshal_as<string>(s);
}
/* 
    Зчитує введені параметри інвестора, перевіряє коректність,
    перевіряє чи вибрано хоча б один актив.
    Якщо все добре — зберігає дані та закриває форму.
*/
System::Void Kursovawin::CreatingInvestor::buttonOK_Click(System::Object^ sender, System::EventArgs^ e)
{
    try
    {
        double riskTolerance, targetReturn;
        // Перевірка числового введення
        if (!Double::TryParse(textBox2->Text, riskTolerance) ||
            !Double::TryParse(textBox3->Text, targetReturn))
        {
            MessageBox::Show("Invalid risk tolerance or target return.");
            return;
        }
        // Портфель не може бути порожнім
        if (user->getPortfolio().getAssets().empty())
        {
            MessageBox::Show("Please select at least one asset.");
            return;
        }
        // Записуємо дані інвестора
        user->setData(
            toStdString(textBox1->Text),
            riskTolerance,
            targetReturn);
        // Повертаємо позитивний результат діалогу
        this->DialogResult = System::Windows::Forms::DialogResult::OK;
        this->Close();
    }
    catch (exception& ex)
    {
        MessageBox::Show(gcnew String(ex.what()));
    }
}
/* 
    Додає вибраний актив у портфель.
    Перевіряє дублікати, знаходить актив у ринку, 
    оновлює ваги всіх активів на рівномірні перед додаванням нового.
*/
System::Void Kursovawin::CreatingInvestor::buttonAdd_Click(System::Object^ sender, System::EventArgs^ e)
{
    for each (DataGridViewRow ^ row in dataGridView1->SelectedRows)
    {
        String^ name = row->Cells["Name"]->Value ? row->Cells["Name"]->Value->ToString() : "";
        string stdName = toStdString(name);

        // Перевірка чи актив вже доданий
        bool alreadyAdded = false;
        auto& currentAssets = user->getPortfolio().getAssets();
        for (const auto& existingAsset : currentAssets)
        {
            if (existingAsset.first.getName() == stdName)
            {
                alreadyAdded = true;
                break;
            }
        }

        if (alreadyAdded)
        {
            MessageBox::Show("Asset '" + name + "' is already in portfolio.", "Duplicate Asset");
            continue; // Переходимо до наступного рядка
        }

        // Пошук активу серед доступних у ринку
        bool found = false;
        for (const auto& asset : market->getAvailableAssets())
        {
            if (asset.getName() == stdName)
            {
                // Розрахунок рівномірних ваг після додавання активу
                int currentCount = user->getPortfolio().getAssets().size();
                double uniformWeight = 1.0 / (currentCount + 1);
                // Перенормування ваг існуючих активів
                auto& assets = user->getPortfolio().getAssets();
                for (auto& existingAsset : assets)
                {
                    existingAsset.second = uniformWeight;
                }

                // Додаємо новий актив з тією ж вагою
                user->getPortfolio().addAsset(asset, uniformWeight);
                listBoxPortfolio->Items->Add(name);
                found = true;
                break;
            }
        }
        // Якщо актив не знайдено у ринку
        if (!found)
            MessageBox::Show("Asset not found: " + name, "Error");
    }
}

/*
     Видаляє вибраний актив з портфеля користувача.
     Оновлює список у ListBox.
*/
System::Void Kursovawin::CreatingInvestor::buttonRemove_Click(System::Object^ sender, System::EventArgs^ e)
{
    // Перевірка чи обрано елемент
    if (listBoxPortfolio->SelectedIndex == -1)
    {
        MessageBox::Show("Choose asset to remove");
        return;
    }

    String^ name = safe_cast<String^>(listBoxPortfolio->SelectedItem);
    string stdName = toStdString(name);

    auto& assets = user->getPortfolio().getAssets();

    // Видалення активу з вектора портфеля
    for (auto it = assets.begin(); it != assets.end(); )
    {
        if (it->first.getName() == stdName)
        {
            it = assets.erase(it);
        }
        else
        {
            ++it;
        }
    }
    // Видалення з GUI списку
    listBoxPortfolio->Items->RemoveAt(listBoxPortfolio->SelectedIndex);
}

/*
    Записування інформації про активи у таблицю
*/
void Kursovawin::CreatingInvestor::loadMarketData()
{
    dataGridView1->Columns->Clear();
    dataGridView1->Rows->Clear();

    // Додаємо стовпці
    dataGridView1->Columns->Add("Name", "Name");
    dataGridView1->Columns->Add("Type", "Type");
    dataGridView1->Columns->Add("Price", "Price");
    dataGridView1->Columns->Add("ExpectedReturn", "Exp Return");
    dataGridView1->Columns->Add("Risk", "Risk");
    int n = market->getAvailableAssets()[0].getHistoricalReturns().size();
    // Додаємо стовпці для доходів
    for (int i = 1; i <= n; i++)
    {
        dataGridView1->Columns->Add("Ret" + i, "Return " + i);
        dataGridView1->Columns[4 + i]->DefaultCellStyle->Format = "F3";
    }

    // Форматування
    dataGridView1->Columns["Price"]->DefaultCellStyle->Format = "F2";
    dataGridView1->Columns["ExpectedReturn"]->DefaultCellStyle->Format = "P2";
    dataGridView1->Columns["Risk"]->DefaultCellStyle->Format = "P2";
    // Заповнюємо дані
    for (const auto& asset : market->getAvailableAssets())
    {
        const auto& returns = asset.getHistoricalReturns();

        // Створюємо список значень
        System::Collections::Generic::List<Object^>^ rowValues = gcnew System::Collections::Generic::List<Object^>();

        // Додаємо основні дані
        rowValues->Add(gcnew String(asset.getName().c_str()));
        rowValues->Add(gcnew String(asset.getType().c_str()));
        rowValues->Add(asset.getPrice());
        rowValues->Add(asset.calculateExpectedReturn());
        rowValues->Add(asset.calculateRisk());

        // Додаємо доходності 
        int returnsToShow = n;
        for (int i = 0; i < returnsToShow; i++)
        {
            if (i < returns.size())
                rowValues->Add(returns[i]); 
            else
                rowValues->Add(0.0);
        }

        // Додаємо рядок
        dataGridView1->Rows->Add(rowValues->ToArray());
    }
}
