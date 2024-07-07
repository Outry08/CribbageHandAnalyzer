#include "main.h"
#include "Deck.cpp"

//♣ ♠ ♥ ♦

int main(int argc, char const* argv[]) {

    Deck deck(6);

    deck.shuffle();
    Card card("J", "♦");
    cout << card.toString();

    for(int i = 0; i < deck.getNumCards(); i++) {
        cout << deck.getCard(i).toString();
    }

    return 0;
}
