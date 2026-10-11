#include "OptimizationStrategy.h"
#include <algorithm>   // sort, max
#include <cmath>       // isnan, isinf, fabs, pow
#include <random>      // генератори випадкових чисел
#include <numeric>     // accumulate
#include "Exception.h"

using namespace std;


/*
    Стратегія Марковіца

    Основна ідея:
    - Інвестор хоче максимізувати дохідність
    - І одночасно мінімізувати ризик (дисперсію портфеля)
    - Використовується "градієнтний спуск" для знаходження ваг

    Функція оптимізації шукає такі weights[i], що:
        1) Σ weights[i] = 1
        2) weights[i] >= 0
        3) Очікувана дохідність близька до targetReturn
        4) Загальний ризик портфеля мінімальний

*/

vector<double> MarkowitzStrategy::optimize(const Investor& investor)
{
    // Копіюємо портфель інвестора
    Portfolio portfolio = investor.getPortfolio();
    auto assets = portfolio.getAssets();

    // Якщо портфель пустий — помилка
    if (assets.empty())
        throw ExceptionEmptyPortfolio();

    int n = assets.size();

    // Початкове наближення ваг — рівномірний розподіл
    vector<double> weights(n, 1.0 / n);

    // Цільова дохідність, яку хоче інвестор
    double targetReturn = investor.getTargetReturn();

    // Параметри оптимізації (налаштування градієнтного спуску)
    const double learningRate = 0.01;     // швидкість навчання
    const int maxIter = 10000;            // максимальна кількість ітерацій
    const double tolerance = 1e-6;        // межа зупинки

    // Вектор очікуваних доходностей для кожного активу
    vector<double> expReturns(n);
    for (int i = 0; i < n; i++)
    {
        // Очікувана історична дохідність активу
        double exReturn = assets[i].first.calculateExpectedReturn();

        expReturns[i] = exReturn;
    }

    // Матриця коваріацій між активами
    // Розмір: n × n
    vector<vector<double>> covMatrix(n, vector<double>(n, 0.0));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // Обчислення коваріації між активом i та j
            double cov = portfolio.calculateCovariance(assets[i].first, assets[j].first);
            covMatrix[i][j] = cov;
        }
    }

    /*
        Градієнтний спуск
        Мінімізуємо ризик з обмеженнями:

        Risk = Σ Σ w_i * w_j * Cov(i,j)

        Додаємо штраф за різницю між реальною та бажаною дохідністю:

        Loss = Risk - λ * (TargetReturn - PortfolioReturn) * Return_i

        λ — це riskTolerance інвестора:
            • висока riskTolerance → інвестор не боїться ризику
            • мала → більше штрафуємо за відхилення від цільового доходу
    */

    for (int iter = 0; iter < maxIter; iter++)
    {
        // ---- КРОК 1: обчислюємо поточний ризик портфеля ----
        double portfolioRisk = 0.0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                portfolioRisk += weights[i] * weights[j] * covMatrix[i][j];

        // ---- КРОК 2: обчислюємо дохідність портфеля ----
        double portfolioReturn = 0.0;
        for (int i = 0; i < n; i++)
            portfolioReturn += weights[i] * expReturns[i];

        // ---- КРОК 3: обчислюємо градієнт по кожній вазі ----
        vector<double> grad(n, 0.0);

        for (int i = 0; i < n; i++)
        {
            double gradRisk = 0.0;

            // Часткова похідна ризику по weight[i]
            for (int j = 0; j < n; j++)
                gradRisk += 2.0 * covMatrix[i][j] * weights[j];

            double lambda = investor.getRiskTolerance();

            // Фінальний градієнт:
            // враховуємо і ризик, і бажану дохідність
            grad[i] = gradRisk - lambda * (targetReturn - portfolioReturn) * expReturns[i];
        }

        // ---- КРОК 4: оновлюємо ваги ----
        for (int i = 0; i < n; i++)
        {
            // рухаємо ваги у напрямку мінімуму
            weights[i] -= learningRate * grad[i];

            // Забороняємо негативні ваги
            if (weights[i] < 0.0) weights[i] = 0.0;
        }

        // ---- КРОК 5: нормалізуємо ваги, щоб Σ w = 1 ----
        double sumW = accumulate(weights.begin(), weights.end(), 0.0);

        if (sumW <= 0.0)
            throw ExceptionWeights();

        for (auto& w : weights) w /= sumW;

        // ---- КРОК 6: умова зупинки ----
        if (fabs(portfolioReturn - targetReturn) < tolerance)
            break;
    }

    return weights;
}


