#pragma once
#include "OptimizationStrategy.h"  
// Підключення базового інтерфейсу стратегій оптимізації.
// Потрібно, щоб використовувати вказівник на стратегію (патерн Strategy).

class ManageOptimization
{
private:
    // Може вказувати на MarkowitzStrategy, GreedyStrategy або ClusteringStrategy.
    OptimizationStrategy* strategy;

public:
    // Встановлює стратегію (динамічно обирається під час виконання програми)
    void setStrategy(OptimizationStrategy* newStrategy);

    // Викликає оптимізацію через обрану стратегію.
    vector<double> optimizePortfolio(const Investor& investor);
};
