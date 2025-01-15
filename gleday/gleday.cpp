#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>

// Card structure
struct Card 
{
    std::string suit;
    std::string power;
};

const std::string suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
const std::string powers[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };

std::vector<char> tutti_fruttiPlayer;
std::vector<char> tutti_fruttiComputer;  

// Function to initialize the deck
std::vector<Card> initializeDeck() 
{
    std::vector<Card> deck;
    
    for (int i = 0; i < 4; i++) 
    {
        for (int j = 0; j < 13; j++) 
        {
            deck.push_back({suits[i],powers[j]});
        }
    }

    return deck;
}
void swap(Card& a, Card& b)
{
    Card temp = a;
    a = b;
    b = temp;
}
// Shuffle the deck
void shuffleDeck(std::vector<Card>& deck) 
{
    srand(time(0));
    for (int i = 0; i < deck.size(); i++)
    {
        swap(deck[i], deck[rand() % deck.size()]);
    }
}

// Deal initial cards to players
void dealCards(std::vector<Card>& deck, std::vector<Card>& player, std::vector<Card>& computer) 
{
    for (int i = 0; i < 6; i++) 
    {
        player.push_back(deck.back());
        deck.pop_back();

        computer.push_back(deck.back());
        deck.pop_back();
    }
}

// Print player's hand
void printHand(const std::vector<Card>& hand)
{
    for (int i = 0; i < hand.size(); i++)
    {
        std::cout << hand[i].power << " of " << hand[i].suit << std::endl;
    }
}

bool contains(std::string& power, const std::vector<Card>& deck)
{   
    for (int i = 0; i < deck.size(); i++)
    {
        if (deck[i].power == power)
        {
            return true;
        }
    }
    
    return false;
}

int countCardsOfPower(std::string& power, const std::vector<Card>& deck)
{
    int result = 0;
    for (int i = 0; i < deck.size(); i++)
    {
        if (deck[i].power == power)
        {
            result++;
        }
    }

    return result;
}

void removeFruitsFromDeck(std::string& power, std::vector<Card>& deck) 
{
    for (int i = 0; i < deck.size(); i++)
    {
        if (deck[i].power == power)
        {
            deck.erase(deck.begin() + i);
        }
    }
}

//Player's turn
void playerTurn(std::vector<Card>& deck, std::vector<Card>& player, std::vector<Card>& computer) 
{
    bool valid = true;
    while (valid)
    {
        std::string power;
        std::cout << "Your turn! Enter a card value to ask for: ";
        std::cin >> power;
        while (!contains(power, player))
        {
            std::cout << "You can't ask for " << power << "!" << std::endl;
            std::cout << "Enter a card value to ask for: ";
            std::cin >> power;
        }
        std::cout << std::endl;

        // Check if the computer has the card
        bool found = false;
        int countCards = 0;
        for (int i = 0; i < computer.size(); i++)
        {
            if (computer[i].power == power)
            {
                found = true;
                countCards++;
                player.push_back(computer[i]);

                if (countCardsOfPower(power, player) == 4)
                {
                    std::string ans;
                    while (true)
                    {
                        std::cout << "Do you have four of " << power << "? (yes/no)";
                        std::cin >> ans;
                        if (ans == "yes")
                        {
                            char parse = power[0];
                            tutti_fruttiPlayer.push_back(parse);
                            removeFruitsFromDeck(power, player);
                            break;
                        }
                        else
                        {
                            std::cout << "Incorrect answer" << std:: endl;
                        }
                    }
                }
                computer.erase(computer.begin() + i);
            }
        }
       // std::cout << found;
        if (!found)
        {
            std::cout << "Computer doesn't have " << power << ". Drawing a card from the deck." << std::endl;
            if (!deck.empty())
            {
                player.push_back(deck.back());
                deck.pop_back();
                
                if (countCardsOfPower(power, player) == 4)
                {
                    std::string ans;
                    while(true)
                    {
                        std::cout << "Do you have four of " << power << "? (yes/no)";
                        std::cin >> ans;
                        if (ans == "yes")
                        {
                            char parse = power[0];
                            tutti_fruttiPlayer.push_back(parse);
                            removeFruitsFromDeck(power, player);
                            break;
                        }
                        else
                        {
                            std::cout << "Incorrect answer";
                        }
                    }
                }

                if (player.back().power == power)
                {
                    found = true;
                    std::cout << "You drew a " << power << '.' << std::endl;
                    continue;
                }
            }
            else
            {
                std::cout << "Deck is empty!" << std::endl;
            }
            valid = false;
        }
        else
        {
            std::cout << "Computer gives you " << power << "!" << std::endl;
        }
    }

    printHand(player);
    std::cout << std::endl;
    std::cout << std::endl << "Computer's hand: " << std::endl;
    printHand(computer);
    std::cout << std::endl;
}

