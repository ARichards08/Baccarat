// Included packages
#include <string>
#include <iostream>
#include <vector>
#include <ctime>

// Classes
class card{
    public:

        int value_by_name(std::string str){
            if (name=="ace"){
                return 1;
            } else if(name=="two"){
                return 2;
            } else if(name=="three"){
                return 3;
            } else if(name=="four"){
                return 4;
            } else if(name=="five"){
                return 5;
            } else if(name=="six"){
                return 6;
            } else if(name=="seven"){
                return 7;
            } else if(name=="eight"){
                return 8;
            } else if(name=="nine"){
                return 9;
            } else{
                return 10;
            };
        };

        void set_name(std::string str){
            name=str;
            value=value_by_name(name);
        };

        void set_value(int i){
            value=i;
        };

        std::string get_name(){
            return name;
        };

        int get_value(){
            return value;
        };

        // Constructors

        // Default constructor
        // Set value to 0 if no string for name
        card(std::string str=""){
            if (str==""){
                name=str;
                value=0;
            } else{
                set_name(str);
            };
            };

        // Copy constructor
        card(const card &c1){name=c1.name, value=c1.value;};

    private:
        std::string name;
        int value;
};

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

// Simple function to save repetition, draws a card from the shoe, adds it to the person's hand and total, and erases it from the shoe
void draw_card(std::vector<card> &person_hand, int &person_total, std::vector<card> &shoe){
    int random;
    random=rand()%shoe.size();
    person_hand.push_back(shoe[random]);
    person_total=(person_total+shoe[random].get_value())%10;
    shoe.erase(shoe.begin()+random);
};

// Simple function to save repetition, simply compares the two totals and outputs who wins
void conclude_coup(int player_total, int banker_total, int &money, bool banker_bet, int bet_amount, bool tie, int tie_amount, bool spec_tie_bool, int spec_tie, int spec_tie_amount){
    
    std::cout << "======================================" << std::endl;
    // Tie
    if (player_total==banker_total){
        std::cout << "Tie with total " << player_total << "." << std::endl;

        //Egalite bet wins
        if (tie){
            money+=tie_amount*9;
            std::cout << "Egalite! Tie bet wins." << std::endl;
        };

        // Specific Tie bet wins and odds
        if (spec_tie_bool && spec_tie==player_total){
            switch (spec_tie){
            case 0:
                money+=spec_tie_amount*150;
                break;
            case 1:
                money+=spec_tie_amount*215;
                break;
            case 2:
                money+=spec_tie_amount*225;
                break;
            case 3:
                money+=spec_tie_amount*200;
                break;
            case 4:
                money+=spec_tie_amount*120;
                break;
            case 5:
                money+=spec_tie_amount*110;
                break;
            case 6:
                money+=spec_tie_amount*45;
                break;
            case 7:
                money+=spec_tie_amount*45;
                break;
            case 8:
                money+=spec_tie_amount*80;
                break;
            case 9:
                money+=spec_tie_amount*80;
                break;
            default:
                break;
            };
            std::cout << "Egalite! Specific tie bet wins!" << std::endl;
        } else if (spec_tie_bool){
            money-=spec_tie_amount;
            std::cout << "Specific tie bet loses." << std::endl;
        };

    }

    // Player win
    else if (player_total > banker_total){

        if (!banker_bet){
            money+=bet_amount;
            std::cout << "Player win, Congradulations!" << std::endl;
        } else{
            money-=bet_amount;
            std::cout << "Player win, Commiserations." << std::endl;
        };

    }
    // Banker win
    else if (player_total < banker_total){

        if (banker_bet){
            money+=bet_amount;
            std::cout << "Banker win, Congradulations!" << std::endl;
        } else{
            money-=bet_amount;
            std::cout << "Banker win, Commiserations." << std::endl;
        };

    };

    // Tie loss
    if (banker_total!=player_total){
        if (tie || spec_tie){
            std::cout << "Tie and Specfic Tie bets lose" << std::endl;
            if (tie) money-=tie_amount;
            if(spec_tie) money-=spec_tie_amount;
        };
    };
    std::cout << "======================================" << std::endl;
};

// Simple function to save repetition, setup the full shoe of cards
void card_setup(std::vector<card> &shoe, int n_decks){

    shoe.resize(n_decks*52);

    for (int i=0; i<n_decks; i++){
        for (int j=0; j<4; j++){
            shoe[0+j*13+i*52].set_name("ace");
            shoe[1+j*13+i*52].set_name("two");
            shoe[2+j*13+i*52].set_name("three");
            shoe[3+j*13+i*52].set_name("four");
            shoe[4+j*13+i*52].set_name("five");
            shoe[5+j*13+i*52].set_name("six");
            shoe[6+j*13+i*52].set_name("seven");
            shoe[7+j*13+i*52].set_name("eight");
            shoe[8+j*13+i*52].set_name("nine");
            shoe[9+j*13+i*52].set_name("ten");
            shoe[10+j*13+i*52].set_name("jack");
            shoe[11+j*13+i*52].set_name("queen");
            shoe[12+j*13+i*52].set_name("king");
        };
    };
};

