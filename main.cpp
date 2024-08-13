#include "main.h"
#include "Deck.cpp"

//♣ ♠ ♥ ♦

int main(int argc, char const* argv[]) {

    // Deck deck(6);
    Deck inputDeck(0);
    int menuChoice;

    cout << "Welcome to the Cribbage Hand Analyzer!\nA tool to analyze all the angles of a hand of 4 or 6 cards to help make the right choice of which cards to discard.\nInputting 6 cards allows you to analyze each combination of 4 cards as well as possible cuts with these combinations.\nEntering 4 cards jumps straight to the cut analysis.\n";

    do {
        cout << "\nPlease input your hand you would like to analyze.\n(3 of Clubs = 3c) (Example: \"3c, As, 10h, Qd\")\nInput: ";

        int numCardsInputted = 0;
        string input;
        getline(cin, input);
        do {
            if(numCardsInputted > 6) {
                cout << "Number of cards entered exceeded maximum of 6. Please try again: ";
                numCardsInputted = 0;
                inputDeck.removeAll();
                getline(cin, input);
            }
            if(input.length() == 0) {
                cout << "Hand so far:\n" << inputDeck.toStringln();
                cout << "Number of cards inputted so far: " << numCardsInputted << "\nPlease input ";
                if(numCardsInputted < 4) {
                    cout << (4 - numCardsInputted);
                    cout << " more cards to reach 4 cards, or ";
                }
                cout << (6 - numCardsInputted) << " more cards to reach 6 cards.\nInput: ";
                getline(cin, input);
            }

            string card;
            if(input.find_first_of(',') != string::npos)
                card = input.substr(0, input.find_first_of(',') + 1);
            else
                card = input;
            numCardsInputted++;

            string icon, suit;

            icon = card.substr(0, card[card.length() - 1] == ',' ? card.length() - 2 : card.length() - 1);

            suit = "";
            suit += card[card[card.length() - 1] == ',' ? card.length() - 2 : card.length() - 1];

            if(!isValidSuit(suit) || !isValidIcon(icon)) {
                cout << "Error: Invalid input format. Please try again: ";
                inputDeck.removeAll();
                numCardsInputted = 0;
                getline(cin, input);
                continue;
            }

            if(input.find_first_of(',') != string::npos)
                input = input.substr(input.find_first_of(',') + (input[input.find_first_of(',') + 1] == ' ' ? 2 : 1));
            else
                input = "\0";

            inputDeck.add(Card(icon, suit, false));
            cout << inputDeck.toStringln();
        } while(!(input.length() == 0 && (numCardsInputted == 4 || numCardsInputted == 6)));

        cout << "\nWhat would you like to do?\n";
        if(inputDeck.getNumCards() == 6) {
            cout << "1. Choose two discard cards\n"
                << "2. Rank all possible choices\n";
        }
        else if(inputDeck.getNumCards() == 4) {
            cout << "1. Rank all possible cuts\n"
                << "2. Go back to original hand of 6\n";
        }
        cout << "3. Input new deck\n"
            << "0. Exit program\n"
            << "Input: ";

        do {
            cin >> menuChoice;
            if(menuChoice < 0 || menuChoice > 3)
                cout << "Error. Please input a number between 0-3: ";
        } while(menuChoice < 0 || menuChoice > 3);

    } while(menuChoice == 3);

    // deck.shuffle();
    // cout << deck.toStringln();

    // int numPossibleHands = deck.numPossibleHands();

    // int handChoice;

    // do {
    //     deck.scoreAllHandsMinusTwo(false);
    //     cout << "Enemy's Crib:\n";
    //     deck.rankAllPossibilities(false);
    //     cout << "Your Crib:\n";
    //     Deck* allHands = deck.rankAllPossibilities(true);
    //     cout << "Which hand would you like to see the cuts of? (1-" << numPossibleHands << ") (0 to exit): ";
    //     do {
    //         cin >> handChoice;
    //         if(handChoice < 0 || handChoice > numPossibleHands)
    //             cout << "Please input a number between 0-" << numPossibleHands << ": ";
    //     } while(handChoice < 0 || handChoice > numPossibleHands);

    //     if(handChoice > 0)
    //         allHands[handChoice - 1].scoreAllCuts(deck);
    // } while(handChoice > 0 && handChoice <= numPossibleHands);

    return 0;
}

bool isValidIcon(string icon) {
    if(icon.length() > 2 || icon.length() <= 0)
        return false;

    if(icon.length() == 2) {
        return icon == "10";
    }
    else if(isdigit(icon[0])) {
        bool foundDigit = false;

        for(int i = 2; i < 10; i++)
            if(icon[0] == '0' + i)
                foundDigit = true;

        return foundDigit;
    }
    else if(icon.length() == 1) {
        icon[0] = toupper(icon[0]);
        return icon == "J" || icon == "Q" || icon == "K" || icon == "A";
    }
    return false;
}

bool isValidSuit(string suit) {
    if(suit.length() != 1)
        return false;

    suit[0] = toupper(suit[0]);

    return suit == "C" || suit == "S" || suit == "H" || suit == "D" || suit == "♣" || suit == "♠" || suit == "♥" || suit == "♦";
}
