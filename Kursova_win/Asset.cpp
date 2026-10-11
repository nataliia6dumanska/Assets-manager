#include "Asset.h"
#include "Exception.h"

Asset::Asset() : name("unnamed"), type("type"), price(0) {}

Asset::Asset(const string& _name, const string& _type, const double& _price,
    const vector<double>& _historacalReturns)
    : name(_name), type(_type), price(_price),
    historicalReturns(_historacalReturns)
{
    // Якщо ціна активу від'ємна — це помилка
    // ExceptionInvalidAsset(name) — твоє користувацьке виключення, яке вказує,
    // що актив з таким ім'ям некоректний (має неправильні параметри).
    if (_price < 0)
    {
        throw ExceptionInvalidAsset(_name);
        return;
    }

    // Якщо історичних значень немає, розрахувати доходність неможливо
    if (_historacalReturns.empty())
    {
        throw ExceptionInvalidAsset(_name);
        return;
    }
}

// Обчислює середню історичну доходність активу
double Asset::calculateExpectedReturn() const
{
    // Перевірка, чи є доступні дані
    if (historicalReturns.empty())
    {
        throw ExceptionInvalidAsset(name);
        return 0;
    }

    int n = historicalReturns.size();
    double expRet = 0;

    // Підсумовуємо всі доходності
    for (const double it : historicalReturns)
    {
        expRet += it;
    }

    // Середнє арифметичне
    return expRet / n;
}

// Обчислення ризику активу: стандартне відхилення (корінь з дисперсії)
double Asset::calculateRisk() const
{
    if (historicalReturns.empty())
    {
        throw ExceptionInvalidAsset(name);
        return 0;
    }

    int n = historicalReturns.size();
    double variance = 0;

    for (const double it : historicalReturns)
    {
        // Форма (x - μ)^2 
        variance += (it - calculateExpectedReturn()) * (it - calculateExpectedReturn());
    }

    variance = variance / n; // середнє значення квадратів відхилень

    // корінь — стандартне відхилення, показує ризик
    return sqrt(variance);
}

// Повертає ціну активу
const double Asset::getPrice() const
{
    return price;
}

// Повертає історичні доходності
const vector<double> Asset::getHistoricalReturns() const
{
    return historicalReturns;
}

// Повертає назву активу
const string Asset::getName() const
{
    return name;
}

// Повертає тип активу
const string Asset::getType() const
{
    return type;
}

// Оновлює історичні доходності активу
void Asset::setHistoricalReturns(const vector<double>& h)
{
    // Якщо новий набір порожній → помилка
    if (h.empty())
    {
        throw ExceptionInvalidAsset(name);
        return;
    }

    historicalReturns = h;
}