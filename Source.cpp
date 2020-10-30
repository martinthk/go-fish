#include "Card.h"
#include "Player.h"
#include <iostream>
#include <ctime>
#include <sstream>
#include <fstream>


void shuffle();
Card draw();
std::string read();
void showBooks(Player, Player);
std::string getInput(Player);
Card fish(Player, Player);
//void process(std::string, Player, Player);


std::vector <Card> cards;	//For storing an unshuffled deck
std::vector <Card> cards2;	//For shuffling use, will be empty after shuffle
std::vector <Card> shuffled;	//For storing shuffled deck


//If turn = 1 --> Player's turn
//If turn = 2 --> Ai's turn 
int turn = 1;

int main() {
	std::cout << read() << std::endl;
	std::string pName;
	std::cout << "Hello, please enter your name: ";
	std::cin >> pName;
	Player p1(pName);

	std::string aiName;
	std::cout << "\nAlso, please assgin me a name :D ";
	std::cin >> aiName;
	Player ai(aiName);
	//std::cout << "My assgined name is: " << ai.getName() << std::endl;

	Card deck;
	int CardNum = 0;	//For checking does the program successfuly generate the number of cards I want
	//Initialization card string, make sure it does not store anything
	//Using 2D array's concept to generate a deck

	//**Iterate through suits
	for (int i = 0; i < 4; i++) {
		//**Iterate through ranks
		for (int j = 0; j < 13; j++) {
			Card newCard(i, j);

			//Add card to vectors
			cards.push_back(newCard);
			cards2.push_back(newCard);

			//Raise card number by 1 for each time adding 1 card to the deck
			CardNum++;
		}
	}

	//[For checking only] Print unshuffle deck
	  /*for (int w = 0; w <52; w++){
	   std::cout<<cards[w].getId()<<std::endl;
   }
   std::cout << "==================================" << std::endl;*/

   //Suffle the deck after generated 52 cards
	shuffle();

	//[For checking only] Print shuffled deck 
	/*for (int e = 0; e < 52; e++) {
		std::cout << shuffled[e].getId() << std::endl;
	}
	std::cout << "==================================" << std::endl;*/

	//Dealing cards to each player
	/***Extra Functions***/
	int n;
	std::cout << "\n" << p1.getName() << ", how many cards do you want in the initial hand dealt ? (3/5/7) ";
	std::cin >> n;
	for (int i = 0; i < n; i++)
	{
		p1.addCard(draw());
		ai.addCard(draw());
	}
	/*********************************************************/


	while (shuffled.size() > 0 && (p1.getBooksCount() + ai.getBooksCount() < 13)) {


		//Player's turn
		while (turn == 1) {
			std::string c = getInput(p1);	//c is the card player asked for
			//If AI has the card
			if (ai.holds(c)) {
				//Keep looping if p2 still have that rank
				if (ai.holds(c)) {
					//Taking the rquested rank from AI & add it to player
					p1.addCard(ai.takeCard(c));
					p1.checkForBook();
					turn = 1;
				}
				//If the AI dun have any more cards that means Go Fish 
			}
			else {
				p1.addCard(fish(p1, ai));
				p1.checkForBook();
			}
			p1.showPlayerCards();
			std::cout << "\n\n";
			showBooks(p1, ai);
			turn = 2;
		}

		//AI's turn 
		if (turn == 2) {
			std::string c = ai.makeMove();
			if (ai.hasCard()) {
				std::string b;
				std::cout << "\nDo you have any " << c << " 's? (Y)es/ (G)o Fish ";
				std::cin >> b;
				bool hasIt = p1.holds(c);
				//if (b != "Y" && b != "G") {

				//}
				if (b == "Y" && !hasIt) {
					std::cout << "No!!! You don't hane it!!!\n";
				}
				if (b == "G" && hasIt) {
					std::cout << "I know you're trying to cheat.....\n";
				}

				if (p1.holds(c)) {
					//Keep looping if p2 still have that rank
					while (p1.holds(c)) {
						//Taking the rquested rank from AI & add it to player
						ai.addCard(p1.takeCard(c));
						ai.checkForBook();
						turn = 2;
					}
					//If the AI dun have any more cards that means 
				}
				else {
					fish(p1, ai);
					ai.checkForBook();
					turn = 1;

				}
			}
			else {
				for (int i = 0; i < 7; i++) {
					ai.addCard(draw());
				}
			}
		}
		std::cout << "\n\n";
		showBooks(p1, ai);
		turn = 1;
	}

		//Endgame display
		if (p1.getBooksCount() > ai.getBooksCount()) {
			std::cout << "\n\n\t*** !!! CONGRATULATIONS !!! ***\n\n\n";
		}
		else {
			std::cout << "\n\n\t*** !!! YOU LOSE - HA HA HA !!! ***\n\n\n";
		}
		system("pause");
		return 0;
}






void shuffle()
{
	std::vector <Card> ::iterator iter;
	for (iter = cards.begin(); iter != cards.end(); iter++) {
		srand(time(NULL));
		int ranCard = rand() % cards2.size();
		shuffled.push_back(cards2[ranCard]);
		//same result as "Shuffled.push_back(*(card2.begin() + ranCard));"
		cards2.erase(cards2.begin() + ranCard);
	}
}

std::string read() {
	std::ifstream readParagraph;
	readParagraph.open("Description.txt");
	std::stringstream ss;
	std::string  paragraph;
	while (std::getline(readParagraph, paragraph))
	{
		ss << paragraph << "\n";
	}
	return ss.str();
}

Card draw() {
	Card c;
	if (shuffled.size() > 0) {
		c = shuffled.back();
		shuffled.pop_back();
		return c;
	}
}

void showBooks(Player p1, Player p2) {
	if (p1.getBooksCount() > 0) {
		std::cout << "\nYour Book(s): ";
		p1.listBooks();
	}
	if (p2.getBooksCount() > 0) {
		std::cout << "\nMy Book(s): ";
		p2.listBooks();
	}
}

std::string getInput(Player p1) {
	std::string c;
	//Check if it is player turn 
	if (turn == 1) {
		if (p1.hasCard()) {
			p1.showPlayerCards();
			while (turn == 1)
			{
				std::cout << "\n" << p1.getName() << ", what rank do you want? ";
				std::cin >> c;

				//Check if the player actually has at least one rank of that card in hand 
				if (p1.holds(c) == false) {
					std::cout << p1.getName() << " , you can't ask for a card you don't have!!!\n\n";

				}
				else {
					return c;
				}
			}
		}
		//The player has run out of cards but there are some left in the deck so deal them
		//**another hand of 7 cards or however many are left.
		else {
			for (int i = 0; i < 7; i++) {
				p1.addCard(draw());
			}
		}

	}
	return c;
}



Card fish(Player p1, Player p2) {
	std::cout << "\n\n\t  #### GO FISH! ####\n\n";
	Card newCard = draw();
	if (turn == 1) {
		std::cout << "Your new card is: " << newCard.getId() << ".\n\n======== Your turn is over! ========\n" << "\n\n";
		return newCard;

	}
	if (turn == 2) {
		std::cout << "\n========= My turn is over! =========\n" << "\n\n";
		return newCard;
	}
}

