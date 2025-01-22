/**
*
* Solution to course project # 1
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2023/2024
*
* @author Katerina Bancheva
* @idnumber 1MI0600482* @compiler VS
*
* <file with all functions>
*
*/


#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>

const int NUMBER_OF_SUITS = 4;
const int NUMBER_OF_POWERS = 13;
const int STARTING_NUMBER_OF_CARDS = 6;
const int NUMBER_OF_CARDS_TO_PUT_DOWN = 4;

// Card structure
struct Card {
 std::string suit;
 std::string power;
};

const std::string suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
//const std::string powers[] = { "2", "3", "4", "5", "6" };
const std::string powers[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };

std::vector<char> tutti_fruttiPlayer;
std::vector<char> tutti_fruttiComputer;  

// Function to initialize the deck
std::vector<Card> initializeDeck() {
    std::vector<Card> deck;
    
    for (int i = 0; i < NUMBER_OF_SUITS; i++) {
        for (int j = 0; j < NUMBER_OF_POWERS; j++) { // j < NUMBER_OF_POWERS
            deck.push_back({suits[i],powers[j]});
        }
    }
    return deck;
}

void swap(Card& a, Card& b) {
    Card temp = a;
    a = b;
    b = temp;
}

void shuffleDeck(std::vector<Card>& deck) {
    srand(time(0));
    for (int i = 0; i < deck.size(); i++) {
        swap(deck[i], deck[rand() % deck.size()]);
    }
}

int countCardsOfPower(std::string& power, const std::vector<Card>& deck) {
    int result = 0;
    for (int i = 0; i < deck.size(); i++) {
        if (deck[i].power == power) {
            result++;
        }
    }
    return result;
}

void validDeck(std::vector<Card>& validDeck, std::vector<Card>& deck) {
    for (int i = 0; i < validDeck.size(); i++) {
        if (countCardsOfPower(validDeck[i].power, validDeck) == 4) {
            Card toRemove = validDeck.back();
            validDeck.erase(validDeck.begin() + i);
            validDeck.push_back(deck.back());
            deck.push_back(toRemove);
        }
    }
}

void dealCards(std::vector<Card>& deck, std::vector<Card>& player, std::vector<Card>& computer) {
    for (int i = 0; i < STARTING_NUMBER_OF_CARDS; i++) {
        player.push_back(deck.back());
        deck.pop_back();

        computer.push_back(deck.back());
        deck.pop_back();
    }
    validDeck(computer, deck);
    validDeck(player, deck);
}

void printHand(const std::vector<Card>& hand) {
    for (int i = 0; i < hand.size(); i++) {
        std::cout << hand[i].power << " of " << hand[i].suit << std::endl;
    }
}

//da mahna
void printFruits(std::vector<char>& tutti_frutti)
{
    for(int i = 0; i < tutti_frutti.size(); i++)
    {
        std::cout << tutti_frutti[i] << " ";
    }
}

bool contains(std::string& power, const std::vector<Card>& deck) {   
    for (int i = 0; i < deck.size(); i++) {
        if (deck[i].power == power) {
            return true;
        }
    }
    return false;
}

bool contains(char current, const std::vector<char>& tutti_frutti) {
    for (int i = 0; i < tutti_frutti.size(); i++) {
        if (tutti_frutti[i] == current) {
            return true;
        }
    }
    return false;
}

void removeFruitsFromDeck(std::string& power, std::vector<Card>& deck) {
    for (int i = 0; i < deck.size();) {
        if (deck[i].power == power) {
            deck.erase(deck.begin() + i);
        }
        else {
            i++;
        }
    }
}

