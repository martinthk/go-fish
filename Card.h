#pragma once
#ifndef CARD_H
#define CARD_H

#include <string>
#include <iostream>
#include <vector>

class Card
{
public:
	Card();
	Card(int, int);
	~Card();
	std::string getRank();	
	std::string getSuit();	
	std::string getId();
	

private:
	std::string suit;
	std::string rank;
	std::string id;
};

#endif // !CARD_H


