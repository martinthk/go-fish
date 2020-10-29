#include "Card.h"



Card::Card()
{
}

Card::Card(int s, int r) {
	std::string ranks[] = { "A","2","3","4","5","6","7","8","9","T","J","Q","K" };
	std::string suits[] = { "H","C","D","S" };
	suit = suits[s];
	rank = ranks[r];
	id = rank + suit;
}


Card::~Card()
{
}

std::string Card::getRank() {
	 return rank;
}

std::string Card::getSuit(){
	return suit;
}

std::string Card::getId() {
	return id;
}


