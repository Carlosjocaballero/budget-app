#include "../include/BudgetApp.h"
#include "../include/SQLUtils.h"

BudgetApp::BudgetApp(){
    SQLUtils sql;
    try{
        driver = sql.getMySQLDriver();
        std::string pwd = sql.getConnectionPassword();
        con = sql.createConnection(driver, "tcp://127.0.0.1:3306", "root", pwd, "infodb");

    } catch (sql::SQLException &e)
    {
        std::cout << "# ERR: SQLException in " << __FILE__;
        std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
        std::cout << "# ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }
}

BudgetApp::~BudgetApp(){
    delete driver;
    delete con;
}

void BudgetApp::read_all(){
    sql::Statement *stmt;
    sql::ResultSet *res;

    stmt = con->createStatement();
    res = stmt->executeQuery("SELECT * FROM incomehistory;");

    // Get the metadata of the result set
    sql::ResultSetMetaData *metaData = res->getMetaData();
    int columnCount = metaData->getColumnCount();

    while(res->next()){
        // Iterate over each column in the row
        for(int i = 1; i <= columnCount; i++){
            std::string columnName = metaData->getColumnName(i);
            std::string columnValue = res->getString(i);
            
            // Print column name and value
            std::cout << columnName << ": " << columnValue << std::endl;
        }
    }
}
