// Included packages
#include <string>
#include <iostream>
#include <sstream>

// Classes

// Functions

// Simple function to check if every character in a string is a digit, and optionally if it is within bounds
void input_int_check(std::string &str, int lowerbound=0, int upperbound=INT_MAX){

bool is_int=false, lb=false, ub=false;
int sum;

// Don't test upper or lower bounds if they are INT_MAX or 0 respectively
if (lowerbound==0) lb=true;
if (upperbound==INT_MAX) ub=true;

    // Assumes all checks are false
    while (is_int==false || lb==false || ub==false){

        // Checks if any character currently isn't a digit
        sum=0;
        for (int i=0; i<str.length(); i++){
            if (isdigit(str[i])) sum++;
        };

        if (sum==str.length()){
            is_int=true;
        } else{
            std::cout << "Failed, please ensure value is a positive integer: ";
            getline(std::cin, str);
            continue;
        };

        // Checks the lower bound
        if (is_int==true && lb==false){
            if (stoi(str)>=lowerbound){
                lb=true;
            } else {
                std::cout << "Failed, please ensure value is greater than or equal to " << lowerbound << ": ";
                getline(std::cin, str);
                continue;
            };
        };

        // Checks the upper bound
        if (is_int==true && ub==false){
            if (stoi(str)<=upperbound){
                ub=true;
            } else {
                std::cout << "Failed, please ensure value is less than or equal to " << upperbound << ": ";
                getline(std::cin, str);
                continue;
            };
        };

    };

};

void input_lt(std::string str){

}

int main () {

// Get the player to enter their name
std::string name;

std::cout << "Please enter your name: " ;
getline(std::cin, name);

std::cout << "Welcome to Baccarat, " << name << "!" << std::endl;
std::cout << "======================================" << std::endl;

// Variables
// Initial money set to 10000
int bet, bet_amount, money=10000;
bool again=true;
std::string mystr;

////
// Bets
////

while (again){

    // Initial bet inputs
    std::cout << "1 - Banker" << "\n" << "2 - Player" << "\n" << "Choose your bet, 1 or 2: ";
    getline(std::cin, mystr);

    input_int_check(mystr, 1, 2);
    bet=std::stoi(mystr);

    std::cout << "Current money is £" << money << std::endl;
    std::cout << "Enter a bet amount in whole pounds: ";
    getline(std::cin, mystr);

    input_int_check(mystr, 1, money);
    bet_amount=std::stoi(mystr);

    // Ask the player to play again
    if (money>0) std::cout << "Do you wish to try your luck again? y/n: ";
    getline(std::cin, mystr);

    while (mystr!="y" && mystr!="Y" && mystr!="n" && mystr!="N"){
        std::cout << "Please enter either y or n: ";
        getline(std::cin, mystr);
    };

    if (mystr=="n" || mystr=="N") {
        again=false;
        std::cout << "Thanks for playing!" << std::endl;
    };
};

}