// Command to run sudo 

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
        std::cout << "1.Today    2.Custom Date" << std::endl;
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

float getTotalPay(){
    std::cout << "\nWhat is the total pay amount? ";
    float total;
    std::cin >> total;
    return total;
}

std::string getIncomeType(){
    bool loop = true;
    std::string incomeType;
    std::string custom_choice;
    while(loop){
        // Get user choice
        std::cout << "\nWhat kind of income amount would you want to make?"<< std::endl;
        std::cout << "1.Semi-weekly    2.Monthly    3.Custom" << std::endl;
        int usr_choice;
        std::cin >> usr_choice;

        // Execute choice
        switch(usr_choice){
            case 1:
                incomeType = "semi-weekly";
                loop = false;
                break;
            case 2:
                incomeType = "monthly";
                loop = false;
                break;
            case 3:
                std::cout << "\n What custom name would you want to apply to this income: ";
                std::cin >> custom_choice;
                incomeType = custom_choice;
                loop = false;
                break;
            default:
                std::cout << usr_choice << " is not an option, please choose again.\n" << std::endl;
                break;
        }
    }
    return incomeType;
}

float usePercentage(float percentage, float remainingTotal){
    
    return 0.0;
}

void calculator(){
    std::cout << "\n----- PERCENTAGE CALCULATOR -----" << std::endl;
    bool exit = false;
    int usr_choice;
    float a,b;
    while(!exit){
        std::cout << "\nPlease choose one of the following: \n" << std::endl;
        std::cout << "1. What is (a)_____% of (b)_____\t2. (a)_____ is what percentage of (b)_____\t3. Exit"<< std::endl;
        std::cin >> usr_choice;

        switch(usr_choice){
            case 1: {
                std::cout << "\na: ";
                std::cin >> a;
                std::cout << "b: ";
                std::cin >> b;
                if(a > 100){
                    std::cout << "Percentage cannot be bigger than 100" << std::endl;
                    break;
                }
                float calculation = b * (a / 100);
                std::cout << std::endl << calculation << " is " << a << "% of " << b << std::endl;
            } break;
            case 2: {
                std::cout << "\na: ";
                std::cin >> a;
                std::cout << "b: ";
                std::cin >> b;
                if(a > b){
                    std::cout << "a cannot be bigger than b" << std::endl;
                    break;
                }
                float percentage = (a * 100) / b;
                std::cout << std::endl << a << " is " << percentage << "% of " << b << std::endl; 
            } break;
            case 3:
                exit = true;
                break;
            default:
                std::cout << usr_choice << " is not an option, please choose again.\n" << std::endl;
                break;
        }


    }   
}

void newEntry(BudgetApp &app) {
    std::string date = getValidDate();
    float totalPay = getTotalPay();
    std::string incomeType = getIncomeType();
    
    std::vector<std::string> transactions = {"home", "expenses", "spending", "savings"};
    int usr_choice{0}, conversionType;
    float remainingTotal = totalPay;
    // Key: transaction type | value: Transaction amount
    std::unordered_map<std::string, float> budget;
    float amountChosen, amountCalculated;

    std::cout << std::endl;
    while(budget.size() != 4){
        if(usr_choice == 0){
            std::cout << "Which one would you want to budget? " << std::endl;
            for(int i = 0; i < transactions.size(); i++){
                std::cout << i+1 << "." << transactions[i] << "   ";
            }
            std::cout << std::endl;
            std::cin >> usr_choice;
        }

        
        std::cout << std::endl <<  transactions[usr_choice - 1] << ": Would you want to budget in percentage or money amount? " << std::endl;
        std::cout << "1.Percentage    2.Money Amount    3. Percentage Calculator" << std::endl;
        std::cin >> conversionType;

        switch(conversionType){
            case 1:
                std::cout << "\nHow much percentage? " << std::endl;
                std::cin >> amountChosen;
                amountCalculated = usePercentage(amountChosen, remainingTotal);
                budget[transactions[usr_choice - 1]] = amountCalculated;
                transactions.erase(std::remove(transactions.begin(), transactions.end(), transactions[usr_choice - 1]), transactions.end());
                usr_choice = 0;
                break;
            case 2:
                std::cout << "\nHow much money amount? " << std::endl;
                std::cin >> amountChosen;
                budget[transactions[usr_choice - 1]] = amountChosen;
                break;
            case 3:
                calculator();
                break;
            default:
                std::cout << "Choice not avaliable. Please choose again. \n" << std::endl;
                break;
        }

    }

    std::cout << "\nDate: " << date << std::endl;
    std::cout << "Total Pay: " << totalPay << std::endl;
    std::cout << "Income type: " << incomeType << std::endl;
    for(auto type : budget){
        std::cout << type.first <<": " << type.second << std::endl;
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
        std::cout << "1.New Entry    2.Edit Entry    3.View History    4.Exit" << std::endl;
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

