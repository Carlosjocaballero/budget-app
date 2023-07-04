#pragma once
#include "pch.h"

/* mySQL Connector Libraries */
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

class SQLUtils
{
public:
    /**
     * @brief Get the Connection Password string
     * 
     * @return Correct password if correct txt exists, empty string if not
     */
    std::string getConnectionPassword();

    /**
     * @brief Get MySQL Driver object
     * @return Pointer to the mySQL driver
     */
    sql::mysql::MySQL_Driver *getMySQLDriver();

    /**
     * @brief Create a Connection object
     * 
     * @param driver Pointer to the mySQL driver
     * @param host Name of the host (typically "tcp://127.0.0.1:3306")
     * @param username Name of the username (typically "root")
     * @param pwd Password for the connection
     * @param database Name of the database
     * @return Pointer to the mySQL connection  
     */
    sql::Connection *createConnection(sql::mysql::MySQL_Driver *driver, const std::string &host, const std::string &username, const std::string &pwd, const std::string &database);

    
    void read_all();
};