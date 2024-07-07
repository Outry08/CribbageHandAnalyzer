#include "main.h"
#include "Card.cpp"

//♣ ♠ ♥ ♦

class Deck {

    private:
    Card cards[MAX_CARDS];
    int numCards;

    public:
    Deck() {
        string suits[] = { "♣", "♠", "♥", "♦" };
        string icons[] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
        int cardNum = 0;

        for(int i = 0; i < 13; i++) {
            for(int j = 0; j < 4; j++) {
                cards[cardNum].setIcon(icons[i]);
                cards[cardNum].setSuit(suits[j]);
                cardNum++;
            }
        }

        numCards = MAX_CARDS;
    }

    Deck(int num) {
        string suits[] = { "♣", "♠", "♥", "♦" };
        string icons[] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
        int cardNum = 0;

        int count = 0;

        numCards = num;

        for(int i = 0; i < 13; i++) {
            for(int j = 0; j < 4; j++) {
                cards[cardNum].setIcon(icons[i]);
                cards[cardNum].setSuit(suits[j]);
                cardNum++;
                count++;
                if(count >= num)
                    return;
            }
        }
    }

    int getNumCards() {
        return numCards;
    }

    Card getCard(int index) {
        if(index >= 0 && index < 52)
            return cards[index];
        return Card("Error", "Err");
    }

    void shuffle() {

        srand((unsigned)time(0));
        int pastIndexes[MAX_CARDS];
        Deck tempDeck;

        for(int i = 0; i < MAX_CARDS; i++) {
            pastIndexes[i] = -1;
        }

        for(int i = 0; i < numCards; i++) {
            int randIndex;
            int taken = 0;
            int j;
            do {
                taken = 0;
                randIndex = rand() % MAX_CARDS;
                for(j = 0; j < MAX_CARDS; j++) {
                    if(pastIndexes[j] == randIndex)
                        taken = 1;
                    else if(pastIndexes[j] == -1)
                        break;
                }
            } while(taken);

            cards[i] = tempDeck.getCard(randIndex);
            pastIndexes[j] = randIndex;

        }

    }

};
