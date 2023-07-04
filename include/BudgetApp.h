#pragma once

#include "SQLUtils.h"

class BudgetApp{ 
    public:
        BudgetApp();
        ~BudgetApp();
        void read_all();
        
    private:
        sql::mysql::MySQL_Driver *driver;
        sql::Connection *con;
};