int main () {

// Get the player to enter their name
std::string name;

std::cout << "Please enter your name: " ;
getline(std::cin, name);

std::cout << "Welcome to Baccarat, " << name << "!" << std::endl;

// Seed random numbers
srand(time(NULL));

////
// Bets
////

//Variables
// Initial money set to 10000
int bet_amount, tie_amount=0, spec_tie_amount=0, spec_tie, money=10000, coup_counter=0, decks=8, random, player_total, banker_total;
bool banker_bet, tie, spec_tie_bool, again=true;
std::string mystr;
card drawn;
std::vector<card> cards(decks*52), player_hand, banker_hand;

while (again){
    // Reset and increment variables at the start of a loop
    coup_counter++;
    banker_total=0, player_total=0, tie_amount=0, spec_tie_amount=0, banker_bet=false, tie=false, spec_tie_bool=false;

    // Initial bet inputs
    std::cout << "======================================" << std::endl;

    // Standard bets
    std::cout << "1 - Banker" << "\n" << "2 - Player" << "\n" << "Choose your bet, 1 or 2: ";
    getline(std::cin, mystr);

    input_int_check(mystr, 1, 2);
    if (mystr=="1") banker_bet=true;

    std::cout << "Current money is £" << money << "." << std::endl;
    std::cout << "Enter a bet amount in whole pounds: ";
    getline(std::cin, mystr);

    input_int_check(mystr, 1, money);
    bet_amount=std::stoi(mystr);

    if (money-bet_amount>0){
        // Tie bets
        std::cout << "Would you like to make a standard tie bet? y/n: ";
        getline(std::cin, mystr);

        while (mystr!="y" && mystr!="Y" && mystr!="n" && mystr!="N"){
            std::cout << "Please enter either y or n: ";
            getline(std::cin, mystr);
        };

        if (mystr=="y" || mystr=="Y") {
            tie=true;
            std::cout << "Enter a tie bet amount in whole pounds: ";
            getline(std::cin, mystr);

            input_int_check(mystr, 1, money-bet_amount);
            tie_amount=std::stoi(mystr);
        };

        if (money-bet_amount-tie_amount>0){
           // Tie bets
            std::cout << "Would you like to make a specific tie bet? y/n: ";
            getline(std::cin, mystr);

            while (mystr!="y" && mystr!="Y" && mystr!="n" && mystr!="N"){
                std::cout << "Please enter either y or n: ";
                getline(std::cin, mystr);
            };

            if (mystr=="y" || mystr=="Y") {
                spec_tie=true;
                std::cout << "Enter the specfic value you think the Banker and Player will tie on, 0-9: ";
                getline(std::cin, mystr);

                input_int_check(mystr, 0, 9);
                spec_tie=std::stoi(mystr);

                std::cout << "Enter a specific tie bet amount in whole pounds: ";
                getline(std::cin, mystr);

                input_int_check(mystr, 1, money-bet_amount-tie_amount);
                tie_amount=std::stoi(mystr);
            }; 
        };
    };

    // Cards setup and burnt cards
    if (coup_counter==1 || cards.size()<=7){
        card_setup(cards, decks);

        random=rand()%cards.size();
        drawn=card(cards[random]);

        if (coup_counter==1) std::cout << "First coup, so cards shall be burnt." << std::endl;
        if (coup_counter>1) std::cout << "The cut card (8th remaining card) was drawn, so the shoe is refilled and cards shall be burnt." << std::endl;

        std::cout << "Card burnt face up is " << drawn.get_name() << ",  burning " << drawn.get_value() << " cards face down." << std::endl;
        std::cout << "======================================" << std::endl;
        cards.erase(cards.begin()+random);

        for (int i=0; i<drawn.get_value(); i++){
            random=rand()%cards.size();
            cards.erase(cards.begin()+random);
        };
    };

    ////
    // Coup
    ////

    // Initial draw
    for (int i=0; i<2; i++){
        draw_card(player_hand, player_total, cards);
        draw_card(banker_hand, banker_total, cards);
    };

    std::cout << "Player hand is " << player_hand[0].get_name() << ", " << player_hand[1].get_name() << ". Total is " << player_total << "." << std::endl;
    std::cout << "Banker hand is " << banker_hand[0].get_name() << ", " << banker_hand[1].get_name() << ". Total is " << banker_total << "." << std::endl;

    // Tableau

    // Tie
    if (banker_total>=8 && player_total>=8){
        std::cout << "Player and Banker draw Naturals." << std::endl;
        conclude_coup(player_total, banker_total, money, banker_bet, bet_amount, tie, tie_amount, spec_tie_bool, spec_tie, spec_tie_amount);
    }
    // Natural player win
    else if(player_total>=8){
        std::cout << "Natural Player win." << std::endl;
        conclude_coup(player_total, banker_total, money, banker_bet, bet_amount, tie, tie_amount, spec_tie_bool, spec_tie, spec_tie_amount);
    }
    // Natural Banker win
    else if (banker_total>=8){
        std::cout << "Natural Banker win." << std::endl;
        conclude_coup(player_total, banker_total, money, banker_bet, bet_amount, tie, tie_amount, spec_tie_bool, spec_tie, spec_tie_amount);
    }
    // Player stands if they have 6 or 7. Banker follows the player rules
    else if (player_total>=6){
        // Banker stands if they have 6 or 7
        if (banker_total>=6){
            std::cout << "Player and banker both stand. ";
        }
        // Banker draws if they have 5 or less
        else if (banker_total<=5){
            draw_card(banker_hand, banker_total, cards);
            std::cout << "Player stands. Banker draws " << banker_hand[2].get_name() << ", total " << banker_total << "." << std::endl;
        };

        // Conclude the coup
        conclude_coup(player_total, banker_total, money, banker_bet, bet_amount, tie, tie_amount, spec_tie_bool, spec_tie, spec_tie_amount);
    }
    // Player draws if they have 5 or less
    else if (player_total<=5){
        draw_card(player_hand, player_total, cards);
        std::cout << "Player draws " << player_hand[2].get_name() << ", total " << player_total << "." << std::endl;
    
        // Banker always draws if they have 2 or less
        if (banker_total<=2){
            draw_card(banker_hand, banker_total, cards);
            std::cout << "Banker draws " << banker_hand[2].get_name() << ", total " << banker_total << "." << std::endl;
        }
        // Banker draws on 3 if Player didn't draw an 8 as their third card
        else if (banker_total==3 && player_hand[2].get_value()!=8){
            draw_card(banker_hand, banker_total, cards);
            std::cout << "Banker draws " << banker_hand[2].get_name() << ", total " << banker_total << "." << std::endl;
        }
        // Banker draws on 4 if Player didn't draw 0(10), 1, 8 or 9 as their third card
        else if (banker_total==4 && (player_hand[2].get_value()!=10 || player_hand[2].get_value()!=1 || player_hand[2].get_value()!=8 || player_hand[2].get_value()!=9)){
            draw_card(banker_hand, banker_total, cards);
            std::cout << "Banker draws " << banker_hand[2].get_name() << ", total " << banker_total << "." << std::endl;
        }
        // Banker draws on 5 if Player drew 4, 5, 6 or 7 as their third card
        else if (banker_total==5 && (player_hand[2].get_value()==4 || player_hand[2].get_value()==5 || player_hand[2].get_value()==6 || player_hand[2].get_value()==7)){
            draw_card(banker_hand, banker_total, cards);
            std::cout << "Banker draws " << banker_hand[2].get_name() << ", total " << banker_total << "." << std::endl;
        } 
        // Banker draws on 6 if Player drew 6 or 7 as thier third card
        else if (banker_total==6 && (player_hand[2].get_value()==6 || player_hand[2].get_value()==7)){
            draw_card(banker_hand, banker_total, cards);
            std::cout << "Banker draws " << banker_hand[2].get_name() << ", total " << banker_total << "." << std::endl;
        }
        // Banker stands on 7
        else if (banker_total==7){
            std::cout << "Banker stands, total " << banker_total << "." << std::endl;
        };

        // Conclude the coup
        conclude_coup(player_total, banker_total, money, banker_bet, bet_amount, tie, tie_amount, spec_tie_bool, spec_tie, spec_tie_amount);
    };

    // Ask the player to play again
    if (money > 0) std::cout << "Do you wish to try your luck again? y/n: ";
    getline(std::cin, mystr);

    while (mystr!="y" && mystr!="Y" && mystr!="n" && mystr!="N"){
        std::cout << "Please enter either y or n: ";
        getline(std::cin, mystr);
    };

    if (mystr=="n" || mystr=="N") {
        again=false;
        std::cout << "Thanks for playing, " << name << "!";
        if (money>10000){
            std::cout << "Your final amount of money is £" << money << ", an increase of "<< money-10000 << "!" << std::endl;
        } else if (money<10000){
            std::cout << "Your final amount of money is £" << money << ", an decrease of "<< 10000-money << "." << std::endl;
        } else{
            std::cout << "You leave with what you started with! No harm, no foul." << std::endl;
        }

    };
};

}