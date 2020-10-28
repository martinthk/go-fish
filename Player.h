#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
#include <algorithm>
#include <ctime>

class Player
{
public:
	Player();
	Player(std::string);
	~Player();
	void setName(std::string);
	void printHand();
	void listBooks();
	void checkForBook();
	void addCard(Card);
	void showPlayerCards();
	std::string getName();
	std::string makeMove(); //For AI only
	Card takeCard(std::string);

	int getBooksCount();
	bool holds(std::string);
	bool hasCard();
	

private:
	std::string name;
	std::vector <Card> hand;	 
	std::vector <Card> discard;
	std::vector < std::string > books;
	int score;
};

#endif // !PLAYER_H