void playerTurn(std::vector<Card>& deck, std::vector<Card>& player, std::vector<Card>& computer) {
    bool valid = true;
    while (valid) {
        if (computer.empty()) {
            break;
        }
        if (player.empty()) {
            std::cout << "Drawing a card from the deck." << std::endl;
            player.push_back(deck.back());
            deck.pop_back();
        }
        std::string power;
        std::cout << "Your turn! Enter a card value to ask for: ";
        std::cin >> power;

        while (!contains(power, player)) {
            std::cout << "You can't ask for " << power << "!" << std::endl;
            std::cout << "Enter a card value to ask for: ";
            std::cin >> power;
        }
        std::cout << std::endl;

        bool found = false;
        //check if computer has cards of the same power
        for (int i = 0; i < computer.size();) {
            if (computer[i].power == power) {
                found = true;
                player.push_back(computer[i]);
                computer.erase(computer.begin() + i);
            }
            else {
                i++;
            }
        }

        if (!found) {
            std::cout << "Computer doesn't have " << power << ". Drawing a card from the deck." << std::endl;
            if (!deck.empty()) {
                player.push_back(deck.back());
                deck.pop_back();
                Card drawnCard = player.back();
                if (countCardsOfPower( drawnCard.power, player) == NUMBER_OF_CARDS_TO_PUT_DOWN) {
                    std::cout << "You drew a " << power << "." << std::endl;
                    std::string ans;
                    while (true) {
                        std::cout << "Do you have four of " << power << "? (yes/no)";
                        std::cin >> ans;
                        if (ans == "yes") {
                            char parse = power[0];
                            tutti_fruttiPlayer.push_back(parse);
                            removeFruitsFromDeck(power, player);
                            std::cout << "You put away " << power << ". " << std::endl;
                            break;
                        }
                        else {
                            std::cout << "Incorrect answer.";
                        }
                    }
                    found = true;
                    continue;
                }

                if (player.back().power == power) {
                    found = true;
                    std::cout << "You drew a " << power << '.' << std::endl;
                    continue;
                }
            }
            else {
                std::cout << "Deck is empty!" << std::endl;
            }
            valid = false;
        }
        else {
            std::cout << "Computer gives you " << power << "!" << std::endl;

            if (countCardsOfPower(power, player) == NUMBER_OF_CARDS_TO_PUT_DOWN) {
                std::string ans;
                while (true) {
                    std::cout << "Do you have four of " << power << "? (yes/no)";
                    std::cin >> ans;
                    if (ans == "yes") {
                        char parse = power[0];
                        tutti_fruttiPlayer.push_back(parse);
                        removeFruitsFromDeck(power, player);
                        break;
                    }
                    else {
                        std::cout << "Incorrect answer" << std::endl;
                    }
                }
                std::cout << "You put away " << power << "." << std::endl;
            }
        }
    }

    printHand(player);
    std::cout << std::endl;
    std::cout << "fruits player: ";
    printFruits(tutti_fruttiPlayer);
    std::cout << std::endl << "Computer's hand: " << std::endl;
    printHand(computer);
    std::cout << std::endl;
    std::cout << "fruits comp: ";
    printFruits(tutti_fruttiComputer);
    std::cout << std::endl;
}

bool typeAnswer(std::string& power, bool&found) {
    std::string answer = " ";

    while(true) {
        std::cout << "Do you have " << power << "? (yes/no)";
        std::cin >> answer;
        if (answer == "yes") {
            found = true;
            break;
        }
        else if (answer == "no") {
            found = false;
            break;
        }
        else {
            std::cout << "Incorrect answer!" << std::endl;
        }
    }

    return found;
}

void takeFruits(char current, std::vector<char>& in, std::vector<char>& out, bool& found) {
    found = false;
    for (int i = 0; i < out.size(); i++) {
        if (out[i] == current) {
            in.push_back(current);
            out.erase(out.begin() + i);
            found = true;
            break;
        }
    }
}
//second stage
void playerTurn(std::vector<char>& tutti_fruttiPlayer, std::vector<char>& tutti_fruttiComputer) {
    char current;
    bool found;
    do {
        if (tutti_fruttiComputer.empty() || tutti_fruttiComputer.empty()) {
            break;
        }

        std::cout << "Your turn! Enter a card value to ask for: ";
        std::cin >> current;

        takeFruits(current, tutti_fruttiPlayer, tutti_fruttiComputer, found); // in out

        if(found) {
            std::cout << "Computer gives you " << current << "!" << std::endl;
        }
        else {
            std::cout << "Computer doesn't have " << current << std::endl;
        }

    } while (found);
   
    std::cout << std::endl;
    std::cout << "fruits player: ";
    printFruits(tutti_fruttiPlayer);
    std::cout << std::endl;
    std::cout << "fruits comp: ";
    printFruits(tutti_fruttiComputer);
    std::cout << std::endl;
}

