#include "main.h"

//♣ ♠ ♥ ♦

class Card {
    private:
    int value;
    string suit;
    string icon;

    public:

    Card() {
        value = -1;
        suit = "💣";
        icon = "💣";
    }

    Card(string ico, string su) {
        icon = ico;
        suit = su;
        value = iconToValue(ico);
    }

    int getValue() {
        return value;
    }
    void setValue(int val) {
        value = val;
    }

    string getSuit() {
        return suit;
    }
    void setSuit(string s) {
        suit = s;
    }

    string getIcon() {
        return icon;
    }
    void setIcon(string i) {
        icon = i;
        value = iconToValue(i);
    }

    int iconToValue(string ico) {

        if(icon == "J" || icon == "Q" || icon == "K")
            return 10;
        else if(icon == "A")
            return 1;
        else
            return stoi(icon);

    }

    std::string toString() {

        char extraSpace = ' ';

        if(icon == "10")
            extraSpace = '\0';

        return "-------\n|" + suit + "    |\n" + "|  " + icon + " " + extraSpace + "|\n" + "|    " + suit + "|\n" + "-------\n";

    }

};
