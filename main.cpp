// Command to run g++ main.cpp -lmysqlcppconn -lmysqlcppconn-static

/* Standard C++ Libraries*/
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

/* mySQL Connector Libraries */
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>


/**
 * @brief Get the Driver Password
 * @return The correct password if the password text file is in directory, blank string if not
 */
std::string getDriverPassword(){
    std::string pwd;
    std::fstream file;
    // open a file to perform read operation using file object
    file.open("pwd.txt", std::ios::in); 
    if(!file.is_open()){
        std::cout << "Need password to connect to MySQL" << std::endl;
    }
    else{
        std::getline(file, pwd);
    }
    return pwd;
}

int main(void){
    std::cout << std::endl;
    std::cout << "Running 'SELECT 'Hello World!' AS _message'..." << std::endl;

    try{
        sql::Driver *driver;
        sql::Connection *con;
        sql::Statement *stmt;
        sql::ResultSet *res;

        /* Create a connection */
        driver = get_driver_instance();
        // get password
        std::string pwd = getDriverPassword();
        con = driver->connect("tcp://127.0.0.1:3306","root",pwd);


        /* Connect to the MySQL test database*/
        con->setSchema("infodb");

        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * FROM incomehistory;");
        while(res->next()){
            std::cout << "\t... mySQL says it again: ";
            /* Acess column data by numeric offset, 1 is the first column */
            std::cout << res->getString(2) << std::endl;
        }
        delete res;
        delete stmt;
        delete con;
    } catch (sql::SQLException &e){
        std::cout << "# ERR: SQLException in " << __FILE__;
        std::cout <<  "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
        std::cout << "# ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }


  
  return EXIT_SUCCESS;
}