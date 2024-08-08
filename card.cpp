#include "main.h"

//♣ ♠ ♥ ♦

class Card {
    private:
    int value;
    string suit;
    string icon;
    int rank;
    bool cutCard;

    public:
    Card() {
        value = -1;
        rank = -1;
        suit = "💣";
        icon = "💣";
        cutCard = false;
    }
    Card(bool cut) {
        value = -1;
        rank = -1;
        suit = "💣";
        icon = "💣";
        cutCard = cut;
    }
    Card(string ico, string su) {
        icon = ico;
        if(su == "c" || su == "C")
            su = "♣";
        else if(su == "s" || su == "S")
            su = "♠";
        else if(su == "h" || su == "H")
            su = "♥";
        else if(su == "d" || su == "D")
            su = "♦";

        suit = su;
        value = iconToValue(ico);
        rank = iconToRank(ico);
        cutCard = false;
    }
    Card(int rnk, string su) {
        rank = rnk;

        if(su == "c" || su == "C")
            su = "♣";
        else if(su == "s" || su == "S")
            su = "♠";
        else if(su == "h" || su == "H")
            su = "♥";
        else if(su == "d" || su == "D")
            su = "♦";

        suit = su;
        icon = rankToIcon(rnk);
        value = iconToValue(icon);
        cutCard = false;
    }
    Card(string ico, string su, bool cut) {
        icon = ico;
        if(su == "c" || su == "C")
            su = "♣";
        else if(su == "s" || su == "S")
            su = "♠";
        else if(su == "h" || su == "H")
            su = "♥";
        else if(su == "d" || su == "D")
            su = "♦";

        suit = su;
        value = iconToValue(ico);
        rank = iconToRank(ico);
        cutCard = cut;
    }
    Card(int rnk, string su, bool cut) {
        rank = rnk;

        if(su == "c" || su == "C")
            su = "♣";
        else if(su == "s" || su == "S")
            su = "♠";
        else if(su == "h" || su == "H")
            su = "♥";
        else if(su == "d" || su == "D")
            su = "♦";

        suit = su;
        icon = rankToIcon(rnk);
        value = iconToValue(icon);
        cutCard = cut;
    }

    int getValue() {
        return value;
    }
    void setValue(int val) {
        value = val;
        rank = val;
    }

    int getRank() {
        return rank;
    }

    string getSuit() {
        return suit;
    }
    void setSuit(string s) {
        if(s == "c" || s == "C" || s == "♣")
            suit = "♣";
        else if(s == "s" || s == "S" || s == "♠")
            suit = "♠";
        else if(s == "h" || s == "H" || s == "♥")
            suit = "♥";
        else if(s == "d" || s == "D" || s == "♦")
            suit = "♦";
    }
    bool isClub() {
        return getSuit() == "♣";
    }
    bool isSpade() {
        return getSuit() == "♠";
    }
    bool isHeart() {
        return getSuit() == "♥";
    }
    bool isDiamond() {
        return getSuit() == "♦";
    }

    string getIcon() {
        return icon;
    }
    void setIcon(string i) {
        icon = i;
        value = iconToValue(i);
        rank = iconToRank(i);
    }

    bool isCutCard() {
        return cutCard;
    }
    void setCutCard(bool cut) {
        cutCard = cut;
    }

    int iconToValue(string ico) {

        if(icon == "J" || icon == "Q" || icon == "K")
            return 10;
        else if(icon == "A")
            return 1;
        else
            return stoi(icon);

    }

    int iconToRank(string ico) {

        if(icon == "J")
            return 11;
        else if(icon == "Q")
            return 12;
        else if(icon == "K")
            return 13;
        else if(icon == "A")
            return 1;
        else
            return stoi(icon);

    }

    string rankToIcon(int rank) {
        if(rank == 11)
            return "J";
        else if(rank == 12)
            return "Q";
        else if(rank == 13)
            return "K";
        else if(rank == 1)
            return "A";
        else
            return to_string(rank);
    }

    bool equals(Card card) {
        return getSuit() == card.getSuit() && getIcon() == card.getIcon() && getRank() == card.getRank();
    }

    string toStringSmall() {
        return "[" + getIcon() + getSuit() + "]";
    }

    string toString() {

        char extraSpace = ' ';

        if(icon == "10")
            extraSpace = '\0';

        return "-------\n|" + suit + "    |\n" + "|  " + icon + " " + extraSpace + "|\n" + "|    " + suit + "|\n" + "-------\n";

    }

};
