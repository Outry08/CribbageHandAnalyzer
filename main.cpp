#include "main.h"
#include "Deck.cpp"

//♣ ♠ ♥ ♦

int main(int argc, char const* argv[]) {

    Deck deck(6);

    deck.shuffle();

    cout << deck.toString();

    deck.remove(4);
    deck.remove(4);
    deck.sort();

    cout << deck.toString();

    deck.scoreAllPrint();

    Deck deck1Copy = deck;
    deck1Copy.remove(0);
    cout << deck.toString() << "\n" << deck1Copy.toString();

    Deck deck2(0);
    deck2.add(Card("8", "C"));
    deck2.add(Card("7", "c"));
    deck2.add(Card("8", "c"));
    deck2.add(Card("9", "c"));

    cout << deck2.toString();

    deck2.scoreAllPrint();

    Deck deck3(0);
    deck3.add(Card("J", "C"));
    deck3.add(Card("5", "c"));
    deck3.add(Card("5", "c", true));
    deck3.add(Card("5", "c"));
    deck3.add(Card("5", "s"));

    cout << deck3.toString();

    deck3.scoreAllPrint();

    return 0;
}
