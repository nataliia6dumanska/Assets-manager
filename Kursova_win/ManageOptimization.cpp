#include "ManageOptimization.h"

void ManageOptimization::setStrategy(OptimizationStrategy* newStrategy)
{
    // Змінюємо активну стратегію на нову.
    // Користувач повинен передати об'єкт, який реалізує OptimizationStrategy.
    strategy = newStrategy;
}

vector<double> ManageOptimization::optimizePortfolio(const Investor& investor)
{
    // Виклик методу оптимізації через активну стратегію.

    vector<double> weights = strategy->optimize(investor);

    return weights;  // Повертаємо ваги активів після оптимізації
}
