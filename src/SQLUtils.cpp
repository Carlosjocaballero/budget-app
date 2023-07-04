#include "../include/SQLUtils.h"

std::string SQLUtils::getConnectionPassword(){
    std::string pwd;
    std::fstream file;
    // open a file to perform read operation using file object
    file.open("../pwd.txt", std::ios::in);
    if (!file.is_open())
    {
        std::cout << "Need password to connect to MySQL" << std::endl;
    }
    else
    {
        std::getline(file, pwd);
    }
    return pwd;
}

sql::mysql::MySQL_Driver *SQLUtils::getMySQLDriver(){
    return sql::mysql::get_mysql_driver_instance();
}

sql::Connection *SQLUtils::createConnection(sql::mysql::MySQL_Driver *driver, const std::string &host, const std::string &username, const std::string &pwd, const std::string &database){
    sql::Connection *con;
    con = driver->connect(host, username, pwd);
    con->setSchema(database);

    return con;
}

void SQLUtils::read_all()
{
    try
    {
        // Create a connection
        sql::mysql::MySQL_Driver *driver = getMySQLDriver();
        std::string pwd = getConnectionPassword();
        sql::Connection *con = createConnection(driver, "tcp://127.0.0.1:3306", "root", pwd, "infodb");

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
        delete res;
        delete stmt;
        delete con;
    }
    catch (sql::SQLException &e)
    {
        std::cout << "# ERR: SQLException in " << __FILE__;
        std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
        std::cout << "# ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }
}

// std::cout << std::endl;
//     std::cout << "Running 'SELECT 'Hello World!' AS _message'..." << std::endl;

//     try{
//         sql::Driver *driver;
//         sql::Connection *con;
//         sql::Statement *stmt;
//         sql::ResultSet *res;

//         /* Create a connection */
//         driver = get_driver_instance();
//         // get password
//         std::string pwd = getDriverPassword();
//         con = driver->connect("tcp://127.0.0.1:3306","root",pwd);

//         /* Connect to the MySQL test database*/
//         con->setSchema("infodb");

//         stmt = con->createStatement();
//         res = stmt->executeQuery("SELECT * FROM incomehistory;");
//         while(res->next()){
//             std::cout << "\t... mySQL says it again: ";
//             /* Acess column data by numeric offset, 1 is the first column */
//             std::cout << res->getString(2) << std::endl;
//         }
//         delete res;
//         delete stmt;
//         delete con;
//     } catch (sql::SQLException &e){
//         std::cout << "# ERR: SQLException in " << __FILE__;
//         std::cout <<  "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
//         std::cout << "# ERR: " << e.what();
//         std::cout << " (MySQL error code: " << e.getErrorCode();
//         std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
//     }