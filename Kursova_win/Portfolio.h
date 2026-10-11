#pragma once
#include "Asset.h"

// Клас Portfolio представляє інвестиційний портфель, що складається з активів
// та ваг (часток кожного активу в портфелі).
class Portfolio
{
private:
    // assets — вектор пар: (Asset, weight)
    vector<pair<Asset, double>> assets;

public:
    Portfolio();
    Portfolio(vector<pair<Asset, double>> _assets, vector<double> _weights);
    //Додавання нового активу
    void addAsset(const Asset& asset, double weight); 
    // Отримання списку активів (константна і неконстантна версія)
    const vector<pair<Asset, double>> getAssets() const;
    vector<pair<Asset, double>>& getAssets();

    // Отримання лише ваг активів
    const vector<double> getWeights() const;

    // Розрахунок загальної очікуваної доходності портфеля
    double calculateExpectedReturnPortfolio() const;

    // Обчислення коваріації між двома активами
    double calculateCovariance(const Asset& i, const Asset& j) const;

    // Розрахунок ризику портфеля (стандартне відхилення)
    double calculateRiskPortfolio() const;

    // Встановлення активів та ваг портфеля
    void setAssets(const vector<Asset>& a);
    void setWeights(const vector<double>& w);
};