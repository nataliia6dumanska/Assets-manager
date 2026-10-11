#pragma once
#include "Portfolio.h"
#include "Exception.h"

// Клас Investor представляє користувача
class Investor
{
private:
    string fullName;        // Ім'я інвестора
    double riskTolerance;   // Толерантність до ризику (0 < x ≤ 1)
    double targetReturn;    // Бажана доходність (0 < x ≤ 1)
    Portfolio portfolio;    // Портфель активів інвестора

public:
    Investor();
    Investor(const string& _fullName, double _riskTolerance,
        double _targetReturn);

    // Метод для встановлення/оновлення полів інвестора
    void setData(const string& _fullName, double _riskTolerance,
        double _targetReturn);

    // Гетери
    const double getTargetReturn()const;
    const string& getFullName()const;
    const double getRiskTolerance()const;
    const Portfolio& getPortfolio()const;
    Portfolio& getPortfolio();
};

