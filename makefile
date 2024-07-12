CC = g++
CFLAGS = -g -Wall -pedantic

all : crib

crib : main.cpp Card.cpp Deck.cpp main.h
	$(CC) $(CFLAGS) main.cpp Card.cpp Deck.cpp -o crib

clean :
	- rm *.o crib

