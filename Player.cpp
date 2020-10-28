#include "Player.h"


Player::Player()
{
	score = 0;
}
Player::Player(std::string newName)
{
	setName(newName);
	score = 0;
}


Player::~Player()
{
}

void Player::setName(std::string newName){
	name = newName;
}

std::string Player::getName() {
	return name;
}

void Player::printHand() {
	/*-------Extra Functino------------*/
	int handSize = hand.size();
	for (int q = 0; q < handSize; q++) {
		std::cout << ".--. ";
	}
	std::cout << "\n";
	for (int e = 0; e < handSize; e++) {
		std::cout << "|" << hand[e].getId() << "| ";
	}
	std::cout << "\n";
	for (int r = 0; r < handSize; r++) {
		std::cout << "`--' ";
	}
	std::cout << "\n";
	/*-------------------------------------------------------*/
}

void Player::addCard(Card c){	
	hand.push_back(c);
}

bool Player::holds(std::string r) {
	bool isVaild = false;
	int handSize = hand.size();
	for (int card = 0; card < handSize; card++) {
		Card c = hand[card];
		if (c.getRank() == r) {
			isVaild = true;
		}
	}
	return isVaild;
}

Card Player::takeCard(std::string c) {
	int handSize = hand.size();
	for (int card = 0; card < handSize; card++) {
		if (hand[card].getRank() == c) {
			std::swap(hand[card], hand.back());
			Card d = hand.back();
			hand.pop_back();
			return d;
		}
	}
}

int Player::getBooksCount(){
	return books.size();
}

void Player::listBooks() {
	std::vector < std::string > ::iterator iter;
	for (iter = books.begin(); iter != books.end(); iter++)
		std::cout << (*iter) << "'s ";
	std::cout << "\n";
}

void  Player::checkForBook() {
	int count = 0;
	//r array is for checking as a reference
	std::string r[] = { "A","2","3","4","5","6","7","8","9","10","J","Q","K" };
	//s array is for storing the score
	int s[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13 };
	for (int j = 0; j <= 13; j++) {
		//Reset the count everytime it runs a cycle
		count = 0;
		for (int i = 0; i < hand.size(); i++) {
			if (hand[i].getRank() == r[j]) {
				count++;
			}

			if (count == 4) {
				//This loop is for removing the book set from hand
				for (int k = 0; k < hand.size(); k++) {
					Card card = hand[k];
					Card book;
					if (card.getRank() == r[j]) {
						discard.push_back(card);
						hand.erase(hand.begin() + k);
						book = card;
						k--;
						i--;
						/******Extra Function******/
						//Making different sets of cards worth different points
						score += s[j];
						/******************************************************/
					}
					books.push_back(book.getRank());
				}
				std::cout <<"\n*****" <<getName() << " got a set!  Congratulations!" << " *****"<< std::endl;
			}
		}
	}

}

bool Player::hasCard() {
	//If T = player has card in hand
	//If F = player has no cards in hand
	return (hand.size() > 0);
}

void Player::showPlayerCards() {
	std::cout << "\n\n" << getName() << ", these are your cards:\n";
	printHand();
	
}

//Only for AI
std::string Player::makeMove() {
	srand(time(NULL));
	int randCard = rand() % hand.size();
	std::string c = hand[randCard].getRank();
	return c;
}
