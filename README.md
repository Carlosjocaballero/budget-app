# budget-app
For a while now I have been budgeting every paycheck manually. But why? With this application I plan to automate the process. 

## How to run
In Ubuntu install the MySQL Connector/C++ library with the following command
```bash
sudo apt-get install  libmysqlcppconn-dev
```
To execute, use the following command
```bash
g++ main.cpp -lmysqlcppconn -lmysqlcppconn-static && ./a.out
```
