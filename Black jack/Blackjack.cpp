#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <vector>
#include <string>
#include <time.h>

class Player {
public:
	int money{100};
	std::vector<int> cards;
	int score{0};
	void CalcScore() {
		
		for (int i = 0; i < cards.size(); i++)
		{
			score += cards.at(i);
		}
		if (score > 21) score = 0;
	}
};
Player player;
Player house;

/*
void drawcard_player() {

	int randint = rand() % 10 + 1;
	player.cards.push_back(randint);
	
	std::cout << "your cards: ";
	for (int i = 0; i < player.cards.size(); i++)
	{
		std::cout << player.cards.at(i) << ' ';
	}
	std::cout << "\n";
}

*/
void drawcard(Player test) {

	int randint = rand() % 10 + 1;
	test.cards.push_back(randint);

}

void show_card(Player test) {
	std::cout << "\t\tCards: ";
	for (int i = 0; i < test.cards.size(); i++)
	{
		std::cout << test.cards.at(i) << ' ';
	}
	std::cout << "\n";
}

void info(Player test) {
	std::cout << "\t\tYou got score of : " << test.score << std::endl;
	std::cout << "\t\tYou got " << test.money << "$ left" << std::endl << std::endl;
}
/*
void infohouse() {
	std::cout << "\t\thouse got score of : " << house.score << std::endl;
	std::cout << "\t\thouse got " << house.money << "$ left" << std::endl;
}
*/
void compare() {
	if (player.score == house.score){
		std::cout << "draw";
	}
	else if (player.score > house.score) {
		std::cout << "player won";
	}
	else if(house.score > player.score){
		std::cout << "House won";
	}
}


void inpfromuser() {
	char todoo;

	std::cout << "do you want to keep cards (k) or draw one more (d)";
	std::cin >> todoo;
	if (todoo == 'k') {
		compare();
		std::cout << "you wanted to hold cards";
	}
	else if (todoo == 'd') drawcard(player);
	else{
		std::cout << "Please write a valid input";
		inpfromuser();
	}
}

void houseai() {
	if (house.score > 21)
	{

	}
	else if (player.score > house.score)
	{
		drawcard(house);
	}
}

int main() {
	bool game{ true };
	srand(time(NULL));



	drawcard(player);
	drawcard(house);

	do
	{
		std::cout << "\t\tplayer\n";
		show_card(player);
		info(player);
		std::cout << "\t\thouse\n";
		show_card(house);
		info(house);
		inpfromuser();
		houseai();
		

	} while (game == true);
	
}