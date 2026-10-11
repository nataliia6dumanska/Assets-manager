#pragma once

#include "Investor.h"
#include <stdexcept>

/*
    ExceptionIO
    Використовується у випадку проблем із доступом до файлів
    Наслідує runtime_error, бо це помилка, що виникає під час виконання програми.
*/
class ExceptionIO : public runtime_error
{
public:
    explicit ExceptionIO() : runtime_error("Error: Cannot open the file") {}
};

/*
    ExceptionWeights
    Викликається, коли передані некоректні ваги
    Наслідує logic_error, бо це логічна помилка у даних користувача.
*/
class ExceptionWeights : public logic_error
{
public:
    explicit ExceptionWeights() : logic_error("Error: Invalid weights values") {}
};

/*
    ExceptionEmptyPortfolio
    Викликається, коли портфель інвестора порожній.
*/
class ExceptionEmptyPortfolio : public logic_error
{
public:
    explicit ExceptionEmptyPortfolio() : logic_error("Error: Portfolio is empty") {}
};

/*
    ExceptionHRMismatch
    HR = Historical Returns.
    Викликається при розрахунках коваріації чи кореляції, коли:
    - вектор історичних доходностей для активів має різну довжину
    - обчислення неможливе через некоректні дані
*/
class ExceptionHRMismatch : public logic_error
{
public:
    ExceptionHRMismatch()
        : logic_error("Error: Historical return vectors have mismatched lengths") { }
};

/*
    ExceptionAWMismatch
    AW = Assets - Weights.
    Викликається, коли:
    - кількість ваг != кількості активів
*/
class ExceptionAWMismatch : public logic_error
{
public:
    ExceptionAWMismatch()
        : logic_error("Error: Assets and weights vectors have mismatched lengths") {  }
};

/*
    ExceptionInvalidAsset
    Викликається, коли актив має неправильні дані.
    Додає назву активу в повідомлення для точнішої діагностики.
*/
class ExceptionInvalidAsset : public logic_error
{
public:
    explicit ExceptionInvalidAsset(const string& name)
        : logic_error("Error: Invalid data for asset: " + name) { }
};

/*
    ExceptionInvalidInvestor
    Викликається, коли інвестору передані некоректні параметри:
    - riskTolerance <= 0 або > 1
    - targetReturn <= 0 або > 1
    - відсутні або некоректні дані
*/
class ExceptionInvalidInvestor : public logic_error
{
public:
    explicit ExceptionInvalidInvestor()
        : logic_error("Error: Invalid data for Investor") { }
};
