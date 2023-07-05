// Command to run g++ main.cpp -lmysqlcppconn -lmysqlcppconn-static

#include "../include/pch.h"
#include "SQLUtils.cpp"
#include "BudgetApp.cpp"

bool validateDate(std::string date){
    if(date.size() == 0) return false;
    // Get the different parts of the date
    std::vector<std::string> dateDetails;
    int begin{0};
    for(int i = 0; i < date.size(); i++){
        if(date[i] == '-'){
            // Push back year, month and date
            dateDetails.push_back(date.substr(begin, i - begin));
            begin = i + 1;
        }
        if(i == date.size() - 1){
            // Push back the last part (the day)
            dateDetails.push_back(date.substr(begin));
        }
    }

    int year = std::stoi(dateDetails[0]);
    int month = std::stoi(dateDetails[1]);
    int day = std::stoi(dateDetails[2]);
    bool valid = false;

    if(year < 1900 || year > 9999){ 
        std::cout << "Year is not valid!" << std::endl;
        return false; 
    }
    if(month < 0 || month > 12){ 
        std::cout << "Month is not valid!" << std::endl;
        return false; 
    }
    if(day < 0 || day > 31) { 
        std::cout << "Day is not valid!" << std::endl;
        return false; 
    }
    return true;
}

std::string getValidDate(){
    std::string date = "";
    std::cout << "\nWhen is the entry for?" << std::endl;
    bool loop{true}, dateBool{true};

    while(loop){
        std::cout << "1.Today\t2.Custom Date" << std::endl;
        int usr_choice;
        std::cin >> usr_choice;
        switch(usr_choice){
            case 1:
                loop = false;
                break;
            case 2:
                while(dateBool){
                    std::cout << "\nPlease write the date (year-month-day): ";
                    std::cin >> date;
                    if(validateDate(date)){
                        dateBool = false;
                        break;
                    }
                    std::cout << date << " is not a valid date.\n" << std::endl;
                }
                loop = false;
                break;
            default:
                std::cout << usr_choice << " is not a choice. Please choose again.\n";
                break;
        }
    }
    return date;
}

int getTotalPay(){
    std::cout << "\nWhat is the total pay amount? ";
    int total;
    std::cin >> total;
    return total;
}

void newEntry(BudgetApp &app) {
    std::string date = getValidDate();
    int totalPay = getTotalPay();


    std::cout << "\nDate: " << date << std::endl;
    std::cout << "Total Pay: " << totalPay << std::endl;
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
                std::cout << "\n\nIs that all? (Y/N) ";
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