/*
    GreedyStrategy — "жадібна стратегія" оптимізації портфеля.

    Основна ідея підходу:
    • Для кожного активу обчислюється його коефіцієнт Шарпа,
      тобто відношення очікуваної дохідності до ризику (стандартного відхилення).
      Чим вищий коефіцієнт Шарпа — тим ефективніший актив
      щодо співвідношення "ризик/дохідність".

    • Коефіцієнт додатково масштабується на показник riskTolerance інвестора.
      Це дозволяє інвестору з високою готовністю приймати ризик
      робити більший акцент на активи з високою дохідністю,
      навіть якщо ризик у них теж більший.

    • Після цього активи сортуються за спаданням “рейтингів”
      (Sharpe * riskTolerance), і вага кожного активу
      визначається пропорційно до цього рейтингу.

    • Якщо всі розраховані значення ≤ 0 (наприклад, всі активи збиткові),
      використовується рівномірний розподіл ваг.

    Результат:
    • Функція повертає нормований вектор weights,
      де сума всіх ваг дорівнює 1.
*/
vector<double> GreedyStrategy::optimize(const Investor& investor)
{
    // Отримуємо портфель інвестора
    Portfolio portfolio = investor.getPortfolio();
    auto assets = portfolio.getAssets();

    // Перевірка: портфель не може бути порожнім
    if (assets.empty())
        throw ExceptionEmptyPortfolio();

    int n = assets.size();

    // Вектор пар <рейтинг активу, індекс активу>
    vector<pair<double, int>> ratios;

    /*
        Проходимо всі активи портфеля та для кожного
        визначаємо його ефективність за допомогою коефіцієнта Шарпа.
    */
    for (int i = 0; i < n; i++)
    {
        // Розрахунок очікуваної дохідності активу
        double exReturn = assets[i].first.calculateExpectedReturn();

        // Розрахунок ризику активу (стандартного відхилення)
        double risk = assets[i].first.calculateRisk();

        if (risk < 0)
            throw ExceptionInvalidAsset(assets[i].first.getName());

        // Розрахунок коефіцієнта Шарпа (захист від ділення на нуль)
        double sharpe = (risk > 0.0) ? (exReturn / risk) : 0.0;

        /*
            Рейтинг активу — це коефіцієнт Шарпа,
            помножений на riskTolerance інвестора.

            Це дозволяє інвестору впливати на "жадібність":
            • якщо riskTolerance високе → акцент на прибуток;
            • якщо низьке → акцент на безпечні активи.
        */
        double ratio = sharpe * investor.getRiskTolerance();

        // Додаємо пару <рейтинг, індекс активу> у список
        ratios.emplace_back(ratio, i);
    }

    // Сортуємо активи за спаданням їх рейтингів
    sort(ratios.rbegin(), ratios.rend());

    vector<double> weights(n, 0.0);

    double total = 0.0;

    /*
        Обчислюємо суму всіх рейтингів (тільки позитивних),
        щоб можна було нормувати ваги.
    */
    for (auto p : ratios)
        total += max(0.0, p.first);

    /*
        Якщо всі рейтинги ≤ 0:
        • портфель має або надто ризикові, або збиткові активи
        • тому оптимальним рішенням є рівний розподіл ваг
    */
    if (total <= 0.0)
    {
        double equal = 1.0 / n;
        fill(weights.begin(), weights.end(), equal);
    }
    else
    {
        /*
            В іншому випадку:
            вага кожного активу пропорційна до його рейтингу
        */
        for (auto p : ratios)
            weights[p.second] = max(0.0, p.first) / total;
    }

    return weights;
}

