#include "main.h"

//♣ ♠ ♥ ♦

class Card {
    private:
    int value;
    string suit;
    string icon;
    int sortValue;
    bool cutCard;

    public:
    Card() {
        value = -1;
        sortValue = -1;
        suit = "💣";
        icon = "💣";
        cutCard = false;
    }
    Card(bool cut) {
        value = -1;
        sortValue = -1;
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
        sortValue = iconToSortValue(ico);
        cutCard = false;
    }
    Card(int val, string su) {
        sortValue = val;

        if(su == "c" || su == "C")
            su = "♣";
        else if(su == "s" || su == "S")
            su = "♠";
        else if(su == "h" || su == "H")
            su = "♥";
        else if(su == "d" || su == "D")
            su = "♦";

        suit = su;
        icon = sortValueToIcon(val);
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
        sortValue = iconToSortValue(ico);
        cutCard = cut;
    }
    Card(int val, string su, bool cut) {
        sortValue = val;

        if(su == "c" || su == "C")
            su = "♣";
        else if(su == "s" || su == "S")
            su = "♠";
        else if(su == "h" || su == "H")
            su = "♥";
        else if(su == "d" || su == "D")
            su = "♦";

        suit = su;
        icon = sortValueToIcon(val);
        value = iconToValue(icon);
        cutCard = cut;
    }

    int getValue() {
        return value;
    }
    void setValue(int val) {
        value = val;
        sortValue = val;
    }

    int getSortValue() {
        return sortValue;
    }

    string getSuit() {
        return suit;
    }
    void setSuit(string s) {
        suit = s;
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
        sortValue = iconToSortValue(i);
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

    int iconToSortValue(string ico) {

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

    string sortValueToIcon(int sortValue) {
        if(sortValue == 11)
            return "J";
        else if(sortValue == 12)
            return "Q";
        else if(sortValue == 13)
            return "K";
        else if(sortValue == 1)
            return "A";
        else
            return to_string(sortValue);
    }

    std::string toString() {

        char extraSpace = ' ';

        if(icon == "10")
            extraSpace = '\0';

        return "-------\n|" + suit + "    |\n" + "|  " + icon + " " + extraSpace + "|\n" + "|    " + suit + "|\n" + "-------\n";

    }

};
