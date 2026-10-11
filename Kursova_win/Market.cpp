#include "Market.h"
#include <fstream>
#include <sstream>
#include "Exception.h"

void Market::loadFromFile(const string& filename)
{
    ifstream file(filename);

    // Якщо файл не відкрився — кидаємо виняток
    if (!file.is_open())
        throw ExceptionIO();

    availableAssets.clear();
    string line;
    bool hasData = false;
    int expectedHistorySize = -1;

    // Читаємо кожен рядок файлу
    while (getline(file, line))
    {
        if (line.empty()) continue;
        hasData = true;

        stringstream ss(line);
        string token;
        string name, type;
        double price;
        vector<double> historicalReturns;
        vector<string> tokens;

        // 1. Читаємо назву активу
        if (!getline(ss, name, ','))
        {
            continue;
        }

        // 2. Тип активу (наприклад: Stock, Bond)
        if (!getline(ss, type, ','))
        {
            continue;
        }

        // 3. Поточна ціна
        if (!getline(ss, token, ','))
        {
            continue;
        }
        price = stod(token);

        // 4. Усі наступні значення — історичні доходності
        while (getline(ss, token, ','))
            tokens.push_back(token);

        if (tokens.empty()) continue;

        // Перетворення рядкових значень у числа
        for (const auto& t : tokens)
            historicalReturns.push_back(stod(t));

        // Якщо немає історичних даних — актив некоректний
        if (historicalReturns.empty())
            throw ExceptionInvalidAsset(name);
        if (expectedHistorySize == -1)
        {
            expectedHistorySize = historicalReturns.size();
        }
        else if (historicalReturns.size() != expectedHistorySize)
        {
            throw ExceptionHRMismatch();
        }
        // Додаємо новий актив до ринку
        availableAssets.emplace_back(name, type, price, historicalReturns);
    }

    // Файл був відкритий, але даних немає
    if (!hasData)
        throw ExceptionEmptyPortfolio();

    file.close();
}


const vector<Asset>& Market::getAvailableAssets() const
{
    return availableAssets;
}

string Market::simulateMarketScenario(vector<pair<Asset, double>>& currentAssets)
{
    // Отримуємо випадково вибраний сценарій: криза, ріст або стабільність
    ScenarioType scenario = getRandomScenario();

    double shift = 0.0;
    string scenarioName;

    // Встановлення базового зміщення ринку відповідно до сценарію
    switch (scenario)
    {
    case CRISIS:
        shift = -0.04;            // У кризу очікуваний спад доходності
        scenarioName = "Crisis";
        break;

    case GROWTH:
        shift = 0.04;             // При рості очікується підвищення доходності
        scenarioName = "Growth";
        break;

    case STABLE:
        shift = 0.01;              // Стабільний ринок — без глобального зміщення
        scenarioName = "Stable";
        break;
    }

    // random_device - дає випадкове зерно (seed) з апаратного джерела
    random_device rd;
     
    // mt19937 — генератор псевдовипадкових чисел (Mersenne Twister)
    // Ініціалізується за допомогою rd()
    mt19937 gen(rd());

    // Базовий шум ринку: нормальний розподіл зі середнім 0 і малим відхиленням
    // Використовується для додавання природної волатильності
    normal_distribution<double> baseNoise(0.0, 0.005);

    // Проходимо кожен актив у портфелі
    for (auto& item : currentAssets)
    {
        Asset& a = item.first;

        vector<double> newReturns = a.getHistoricalReturns();

        // Рандомний ринковий зсув = глобальне зміщення + невеликий шум
        double randomShift = shift + baseNoise(gen);

        // Додатковий шум, специфічний для окремого активу.

        // Середнє = randomShift
        // Стандартне відхилення = 0.01 + половина абсолютного зсуву
        normal_distribution<double> assetNoise(randomShift, 0.01 + abs(randomShift / 2.0));

        // Генеруємо нову доходність активу згідно нормального розподілу
        double newReturn = assetNoise(gen);

        // Додаємо нову доходність у історію
        newReturns.push_back(newReturn);

        // Оновлюємо актив
        a.setHistoricalReturns(newReturns);
    }

    // Повертаємо назву сценарію (для показу в інтерфейсі)
    return scenarioName;
}


Market::ScenarioType Market::getRandomScenario()
{
    // Випадкове число від 0 до 2
    int r = rand() % 3;

    // Перетворюємо на enum
    return static_cast<ScenarioType>(r);
}
