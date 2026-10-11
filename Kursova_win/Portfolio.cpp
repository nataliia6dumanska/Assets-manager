#include <iostream>  
#include "Exception.h"  
#include "Portfolio.h"

using namespace std;

Portfolio::Portfolio() : assets(0) {}

// Конструктор із списку активів і списку ваг
Portfolio::Portfolio(vector<pair<Asset, double>> _assets, vector<double> _weights)
{
    if (_assets.empty())
    {
        throw ExceptionEmptyPortfolio();
    }

    if (_assets.size() != _weights.size())
    {
        // Кількість ваг != кількості активів
        throw ExceptionAWMismatch();
    }

    // Призначаємо вага[i] - актив[i]
    for (int i = 0; i < _assets.size(); i++)
    {
        assets.push_back({ _assets[i].first, _weights[i] });
    }
}
// Додаємо новий актив
void Portfolio::addAsset(const Asset& asset, double weight)
{
    if (weight > 1.0 || weight < 0.0) throw ExceptionWeights();
    assets.emplace_back(asset, weight);
}

const vector<pair<Asset, double>> Portfolio::getAssets() const
{
    return assets;
}

vector<pair<Asset, double>>& Portfolio::getAssets()
{
    return assets;
}

const vector<double> Portfolio::getWeights() const
{
    vector<double> weights;
    for (auto asset : assets)
    {
        weights.push_back(asset.second);
    }
    return weights;
}

// Очікувана доходність портфеля:
// Σ(weight_i * expected_return_i)
double Portfolio::calculateExpectedReturnPortfolio() const
{
    if (assets.empty())
    {
        throw ExceptionEmptyPortfolio();
    }

    double expectedReturn = 0.0;
    for (auto& it : assets)
    {
        expectedReturn += it.first.calculateExpectedReturn() * it.second;
    }
    return expectedReturn;
}

// Коваріація між двома активами
double Portfolio::calculateCovariance(const Asset& i, const Asset& j) const
{
    int n = i.getHistoricalReturns().size();
    int m = j.getHistoricalReturns().size();

    if (m != n)
    {
        // ExceptionHRMismatch — різна кількість історичних значень
        throw ExceptionHRMismatch();
        return 0.0;
    }

    double cov = 0;
    double meanI = 0, meanJ = 0;

    // Обчислення середніх значень
    for (int k = 0; k < n; k++)
    {
        meanI += i.getHistoricalReturns()[k];
        meanJ += j.getHistoricalReturns()[k];
    }
    meanI /= n;
    meanJ /= n;

    // Формула коваріації Σ( (xi-meanI)*(xj-meanJ) ) / n
    for (int k = 0; k < n; k++)
    {
        cov += (i.getHistoricalReturns()[k] - meanI) *
            (j.getHistoricalReturns()[k] - meanJ);
    }
    return cov / n;
}

// Ризик портфеля: sqrt( wᵀ * COV * w )
double Portfolio::calculateRiskPortfolio() const
{
    if (assets.empty())
    {
        throw ExceptionEmptyPortfolio();
    }

    int n = assets.size();

    // Побудова матриці коваріації
    vector<vector<double>> covMatrix(n, vector<double>(n, 0.0));

    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            double cov = calculateCovariance(assets[i].first, assets[j].first);

            // Матриця симетрична
            covMatrix[i][j] = cov;
            covMatrix[j][i] = cov;
        }
    }

    // Обчислення дисперсії портфеля: ΣΣ wi * wj * cov(i,j)
    double variance = 0.0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            variance += assets[i].second * assets[j].second * covMatrix[i][j];
        }
    }

    return sqrt(variance);
}

// Заміна всіх активів портфеля (зберігаючи ваги)
void Portfolio::setAssets(const vector<Asset>& a)
{
    for (int i = 0; i < assets.size(); ++i)
    {
        assets[i].first = a[i];
    }
}

// Заміна всіх ваг портфеля
void Portfolio::setWeights(const vector<double>& w)
{
    if (w.size() != assets.size()) throw ExceptionWeights(); 
    for (int i = 0; i < assets.size(); ++i)
    {
        assets[i].second = w[i];
    }
}