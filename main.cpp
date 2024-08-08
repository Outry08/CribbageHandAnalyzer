#include "main.h"
#include "Deck.cpp"

//♣ ♠ ♥ ♦

int main(int argc, char const* argv[]) {

    Deck deck(6);
    Deck inputDeck(0);

    cout << "Welcome to the Cribbage Hand Analyzer!\nA tool to analyze all the angles of a hand of 4 or 6 cards to help make the right choice of which cards to discard.\nInputting 6 cards allows you to analyze each combination of 4 cards as well as possible cuts with these combinations. Entering 4 cards jumps straight to the cut analysis.";
    cout << "Please input your hand you would like to analyze.\n(3 of Clubs = 3c) (Example: \"3c, As, 10h, Qd\")\nInput: ";
    int numCardsInputted = 0;
    string input;
    getline(cin, input);
    do {
        if(numCardsInputted > 6) {
            cout << "Number of cards entered exceeded maximum of 6. Please try again: ";
            numCardsInputted = 0;
            getline(cin, input);
        }
        if(input.length() == 0) {
            cout << "Number of cards inputted so far: " << numCardsInputted << "\nPlease input ";
            if(numCardsInputted < 4) {
                cout << (4 - numCardsInputted);
                cout << " more cards to reach 4 cards, or ";
            }
            cout << (6 - numCardsInputted) << " more cards to reach 6 cards.\nInput: ";
            getline(cin, input);
        }
        cout << input << "\n";
        string card;
        if(input.find_first_of(',') != string::npos)
            card = input.substr(0, input.find_first_of(',') + 1);
        else
            card = input;
        cout << card << "\n";
        numCardsInputted++;

        string icon = "";
        icon += card[0];
        int suitPos = 1;
        if(card[1] == '0') {
            icon += '0';
            suitPos++;
        }

        string suit = "";
        suit += card[suitPos];

        if(input.find_first_of(',') != string::npos)
            input = input.substr(input.find_first_of(',') + (input[input.find_first_of(',') + 1] == ' ' ? 2 : 1));
        else
            input = "\0";

        cout << Card(icon, suit, false).toString();
    } while(!(input.length() == 0 && (numCardsInputted == 4 || numCardsInputted == 6)));

    deck.shuffle();

    cout << deck.toStringln();

    int numPossibleHands = deck.numPossibleHands();

    int handChoice;

    do {
        deck.scoreAllHandsMinusTwo(true);
        cout << "Enemy's Crib:\n";
        deck.rankAllPossibilities(false);
        cout << "Your Crib:\n";
        Deck* allHands = deck.rankAllPossibilities(true);
        cout << "Which hand would you like to see the cuts of? (1-" << numPossibleHands << ") (0 to exit): ";
        do {
            cin >> handChoice;
            if(handChoice < 0 || handChoice > numPossibleHands)
                cout << "Please input a number between 0-" << numPossibleHands << ": ";
        } while(handChoice < 0 || handChoice > numPossibleHands);

        if(handChoice > 0)
            allHands[handChoice - 1].scoreAllCuts(deck);
    } while(handChoice > 0 && handChoice <= numPossibleHands);

    return 0;
}
