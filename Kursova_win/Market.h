#pragma once
#include "Asset.h"
#include <vector>
#include <random>    // засоби генерації випадкових чисел (mt19937, normal_distribution)
#include <iostream>
#include <cstdlib>   // rand()
#include <string>

class Market
{
private:
    // Вектор усіх активів, завантажених із файлу
    vector<Asset> availableAssets;

public:
    // Завантаження активів з TXT-файлу
    void loadFromFile(const string& filename);

    // Повертає список доступних активів 
    const vector<Asset>& getAvailableAssets() const;

    // Симулює один крок зміни ринку та оновлює доходності активів
    string simulateMarketScenario(vector<pair<Asset, double>>& currentAssets);

    // Типи можливих ринкових сценаріїв
    enum ScenarioType { CRISIS, GROWTH, STABLE };

    // Випадковий вибір сценарію CRISIS/GROWTH/STABLE
    ScenarioType getRandomScenario();

    ~Market() = default;
};