// Computer's turn 
void computerTurn(std::vector<Card>& deck, std::vector<Card>& player, std::vector<Card>& computer) {
    std::cout << "Computer's turn!" << std::endl;
    if (!player.empty()) {
        bool found = false;
        bool valid = true;
        while (valid) {
            if (player.empty() ) {
                break;
            }
            if (computer.empty()) {
                std::cout << "Computer draws a card from the deck." << std::endl;
                computer.push_back(deck.back());
                deck.pop_back();
            }

            std::string power = computer[rand() % computer.size()].power;
            std::cout << "Computer asks for " << power << "!" << std::endl;
            typeAnswer(power, found);

            if(found) {
                for (int i = 0; i < player.size(); ) {
                    if (player[i].power == power) {
                        computer.push_back(player[i]);
                        player.erase(player.begin() + i);
                    }
                    else {
                        i++;
                    }
                }
            }
            if (!found) {
                std::cout << "You don't have " << power << ". Computer draws a card from the deck." << std::endl;
                if (!deck.empty()) {
                    computer.push_back(deck.back());
                    deck.pop_back();

                    Card drawnCard = computer.back();  
                    if (countCardsOfPower(drawnCard.power, computer) == NUMBER_OF_CARDS_TO_PUT_DOWN) {
                        char parse = power[0];
                        tutti_fruttiComputer.push_back(parse);
                        std::cout << "Computer drew a " << power << '.' << std::endl;
                        std::cout << "Computer has four of " << power << "." << std::endl;
                        std::cout << "Computer puts away " << power << "." << std::endl;
                        removeFruitsFromDeck(power, computer);

                        if (drawnCard.power == power) {
                            continue;
                        }
                    }

                    if (drawnCard.power == power) {
                        std::cout << "Computer drew a " << power << '.' << std::endl;
                        found = true;
                        continue;
                    }
                }
                else {
                    std::cout << "Deck is empty!" << std::endl;
                }
                valid = false;
            }
            else {
                std::cout << "You give " << power << " to the computer!" << std::endl;
                if (countCardsOfPower(power, computer) == NUMBER_OF_CARDS_TO_PUT_DOWN) {
                    char parse = computer.back().power[0];
                    tutti_fruttiComputer.push_back(parse);
                    removeFruitsFromDeck(power, computer);
                    std::cout << "Computer has four of " << power << ".";
                    std::cout << "Computer puts away " << power << "." << std::endl;
                }
                found = false;
            }
        }

        printHand(player);
        std::cout << std::endl;
        std::cout << "fruits player: ";
        printFruits(tutti_fruttiPlayer);
        std::cout << std::endl << "Computer's hand: " << std::endl;
        printHand(computer);
        std::cout << "fruits comp: ";
        printFruits(tutti_fruttiComputer);
        std::cout << std::endl;
        std::cout << std::endl;
    }
}

//second stage
void computerTurn(std::vector<char>& tutti_fruttiPlayer, std::vector<char>& tutti_fruttiComputer) {
    char current;
    bool found;
    do {
        if (tutti_fruttiPlayer.empty() || tutti_fruttiComputer.empty()) {
            break;
        }
        std::string c = powers[rand() % powers->size()];
        current = c[0];
        std::cout << "Computer asks for " << current << "!" << std::endl;
        takeFruits(current, tutti_fruttiComputer, tutti_fruttiPlayer, found); // da prenapisha

        if(found) {
            std::cout << "You give " << current << " to the computer!" << std::endl;
        }
        else {
            std::cout << "You don't have " << current << "." << std::endl;
        }

    } while (found);

    std::cout << std::endl;
    std::cout << "fruits player: ";
    printFruits(tutti_fruttiPlayer);
    std::cout << std::endl;
    std::cout << "fruits comp: ";
    printFruits(tutti_fruttiComputer);
    std::cout << std::endl;
}

// Check for winner
bool checkWinner(const std::vector<Card>& player, const std::vector<Card>& computer) {
    if (player.empty() && computer.empty()) {
        if (tutti_fruttiComputer.size() > tutti_fruttiPlayer.size()) {
            std::cout << "Computer wins the first stage of the game!" << std::endl;
            return true;
        }
        else {
            std::cout << "You win the first stage of the game!" << std::endl;
            return true;
        }
    }
    else if (player.empty()) {
        std::cout << "Computer wins the first stage of the game!" << std::endl;
        return true;
    }
    else if (computer.empty()) {
        std::cout << "You win the first stage of the game!" << std::endl;
        return true;
    }
    return false;
}

bool checkWinner(std::vector<char>& tutti_fruttiComputer, std::vector<char>& tutti_fruttiPlayer ) {
    if (tutti_fruttiPlayer.empty()) {
        std::cout << "Computer wins the game!" << std::endl;
        return true;
    }
    else if (tutti_fruttiComputer.empty()) {
        std::cout << "You win the game!" << std::endl;
        return true;
    }
    return false;
}

int main() {
    std::vector<Card> deck = initializeDeck();
    shuffleDeck(deck);
    //printHand(deck);

    std::vector<Card> player, computer;
    dealCards(deck, player, computer);

   // std::cout << validDeck(computer) << validDeck(player) << std::endl;

    std::cout << "Your initial hand:" << std::endl;
    printHand(player);
    std::cout << std::endl;
    

    bool game_over = false;
    while (!game_over) {
        playerTurn(deck, player, computer);
        game_over = checkWinner(player, computer);
        //std::cout << game_over;
        if (game_over) break;

        computerTurn(deck, player, computer);
        game_over = checkWinner(player, computer);
        //std::cout << game_over;
    }

    //second stage
    game_over = checkWinner(tutti_fruttiComputer, tutti_fruttiPlayer);
    while (!game_over) {
        playerTurn(tutti_fruttiPlayer, tutti_fruttiComputer);
        game_over = checkWinner(tutti_fruttiComputer, tutti_fruttiPlayer);
        if (game_over) break;

        computerTurn(tutti_fruttiPlayer, tutti_fruttiComputer);
        game_over = checkWinner(tutti_fruttiComputer, tutti_fruttiPlayer);
    }


    return 0;
}