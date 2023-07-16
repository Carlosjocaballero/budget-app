#pragma once

#include "SQLUtils.h"

class BudgetApp{ 
    public:
        BudgetApp();
        ~BudgetApp();
        void read_all();
        void insert(std::string date_recorded, std::string income_type, float total_income, float home, float home_percentage, float expenses, float expenses_percentage, float spending, float spending_percentage, float savings, float savings_percentage);
    private:
        sql::mysql::MySQL_Driver *driver;
        sql::Connection *con;
};