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
		score = 0;
		for (int i = 0; i < cards.size(); i++)
			score += cards.at(i);
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
		std::cout << player.cards.at(i) << ' ';
	std::cout << "\n";
}

void info(Player &player) {
	std::cout << "\t\tYou got score of : " << player.score << std::endl;
	std::cout << "\t\tYou got " << player.money << "$ left" << std::endl << std::endl;
}

void compare(Player &house, Player &player, int &pot) {
	if (player.score == house.score){
		player.money += pot / 2;
		house.money += pot / 2;
		std::cout << "match is draw, both gets money back\n";
	}
	else if (player.score > house.score) {
		player.money += pot;
		std::cout << "player won, players gets the pot\n";
	}
	else if(house.score > player.score){
		house.money += pot;
		std::cout << "House won, house keeps the pot\n";
	}

	std::cout << "\t\tHouse got score of " << house.score << std::endl;
	show_card(house);
	std::cout << "\t\tYou got score of " << player.score << std::endl;
	show_card(player);
}


void inpfromuser(Player &house, Player &player, bool &draw) {
	char todoo;
	player.CalcScore();
	if (player.score == 0) {
		std::cout << "You passed 21\n";
		draw = false;
		return;
	}

	std::cout << "do you want to keep cards (k) or draw one more (d)";
	todoo = _getch();
	std::cout << std::endl;

	if (todoo == 'd') drawcard(player);
	else if (todoo == 'k') draw = false;
	else{
		std::cout << "Please write a valid input\n";
		inpfromuser(house, player, draw);
	}
}
int placebet(Player &house ,Player &player) {
	int bet;
	int pot{20};
	
	std::cout << "how much would you like to bet? ";
	std::cin >> bet;
	
	if (player.money - bet < 0 || house.money - bet < 0)
	{
		std::cout << "one of the players do not have enough money to bet \n";
		placebet(house, player);
	}
	else {
		system("cls");
		pot += 2 * bet;
		std::cout << "you betted " << bet << "$\n"
			<< "house will match and total pot is: " << pot << "$\n";
		house.money -= bet;
		player.money -= bet;
	}
	return pot;
}

void startround(Player &house, Player &player) {
	std::cout << "every new game takes 10 $" << std::endl ;
	house.money -= 10;
	player.money -= 10;
	std::cout << "bank has drawn 10$ from each account" << std::endl;

	//draw two cards star of round
	for (int i{ 0 }; i < 2; i++) {
		drawcard(player);
		drawcard(house);
	}
	
}


void houseai(Player &house, Player &player) {
	house.CalcScore();
	player.CalcScore();

	while (player.score > house.score) {
		// choose if ace is 1 or 11 
		for (int i{ 0 }; i < house.cards.size(); i++) {
			if (house.cards.at(i) == 1 || house.cards.at(i) == 11)
			{
				house.cards.at(i) == 11;
				house.CalcScore();
				if (house.score == 0 || house.score > 17) {
					house.cards.at(i) == 1;
					house.CalcScore();
		}	}	}
		//house not allowed to draw if score is more than 17
		if (house.score > 17) return;
		drawcard(house);
		house.CalcScore();
		player.CalcScore();
		//if house bust then return.
		if (house.score == 0) return;
	}
}

void ifAce(Player &player) {
	int ace;
	for (int i = 0; i < player.cards.size(); i++)
	{
		if (player.cards.at(i) == 1) {
			std::cout << "Do you want your ace to be valued 1 or 11? ";
			std::cin >> ace;
			player.cards.at(i) = ace;
		}	
	}	
}

void clear_round(Player &house, Player &player) {
	player.cards.clear();
	house.cards.clear();
	std::cout << "cards cleared\n";
}

int main() {
	Player player;
	Player house;
	int pot;
	bool game{ true };
	bool draw{ true };
	std::string broke;

	srand(time(NULL));

	//run game
	do
	{
		
		//ends game if anyone broke
		if (house.money == 0 || player.money == 0) {
			game == false;
			break;
		}
		startround(house, player);
		draw = true;

		//show player cards
		std::cout << std::endl << "\t\t    Your Deck\n";
		show_card(player);
		player.CalcScore();
		house.CalcScore();
		info(player);

		//show first house card
		std::cout << "\n\t\t\tHouse\n\t\tCards: " << house.cards.at(0); 
		for (int j = 0; j < house.cards.size()-1; j++)std::cout << " X ";
			std::cout << std::endl
			<< "\t\tHouse got " << house.money << "$ left"<< std::endl <<std::endl ;

		pot = placebet(house, player);
		
		//run draw sequence
		do
		{
			system("cls");
			house.CalcScore();
			player.CalcScore();

			std::cout << std::endl << "\t\t    Your Deck\n";
			show_card(player);
			info(player);

			//prints houses money
			std::cout << "\n\t\t\tHouse\n\t\tCards: " << house.cards.at(0);
			for (int j = 0; j < house.cards.size()-1; j++)std::cout << " X ";
			std::cout << std::endl
				<< "\t\tHouse got " << house.money << "$ left" << std::endl << std::endl;

			ifAce(player);
			house.CalcScore();
			inpfromuser(house, player, draw);
			houseai(house, player);

		} while (draw == true);

		compare(house, player, pot);
		//clears house and players cards.
		clear_round(house, player);
		system("pause");
		system("cls");

	} while (game);

	// checks who is broke 
	if (house.money == 0) broke = "house";
	else if (player.money == 0) broke = "You";
	std::cout << "well played " << broke << " got broke\n";
}