/*
    ClusteringStrategy — стратегія оптимізації портфеля на основі кластеризації активів.

    Основна ідея:
    1) Розраховується матриця кореляцій між усіма активами.
    2) Виконується спрощена кластеризація на k кластерів (k = 3 або менше, якщо активів менше).
    3) В межах кожного кластера обчислюється середня дохідність та ризик.
    4) Ваги активів розподіляються між кластерами пропорційно ефективності (дохід/ризик).
    5) Якщо розрахунки неможливі (всі ризики ≤ 0), використовується рівномірний розподіл.

    Повертає нормований вектор ваг, сума = 1.
*/
vector<double> ClusteringStrategy::optimize(const Investor& investor)
{
    // Отримуємо портфель та активи
    Portfolio portfolio = investor.getPortfolio();
    auto assets = portfolio.getAssets();

    if (assets.empty())
        throw ExceptionEmptyPortfolio(); // перевірка на порожній портфель

    int n = assets.size();
    int k = min(3, n); // обмежуємо кількість кластерів до 3

    // Матриця кореляцій між активами
    vector<vector<double>> corrMatrix(n, vector<double>(n, 0.0));
    vector<double> stdDevs(n); // стандартні відхилення (ризик) для кожного активу

    // Обчислюємо ризики активів
    for (int i = 0; i < n; i++)
    {
        double risk = assets[i].first.calculateRisk();
        if (risk <= 0.0)
            throw ExceptionInvalidAsset(assets[i].first.getName()); // актив з некоректним ризиком
        stdDevs[i] = risk;
    }

    // Обчислення матриці кореляцій
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            double cov = portfolio.calculateCovariance(assets[i].first, assets[j].first); // коваріація
            double corr = (stdDevs[i] > 0 && stdDevs[j] > 0) ? cov / (stdDevs[i] * stdDevs[j]) : 0.0;
            if (isnan(corr)) // обробка невизначених значень
                corr = 0.0;
            corrMatrix[i][j] = corrMatrix[j][i] = corr; // симетрична матриця
        }
    }

    // Ініціалізація центроїдів для кластерів випадковим чином
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> dist(0, n - 1);
    vector<vector<double>> centroids;
    centroids.push_back(corrMatrix[dist(rng)]);

    // Ініціалізація k центроїдів (спрощена версія k-means++)
    while (centroids.size() < k)
    {
        double maxDist = -1.0;
        int bestIdx = 0;
        for (int i = 0; i < n; i++)
        {
            double minDist = numeric_limits<double>::max();
            for (auto& c : centroids)
            {
                double d = 0;
                for (int j = 0; j < n; j++)
                    d += pow(corrMatrix[i][j] - c[j], 2); // квадрат евклідової відстані
                minDist = min(minDist, d);
            }
            if (minDist > maxDist)
            {
                maxDist = minDist; // знаходимо найбільш віддалений актив
                bestIdx = i;
            }
        }
        centroids.push_back(corrMatrix[bestIdx]); // додаємо новий центроїд
    }

    // Ініціалізація кластерів
    vector<int> cluster(n, -1);

    // Основний цикл кластеризації (100 ітерацій або поки класифікація не стабільна)
    for (int iter = 0; iter < 100; iter++)
    {
        bool changed = false;
        for (int i = 0; i < n; i++)
        {
            double bestDist = 1e9;
            int bestC = 0;
            for (int c = 0; c < k; c++)
            {
                double d = 0;
                for (int j = 0; j < n; j++)
                    d += pow(corrMatrix[i][j] - centroids[c][j], 2); // відстань до центроїду
                if (d < bestDist)
                {
                    bestDist = d;
                    bestC = c;
                }
            }
            if (cluster[i] != bestC)
            {
                cluster[i] = bestC; // призначення активу до кластеру
                changed = true;
            }
        }
        if (!changed) break; // зупинка, якщо кластери не змінилися

        // Оновлення центроїдів
        vector<vector<double>> newC(k, vector<double>(n, 0.0));
        vector<int> count(k, 0);
        for (int i = 0; i < n; i++)
        {
            int c = cluster[i];
            count[c]++;
            for (int j = 0; j < n; j++)
                newC[c][j] += corrMatrix[i][j];
        }
        for (int c = 0; c < k; c++)
            if (count[c] > 0)
                for (int j = 0; j < n; j++)
                    centroids[c][j] = newC[c][j] / count[c]; // середнє значення для кожного центроїду
    }

    // Розподіл ваг активів
    vector<double> weights(n, 0.0);
    vector<double> clusterWeights(k, 0.0);
    double total = 0.0;

    for (int c = 0; c < k; c++)
    {
        vector<int> members;
        for (int i = 0; i < n; i++)
            if (cluster[i] == c)
                members.push_back(i); // активи цього кластеру
        if (members.empty()) continue;

        double avgR = 0, avgRisk = 0;
        for (int i : members)
        {
            avgR += assets[i].first.calculateExpectedReturn();
            avgRisk += assets[i].first.calculateRisk();
        }
        avgR /= members.size();
        avgRisk /= members.size();

        // Розрахунок ефективності кластера (доход/ризик)
        clusterWeights[c] = (avgRisk > 0.0) ? avgR / avgRisk : 0.0;
        total += clusterWeights[c];
    }

    // Нормалізація та розподіл ваг всередині кластерів
    if (total > 0)
    {
        for (int c = 0; c < k; c++)
        {
            vector<int> members;
            for (int i = 0; i < n; i++)
                if (cluster[i] == c)
                    members.push_back(i);
            //double wPerAsset = (clusterWeights[c] / total) / members.size();
            double wPerAsset = (clusterWeights[c] / total) / max(1, (int)members.size());
            for (int i : members)
                weights[i] = wPerAsset;
        }
    }
    else
    {
        // Якщо ефективність всіх кластерів = 0 → рівномірний розподіл
        double equal = 1.0 / n;
        fill(weights.begin(), weights.end(), equal);
    }

    return weights; // повертаємо нормовані ваги
}

