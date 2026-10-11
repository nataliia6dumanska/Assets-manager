#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Asset
{
private:
    string name;    // Назва активу
    string type;    // Тип активу (наприклад: акція, облігація тощо)
    double price;   // Поточна ціна активу
    vector<double> historicalReturns; // Історичні доходності 

public:
    Asset();
    Asset(const string& _name, const string& _type, const double& _price,
        const vector<double>& _historacalReturns);

    // Обчислення очікуваної доходності (середнє історичних значень)
    double calculateExpectedReturn() const;

    // Обчислення ризику активу (дисперсія та корінь з неї)
    double calculateRisk() const;

    // Гетери для приватних полів
    const double getPrice() const;
    const vector<double> getHistoricalReturns() const;
    const string getName() const;
    const string getType() const;

    // Сеттер для оновлення історичних доходностей
    void setHistoricalReturns(const vector<double>& h);
};