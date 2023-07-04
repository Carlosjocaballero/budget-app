// Command to run g++ main.cpp -lmysqlcppconn -lmysqlcppconn-static

#include "../include/pch.h"
#include "SQLUtils.cpp"
#include "BudgetApp.cpp"

void newEntry(BudgetApp &app) {
    std::string date = "";
    std::cout << "\nWhen is the entry for?" << std::endl;
    bool loop = true;
    while(loop){
        std::cout << "1.Today\t2.Custom Date" << std::endl;
        int usr_choice;
        std::cin >> usr_choice;
        switch(usr_choice){
            case 1:
                loop = false;
                break;
            case 2:
                std::cout << "Please write the date (year/month/day): ";
                std::cin >> date;
                loop = false;
                break;
            default:
                std::cout << usr_choice << " is not a choice. Please choose again.\n";
                break;
        }
    }
    if(date == ""){
        std::cout << "no date was chosen" << std::endl;
    }
    else{
        std::cout << "Date: " << date << std::endl;
    }
}

void editEntry(BudgetApp &app) {

}

void viewHistory(BudgetApp &app) {
    app.read_all();
}

int main(void)
{
    BudgetApp app;
    std::cout << "\nWelcome to your Budgeting!\n" << std::endl;
    std::cout << "What would you like to do today?\n" << std::endl;
    bool exit = false; std::string leave;
    while(!exit){
        std::cout << "1.New Entry\t2.Edit Entry\t3.View History\t4.Exit" << std::endl;
        int usr_choice;
        std::cin >> usr_choice;
        switch(usr_choice){
            case 1:
                newEntry(app);
                std::cout << "\nIs that all? (Y/N) ";
                std::cin >> leave;
                if(leave == "Y"){
                    exit = true;
                }
                else{std::cout << std::endl;}
                break;
            case 2:
                editEntry(app);
                std::cout << "\nIs that all? (Y/N) ";
                std::cin >> leave;
                if(leave == "Y"){
                    exit = true;
                }
                else{std::cout << std::endl;}
                break;
            case 3:
                viewHistory(app);
                std::cout << "\nIs that all? (Y/N) ";
                std::cin >> leave;
                if(leave == "Y"){
                    exit = true;
                }
                else{std::cout << std::endl;}
                break;
            case 4:
                return EXIT_SUCCESS;
            default:
                std::cout << std::endl << usr_choice << " is not an option. Choose again.\n" << std::endl;
        }
    }
    return EXIT_SUCCESS;
}

