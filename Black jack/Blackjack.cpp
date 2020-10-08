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
	int CalcScore() {
		
		for (int i = 0; i < cards.size(); i++)
		{
			score += cards.at(i);
		}
		if (score > 21) score = 0;

		return score;
	}
};



void drawcard(Player &player) {

	int randint = rand() % 10 + 1;
	player.cards.push_back(randint);

}

void show_card(Player &player) {
	std::cout << "\t\tCards: ";
	for (int i = 0; i < player.cards.size(); i++)
	{
		std::cout << player.cards.at(i) << ' ';
	}
	std::cout << "\n";
}

void info(Player &player) {
	std::cout << "\t\tYou got score of : " << player.score << std::endl;
	std::cout << "\t\tYou got " << player.money << "$ left" << std::endl << std::endl;
}

void compare(Player &house, Player &player) {
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


void inpfromuser(Player &house, Player &player) {
	char todoo;

	std::cout << "do you want to keep cards (k) or draw one more (d)";
	std::cin >> todoo;
	if (todoo == 'k') {
		compare(house, player);
		// std::cout << "you wanted to hold cards";
	}
	else if (todoo == 'd') drawcard(player);
	else{
		std::cout << "Please write a valid input";
		inpfromuser(house, player);
	}
}

void houseai(Player &house, Player &player) {
	if (house.score > 21)
	{

	}
	else if (player.score > house.score)
	{
		drawcard(house);
	}
}

int main() {
	Player player;
	Player house;
	bool game{ true };
	srand(time(NULL));



	drawcard(player);
	drawcard(house);

	do
	{
		house.CalcScore();
		player.CalcScore();
		std::cout << "\t\tplayer\n";
		show_card(player);
		info(player);
		std::cout << "\t\thouse\n";
		show_card(house);
		info(house);
		inpfromuser(house, player);
		houseai(house, player);
		

	} while (game == true);
	
}