#include "main.h"
#include "Deck.cpp"

//♣ ♠ ♥ ♦

int main(int argc, char const* argv[]) {

    Deck deck(6);

    deck.shuffle();

    cout << deck.toString();

    Deck* allHands = deck.scoreAllHandsMinusTwo();
    int numPossibleHands = deck.numPossibleHands();

    for(int i = 0; i < numPossibleHands; i++) {
        allHands[i].scoreAllPrint();
    }

    // cout << "Which hand would you like to proceed with? (1-" << numPossibleHands << "): ";

    // int handChoice;
    // cin >> handChoice;

    // allHands[--handChoice].scoreAllCuts();

    Deck deck2(0);
    deck2.add(Card("10", "C"));
    deck2.add(Card("10", "s"));
    deck2.add(Card("J", "c"));
    deck2.add(Card("Q", "c"));

    deck2.scoreAllPrint();

    // Deck deck4(0);
    // deck4.add(Card("7", "C"));
    // deck4.add(Card("7", "c"));
    // deck4.add(Card("8", "c"));
    // deck4.add(Card("9", "c"));
    // deck4.add(Card("8", "d", true));

    // deck4.sort();
    // cout << deck4.toString();
    // deck4.scoreAllPrint();

    // Deck deck5(0);
    // deck5.add(Card("7", "C"));
    // deck5.add(Card("9", "c"));
    // deck5.add(Card("8", "c"));
    // deck5.add(Card("9", "c"));
    // deck5.add(Card("8", "d", true));

    // deck5.sort();
    // cout << deck5.toString();
    // deck5.scoreAllPrint();

    // Deck deck6(0);
    // deck6.add(Card("K", "C"));
    // deck6.add(Card("9", "c"));
    // deck6.add(Card("8", "c"));
    // deck6.add(Card("9", "c"));
    // deck6.add(Card("8", "d", true));

    // deck6.sort();
    // cout << deck6.toString();
    // deck6.scoreAllPrint();

    // Deck deck7(0);
    // deck7.add(Card("7", "C"));
    // deck7.add(Card("10", "c"));
    // deck7.add(Card("8", "c"));
    // deck7.add(Card("9", "c"));
    // deck7.add(Card("8", "d", true));

    // deck7.sort();
    // cout << deck7.toString();
    // deck7.scoreAllPrint();

    // Deck deck8(0);
    // deck8.add(Card("7", "C"));
    // deck8.add(Card("10", "c"));
    // deck8.add(Card("8", "c"));
    // deck8.add(Card("9", "c"));
    // deck8.add(Card("J", "d", true));

    // deck8.sort();
    // cout << deck8.toString();
    // deck8.scoreAllPrint();

    // Deck deck3(0);
    // deck3.add(Card("J", "C"));
    // deck3.add(Card("5", "c"));
    // deck3.add(Card("5", "c", true));
    // deck3.add(Card("5", "c"));
    // deck3.add(Card("5", "s"));

    // cout << deck3.toString();

    // deck3.scoreAllPrint();

    return 0;
}