bool typeAnswer(std::string& power, bool&found)
{
    std::string answer = " ";

    while(true)
    {
        std::cout << "Do you have " << power << "? (yes/no)";
        std::cin >> answer;
        if (answer == "yes")
        {
            found = true;
            break;
        }
        else if (answer == "no")
        {
            found = false;
            break;
        }
        else
        {
            std::cout << "Incorrect answer!" << std::endl;
        }
    }

    return found;
}

// Computer's turn (randomized)
void computerTurn(std::vector<Card>& deck, std::vector<Card>& player, std::vector<Card>& computer)
{
    std::cout << "Computer's turn!" << std::endl;
    if (!player.empty()) 
    {
        // Ask if the player has the card
        bool found = false;
        //int countCards = 0;
        bool valid = true;
        while (valid)
        {
            std::string power = computer[rand() % computer.size()].power;
            std::cout << "Computer asks for " << power << "!" << std::endl;
            typeAnswer(power, found);

            if(found)
            {
                for (int i = 0; i < player.size(); i++)
                {
                    if (player[i].power == power)
                    {
                        //found = true;
                        //countCards++;
                        computer.push_back(player[i]);
                        if (countCardsOfPower(power, computer) == 4)
                        {
                            char parse = player[i].power[0];
                            tutti_fruttiComputer.push_back(parse);
                            removeFruitsFromDeck(power, computer);
                        }
                        player.erase(player.begin() + i);
                    }
                }
            }

            if (!found)
            {
                std::cout << "You don't have " << power << ". Computer draws a card from the deck." << std::endl;
                if (!deck.empty())
                {
                    computer.push_back(deck.back());
                    deck.pop_back();

                    if (countCardsOfPower(power, computer) == 4)
                    {
                        char parse = power[0];
                        tutti_fruttiComputer.push_back(parse);
                        removeFruitsFromDeck(power, computer);
                        std::cout << "Computer has four of " << power << ".";
                    }

                    if (computer.back().power == power)
                    {
                        std::cout << "Computer drew a " << power << '.' << std::endl;
                        found = true;
                        continue;
                    }
                }
                else
                {
                    std::cout << "Deck is empty!" << std::endl;
                }
                valid = false;
            }
            else
            {
                std::cout << "You give " << power << " to the computer!" << std::endl;
                found = false;
            }
        }

        printHand(player);
        std::cout << std::endl;
        std::cout << std::endl << "Computer's hand: " << std::endl;
        printHand(computer);
        std::cout << std::endl;
    }
}

// Check for winner
bool checkWinner(const std::vector<Card>& player, const std::vector<Card>& computer) {
    if (player.empty()) {
        std::cout << "Computer wins!" << std::endl;
        return true;
    }
    else if (computer.empty()) {
        std::cout << "You win!" << std::endl;
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

    std::cout << "Your initial hand:" << std::endl;
    printHand(player);
    std::cout << std::endl;
    

    bool game_over = false;
    while (!game_over) {
        playerTurn(deck, player, computer);
        game_over = checkWinner(player, computer);
        if (game_over) break;

        computerTurn(deck, player, computer);
        game_over = checkWinner(player, computer);
    }



    return 0;
}