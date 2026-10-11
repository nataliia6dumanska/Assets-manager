#pragma once
#include "Investor.h"  

// Базовий клас стратегії оптимізації.
// Патерн Strategy: дозволяє змінювати алгоритм оптимізації під час виконання.
class OptimizationStrategy
{
public:
    // Віртуальна функція — кожна стратегія реалізує свій алгоритм.
    // Повертає масив ваг активів.
    virtual vector<double> optimize(const Investor& investor) = 0;

    // Віртуальний деструктор — потрібен для коректного видалення дочірніх класів
    virtual ~OptimizationStrategy() = default;
};


// ---- Реалізація алгоритму Марковіца ----
class MarkowitzStrategy : public OptimizationStrategy
{
public:
    vector<double> optimize(const Investor& investor) override;
};


// ---- Жадібна стратегія ----
class GreedyStrategy : public OptimizationStrategy
{
public:
    vector<double> optimize(const Investor& investor) override;
};


// ---- Кластеризаційна стратегія ----
// Об’єднує активи у кластери за ризиком / доходністю та формує портфель
class ClusteringStrategy : public OptimizationStrategy
{
public:
    vector<double> optimize(const Investor& investor) override;
};
