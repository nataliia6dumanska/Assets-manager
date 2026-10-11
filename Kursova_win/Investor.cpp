
#include "Investor.h"

Investor::Investor()
    : fullName(" "), riskTolerance(0),
    targetReturn(0), portfolio(Portfolio()) { }

Investor::Investor(const string& _fullName, double _riskTolerance,
    double _targetReturn)
    : fullName(_fullName), riskTolerance(_riskTolerance),
    targetReturn(_targetReturn) 
{
    // Перевірка коректності значень інвестора:
    // riskTolerance і targetReturn мають бути всередині (0;1]
    // Якщо хоч одна змінна некоректна → кидаємо виняток
    if (riskTolerance > 1.0 || riskTolerance <= 0)
        throw ExceptionInvalidInvestor();
    if (targetReturn > 1.0 || targetReturn <= 0)
        throw ExceptionInvalidInvestor();
}

const double Investor::getTargetReturn() const
{
    return targetReturn;
}

const string& Investor::getFullName() const
{
    return fullName;
}

const double Investor::getRiskTolerance() const
{
    return riskTolerance;
}

// Повертає портфель (як константне посилання)
const Portfolio& Investor::getPortfolio() const
{
    return portfolio;
}

// Повертає портфель (неконстантне посилання, можна змінювати)
Portfolio& Investor::getPortfolio()
{
    return portfolio;
}

// Установка повних даних інвестора
void Investor::setData(const string& _fullName, double _riskTolerance,
    double _targetReturn)
{
    fullName = _fullName;
    riskTolerance = _riskTolerance;
    targetReturn = _targetReturn;

    // Перевірка на коректність значень
    if (riskTolerance > 1.0 || riskTolerance <= 0)
        throw ExceptionInvalidInvestor();

    if (targetReturn > 1.0 || targetReturn <= 0)
        throw ExceptionInvalidInvestor();
}