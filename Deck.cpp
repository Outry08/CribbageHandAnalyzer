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

        for(int i = 0; i < MAX_CARDS; i++)
            cards[i] = Card();

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

    Deck(Card crds[MAX_CARDS], int num) {
        int count = 0;

        while(count < num && crds[count].getRank() >= 0) {
            cards[count] = crds[count];
            count++;
        }

        numCards = num;
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
        // cout << getNumCards() << "\n";
        if(index >= 0 && index <= getNumCards()) {
            if(cards[index].getValue() != -1) {
                for(int i = index; i < getNumCards() - 1; i++) {
                    cards[i] = cards[i + 1];
                }
                numCards--;
            }
        }
    }

    void add(Card card) {
        if(numCards < 52)
            cards[numCards++] = card;

        moveCutsToEnd();
    }

    bool contains(Card card) {
        for(int i = 0; i < getNumCards(); i++)
            if(getCard(i).equals(card))
                return true;

        return false;
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

        cout << toStringln();

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
                if(cards[i].getValue() + cards[j].getValue() == 15)
                    points += 2;
                else {
                    for(int k = j + 1; k < numCards; k++) {
                        if(cards[i].getValue() + cards[j].getValue() + cards[k].getValue() == 15)
                            points += 2;
                        else
                            for(int l = k + 1; l < numCards; l++)
                                if(cards[i].getValue() + cards[j].getValue() + cards[k].getValue() + cards[l].getValue() == 15)
                                    points += 2;
                    }
                }
            }
        }

        //Checking for quints
        if(numCards >= 5)
            if(cards[0].getValue() + cards[1].getValue() + cards[2].getValue() + cards[3].getValue() + cards[4].getValue() == 15)
                points += 2;

        return points;
    }

    int scorePairs() {
        int points = 0;

        for(int i = 0; i < numCards; i++)
            for(int j = i + 1; j < numCards; j++)
                if(cards[i].getIcon() == cards[j].getIcon())
                    points += 2;

        return points;
    }

    int scoreRuns() {
        sortAll();
        int total = 0;

        total += checkRun();

        if(total == numCards) {
            moveCutsToEnd();
            return total;
        }

        for(int i = 0; i < numCards; i++) {
            Deck tempDeck(cards, getNumCards());
            tempDeck.remove(i);
            tempDeck.sortAll();
            int tempScore = tempDeck.checkRun();
            if(tempScore >= 3)
                total += tempScore;
        }

        if(total == 0 && numCards == 5) {
            for(int i = 0; i < numCards; i++) {
                for(int j = i; j < numCards - 1; j++) {
                    Deck tempDeck(cards, getNumCards());
                    tempDeck.remove(i);
                    tempDeck.remove(j);
                    tempDeck.sortAll();
                    int tempScore = tempDeck.checkRun();
                    if(tempScore >= 3)
                        total += tempScore;
                }
            }
        }

        moveCutsToEnd();

        return total;
    }

    protected:
    int checkRun() {
        bool hasRun = true;

        // cout << "\n" << toStringSmall();

        for(int i = 0; i < numCards - 1; i++) {
            // cout << "Current: " << cards[i].getRank() << " | Next: " << cards[i + 1].getRank() << "\n";
            if(cards[i + 1].getRank() != cards[i].getRank() + 1) {
                // cout << "OOF: Current: " << cards[i].getRank() << " | Next: " << cards[i + 1].getRank() << "\n";
                hasRun = false;
                break;
            }
        }

        if(hasRun) {
            // cout << "+" << numCards << "\n";
            return numCards;
        }
        else
            return 0;
    }
    int factorial(int n) {
        if(n > 0)
            return n * factorial(n - 1);
        return 1;
    }

    string findJackSuit() {
        for(int i = 0; i < getNumCards(); i++)
            if(getCard(i).getIcon() == "J")
                return getCard(i).getSuit();

        return "null";
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

    int numPossibleHands() {
        return factorial(getNumCards()) / (2 * factorial(getNumCards() - 2));
    }

    Deck* scoreAllHandsMinusTwo() {
        int numHandsToScore = numPossibleHands();

        int* scores = (int*)malloc(sizeof(int) * numHandsToScore);
        Deck* hands = (Deck*)malloc(sizeof(Deck) * numHandsToScore);
        int count = 0;

        for(int i = 0; i < numCards; i++) {
            for(int j = i; j < numCards - 1; j++) {
                // cout << count << "\n";
                Deck tempDeck(cards, getNumCards());
                tempDeck.remove(i);
                tempDeck.remove(j);
                tempDeck.sort();
                scores[count] = tempDeck.scoreAll();
                hands[count++] = tempDeck;
            }
        }

        bool isMixed = false;
        do {
            isMixed = false;
            for(int i = 0; i < numHandsToScore - 1; i++) {
                if(scores[i] < scores[i + 1]) {
                    int dummyScore = scores[i];
                    scores[i] = scores[i + 1];
                    scores[i + 1] = dummyScore;

                    Deck dummyHand = hands[i];
                    hands[i] = hands[i + 1];
                    hands[i + 1] = dummyHand;

                    isMixed = true;
                }
            }
        } while(isMixed);

        cout << "All possible hands ranked:\n\n";

        for(int i = 0; i < numHandsToScore; i++) {
            // if(scores[i] > 0) {
            if(i > 0 && scores[i] != scores[i - 1])
                cout << "\n";
            cout << "#" << (i + 1) << ": " << scores[i] << "pts - " << hands[i].toStringSmallln();
            // }
        }

        cout << "\n";

        free(scores);
        return hands;
    }

    void scoreAllCuts() {
        int numHandsToScore = 13;
        int* scores = (int*)malloc(sizeof(int) * numHandsToScore);
        Deck* hands = (Deck*)malloc(sizeof(Deck) * numHandsToScore);
        int count = 0;
        int hasAll4 = 0;
        string availSuit;
        string jackSuit = findJackSuit();
        string flushSuit = "null";

        if(scoreFlush() >= 0)
            flushSuit = getCard(0).getSuit();

        for(int i = 0; i < 13; i++) {
            hasAll4 = 0;
            Deck tempDeck = *this;
            for(int j = 0; j < 4; j++) {

                string suit;
                if(j == 0)
                    suit = "c";
                else if(j == 1)
                    suit = "s";
                else if(j == 2)
                    suit = "h";
                else
                    suit = "d";

                Card tempCard = Card(i + 1, suit, true);

                if(tempDeck.contains(tempCard))
                    hasAll4++;
                else {
                    availSuit = tempCard.getSuit();
                    if(flushSuit == tempCard.getSuit() || jackSuit == tempCard.getSuit())
                        break;
                }

            }
            if(hasAll4 < 4) {
                tempDeck.add(Card(i + 1, availSuit, true));
                int score = tempDeck.scoreAll();
                scores[count] = score;
                hands[count++] = tempDeck;
            }
            else
                numHandsToScore--;
        }

        bool isMixed = false;
        do {
            isMixed = false;
            for(int i = 0; i < numHandsToScore - 1; i++) {
                if(scores[i] < scores[i + 1]) {
                    int dummyScore = scores[i];
                    scores[i] = scores[i + 1];
                    scores[i + 1] = dummyScore;

                    Deck dummyHand = hands[i];
                    hands[i] = hands[i + 1];
                    hands[i + 1] = dummyHand;

                    isMixed = true;
                }
            }
        } while(isMixed);

        cout << "All possible cuts ranked:\n\n";

        for(int i = 0; i < numHandsToScore; i++) {
            if(i > 0 && scores[i] != scores[i - 1])
                cout << "\n";
            cout << "#" << (i + 1) << ": " << scores[i] << "pts - " << hands[i].toStringSmallln();
        }

        cout << "\n";

        free(scores);
        free(hands);
    }

    void scoreAllCuts(Deck originalDeck) {
        int numHandsToScore = 13;
        int* scores = (int*)malloc(sizeof(int) * numHandsToScore);
        float* odds = (float*)malloc(sizeof(float) * numHandsToScore);
        Deck* hands = (Deck*)malloc(sizeof(Deck) * numHandsToScore);
        int count = 0;
        int hasAll4 = 0;
        string availSuit;
        string jackSuit = findJackSuit();
        string flushSuit = "null";

        if(scoreFlush() >= 0)
            flushSuit = getCard(0).getSuit();

        for(int i = 0; i < 13; i++) {
            hasAll4 = 0;
            Deck tempDeck = *this;
            for(int j = 0; j < 4; j++) {
                string suit;
                if(j == 0)
                    suit = "c";
                else if(j == 1)
                    suit = "s";
                else if(j == 2)
                    suit = "h";
                else
                    suit = "d";

                Card tempCard = Card(i + 1, suit, true);

                if(tempDeck.contains(tempCard))
                    hasAll4++;
                else {
                    availSuit = tempCard.getSuit();
                    if(flushSuit == tempCard.getSuit() || jackSuit == tempCard.getSuit())
                        break;
                }
            }

            if(hasAll4 < 4) {
                tempDeck.add(Card(i + 1, availSuit, true));
                int score = tempDeck.scoreAll();

                int numOfCurrCard = 0;
                float chance;
                for(int j = 0; j < originalDeck.getNumCards(); j++) {
                    if(originalDeck.getCard(j).getRank() == i + 1)
                        numOfCurrCard++;
                }
                chance = (float)(4 - numOfCurrCard) / (float)(MAX_CARDS - originalDeck.getNumCards());

                scores[count] = score;
                odds[count] = round(chance * 10000) / 100;
                hands[count++] = tempDeck;
            }
            else
                numHandsToScore--;
        }

        bool isMixed = false;
        do {
            isMixed = false;
            for(int i = 0; i < numHandsToScore - 1; i++) {
                if(scores[i] < scores[i + 1]) {
                    int dummyScore = scores[i];
                    scores[i] = scores[i + 1];
                    scores[i + 1] = dummyScore;

                    float dummyOdd = odds[i];
                    odds[i] = odds[i + 1];
                    odds[i + 1] = dummyOdd;

                    Deck dummyHand = hands[i];
                    hands[i] = hands[i + 1];
                    hands[i + 1] = dummyHand;

                    isMixed = true;
                }
            }
        } while(isMixed);

        cout << "All possible cuts ranked:\n\n";

        float runningOdds = 0;

        for(int i = 0; i < numHandsToScore; i++) {
            if(i > 0 && scores[i] != scores[i - 1]) {
                cout << "(" << runningOdds << "% total)\n\n";
                runningOdds = 0;
            }
            cout << "#" << (i + 1) << ": " << scores[i] << "pts - " << hands[i].toStringSmall() << " - (" << odds[i] << "%)\n";
            runningOdds += odds[i];
        }

        cout << "(" << runningOdds << "% total)\n\n";

        free(scores);
        free(hands);
    }

    string toStringSmall() {

        string deckString = "[";

        for(int i = 0; i < getNumCards(); i++) {
            if(!cards[i].isCutCard()) {
                deckString += cards[i].getIcon();
                deckString += cards[i].getSuit();
                deckString += ", ";
            }
        }

        deckString += "\b\b]  ";

        bool foundCutCard = false;

        for(int i = 0; i < getNumCards(); i++) {
            if(cards[i].isCutCard()) {
                if(!foundCutCard) {
                    deckString += "[";
                    foundCutCard = true;
                }
                deckString += cards[i].getIcon();
                deckString += cards[i].getSuit();
                deckString += ", ";
            }
        }

        if(foundCutCard)
            deckString += "\b\b]";

        return deckString;
    }

    string toStringSmallln() {
        return toStringSmall() + "\n";
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

        return cardsString;
    }

    string toStringln() {
        return toString() + "\n";
    }

};
