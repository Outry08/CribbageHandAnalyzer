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

        numCards = num;

        for(int i = 0; i < 13; i++) {
            for(int j = 0; j < 4; j++) {
                cards[cardNum].setIcon(icons[i]);
                cards[cardNum].setSuit(suits[j]);
                cardNum++;
                if(cardNum >= num)
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

    Card getCutCard() {
        for(int i = 0; i < numCards; i++)
            if(cards[i].isCutCard())
                return cards[i];

        return Card();
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

    void remove(int index) {
        if(cards[index].getValue() != -1) {
            for(int i = index; i < numCards - 1; i++) {
                cards[i] = cards[i + 1];
            }
            numCards--;
        }
    }

    void add(Card card) {
        if(numCards < 52)
            cards[numCards++] = card;

        moveCutsToEnd();
    }

    void sort() {

        bool isMixed;
        Card dummy;

        do {
            isMixed = false;
            for(int i = 0; i < numCards - 1; i++) {
                if(cards[i].getRank() > cards[i + 1].getRank()) {
                    dummy = cards[i];
                    cards[i] = cards[i + 1];
                    cards[i + 1] = dummy;
                    isMixed = true;
                }
            }
        } while(isMixed);

        moveCutsToEnd();

    }

    void sortAll() {

        bool isMixed;
        Card dummy;

        do {
            isMixed = false;
            for(int i = 0; i < numCards - 1; i++) {
                if(cards[i].getRank() > cards[i + 1].getRank()) {
                    dummy = cards[i];
                    cards[i] = cards[i + 1];
                    cards[i + 1] = dummy;
                    isMixed = true;
                }
            }
        } while(isMixed);

    }

    void moveCutsToEnd() {
        Card dummy;
        bool isMixed;

        do {
            isMixed = false;

            for(int i = 0; i < numCards - 1; i++) {
                if(cards[i].isCutCard()) {
                    dummy = cards[i];
                    cards[i] = cards[i + 1];
                    cards[i + 1] = dummy;
                }
            }
        } while(isMixed);
    }

    int scoreAll() {
        int points = 0;

        points += scoreFifteens();
        points += scoreFlush();
        points += scoreJacks();
        points += scorePairs();
        points += scoreRuns();

        return points;
    }

    int scoreAllPrint() {
        int points = 0;

        int temp = scoreFifteens();
        if(temp > 0)
            cout << "15s: +" << temp << "\n";
        points += temp;

        temp = scorePairs();
        if(temp > 0)
            cout << "Pairs: +" << temp << "\n";
        points += temp;

        temp = scoreRuns();
        if(temp > 0)
            cout << "Runs: +" << temp << "\n";
        points += temp;

        temp = scoreFlush();
        if(temp > 0)
            cout << "Flush: +" << temp << "\n";
        points += temp;

        temp = scoreJacks();
        if(temp > 0)
            cout << "Jack: +" << temp << "\n";
        points += temp;

        cout << "Total: " << points << "pts\n";

        return points;
    }

    int scoreFifteens() {
        int points = 0;

        for(int i = 0; i < numCards; i++) {
            for(int j = i + 1; j < numCards; j++) {
                if(cards[i].getValue() + cards[j].getValue() == 15) {
                    points += 2;
                }
                else {
                    for(int k = j + 1; k < numCards; k++) {
                        if(cards[i].getValue() + cards[j].getValue() + cards[k].getValue() == 15) {
                            points += 2;
                        }
                        else {
                            for(int l = k + 1; l < numCards; l++) {
                                if(cards[i].getValue() + cards[j].getValue() + cards[k].getValue() + cards[l].getValue() == 15) {
                                    points += 2;
                                }
                            }
                        }
                    }
                }
            }
        }

        //Checking for quints
        if(numCards >= 5) {
            if(cards[0].getValue() + cards[1].getValue() + cards[2].getValue() + cards[3].getValue() + cards[4].getValue() == 15) {
                points += 2;
            }
        }

        return points;
    }

    int scorePairs() {
        int points = 0;

        for(int i = 0; i < numCards; i++) {
            for(int j = i + 1; j < numCards; j++) {
                if(cards[i].getIcon() == cards[j].getIcon()) {
                    points += 2;
                }
            }
        }

        return points;
    }

    int scoreRuns() {
        sortAll();
        int total = 0;

        for(int i = 0; i <= numCards - 3; i++) {
            int tempScore = checkNextRunPart(i);
            if(tempScore >= 3) {
                total += tempScore;
                break;
            }
        }

        moveCutsToEnd();

        return total;
    }

    protected:
    int checkNextRunPart(int index) {
        int points = 1;
        int streak = 0;

        for(int i = index + 1; i < numCards; i++) {
            if(cards[i].getRank() == cards[index].getRank() + 1) {
                streak++;
                points += checkNextRunPart(i);
                if(streak > 1)
                    points++;
            }
        }

        return points;
    }

    public:
    int scoreFlush() {
        int numClubs = 0;
        int numSpades = 0;
        int numHearts = 0;
        int numDiamonds = 0;
        string cutSuit = "";
        int hasCutCard = 0;

        for(int i = 0; i < numCards; i++) {
            if(!cards[i].isCutCard()) {
                if(cards[i].isClub())
                    numClubs++;
                else if(cards[i].isSpade())
                    numSpades++;
                else if(cards[i].isHeart())
                    numHearts++;
                else
                    numDiamonds++;
            }
            else {
                cutSuit = cards[i].getSuit();
                hasCutCard = 1;
            }
        }

        if(numClubs == numCards - hasCutCard) {
            if(cutSuit == "♣")
                numClubs++;
            return numClubs;
        }
        else if(numSpades == numCards - hasCutCard) {
            if(cutSuit == "♠")
                numSpades++;
            return numSpades;
        }
        else if(numHearts == numCards - hasCutCard) {
            if(cutSuit == "♥")
                numHearts++;
            return numHearts;
        }
        else if(numDiamonds == numCards - hasCutCard) {
            if(cutSuit == "♦")
                numDiamonds++;
            return numDiamonds;
        }

        return 0;
    }

    int scoreJacks() {
        string cutSuit = getCutCard().getSuit();

        for(int i = 0; i < numCards; i++)
            if(!cards[i].isCutCard())
                if(cards[i].getRank() == 11 && cards[i].getIcon() == "J")
                    if(cards[i].getSuit() == cutSuit)
                        return 1;

        return 0;
    }

    string toString() {

        string cardsString = "";

        for(int h = 0; h < numCards / 10; h++) {
            for(int i = 0 + h * 10; i < 10 + h * 10; i++) {
                if(cards[i].isCutCard())
                    cardsString += "   ";

                cardsString += "------- ";

                if(cards[i].isCutCard())
                    cardsString += "   ";
            }

            cardsString += "\n";

            for(int i = 0 + h * 10; i < 10 + h * 10; i++) {
                if(cards[i].isCutCard())
                    cardsString += "   ";

                cardsString += "|" + cards[i].getSuit() + "    | ";

                if(cards[i].isCutCard())
                    cardsString += "   ";
            }

            cardsString += "\n";

            for(int i = 0 + h * 10; i < 10 + h * 10; i++) {
                char extraSpace = ' ';
                if(cards[i].getIcon() == "10")
                    extraSpace = '\0';

                if(cards[i].isCutCard())
                    cardsString += "   ";

                cardsString += "|  " + cards[i].getIcon() + " " + extraSpace + "| ";

                if(cards[i].isCutCard())
                    cardsString += "   ";
            }

            cardsString += "\n";

            for(int i = 0 + h * 10; i < 10 + h * 10; i++) {
                if(cards[i].isCutCard())
                    cardsString += "   ";

                cardsString += "|    " + cards[i].getSuit() + "| ";

                if(cards[i].isCutCard())
                    cardsString += "   ";
            }

            cardsString += "\n";

            for(int i = 0 + h * 10; i < 10 + h * 10; i++) {
                if(cards[i].isCutCard())
                    cardsString += "   ";

                cardsString += "------- ";

                if(cards[i].isCutCard())
                    cardsString += "   ";
            }

            cardsString += "\n";
        }

        for(int i = numCards - numCards % 10; i < numCards; i++) {
            if(cards[i].isCutCard())
                cardsString += "   ";

            cardsString += "------- ";

            if(cards[i].isCutCard())
                cardsString += "   ";
        }

        cardsString += "\n";

        for(int i = numCards - numCards % 10; i < numCards; i++) {
            if(cards[i].isCutCard())
                cardsString += "   ";

            cardsString += "|" + cards[i].getSuit() + "    | ";

            if(cards[i].isCutCard())
                cardsString += "   ";
        }

        cardsString += "\n";

        for(int i = numCards - numCards % 10; i < numCards; i++) {
            char extraSpace = ' ';
            if(cards[i].getIcon() == "10")
                extraSpace = '\0';

            if(cards[i].isCutCard())
                cardsString += "   ";

            cardsString += "|  " + cards[i].getIcon() + " " + extraSpace + "| ";

            if(cards[i].isCutCard())
                cardsString += "   ";
        }

        cardsString += "\n";

        for(int i = numCards - numCards % 10; i < numCards; i++) {
            if(cards[i].isCutCard())
                cardsString += "   ";

            cardsString += "|    " + cards[i].getSuit() + "| ";

            if(cards[i].isCutCard())
                cardsString += "   ";
        }

        cardsString += "\n";

        for(int i = numCards - numCards % 10; i < numCards; i++) {
            if(cards[i].isCutCard())
                cardsString += "   ";

            cardsString += "------- ";

            if(cards[i].isCutCard())
                cardsString += "   ";
        }

        cardsString += "\n";

        return cardsString;
    }

};
