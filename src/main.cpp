// Command to run g++ main.cpp -lmysqlcppconn -lmysqlcppconn-static

#include "../include/pch.h"
#include "SQLUtils.cpp"

/**
 * @brief Get the Driver Password
 * @return The correct password if the password text file is in directory, blank string if not
 */
std::string getConnectionPassword()
{
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

int main(void)
{
    SQLUtils sql;
    sql.read_all();
    return EXIT_SUCCESS;
}