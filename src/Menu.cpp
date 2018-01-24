/*
 * Menu.cpp
 *
 */

#include "Menu.h"
#include <string>
#include <iostream>

using namespace std;

int difficulty = 0;
int playerAmount = 2;
int avatar1 = 1;
int avatar2 = 3;

MainSettingScreen::MainSettingScreen(float width, float height)
{
	isVisible = false;
	avatarSame = false;

	if (!font.loadFromFile("fonts/game.ttf")) {
		// handle error
	}
	menu[0].setFont(font);
	menu[0].setColor(sf::Color::Red);
	menu[0].setString("Number of Players: 1");
	menu[0].setPosition(sf::Vector2f(width * 0.01, height / (MAX_ITEMS + 1) * 1));
	menu[0].setCharacterSize(35);

	menu[1].setFont(font);
	menu[1].setColor(sf::Color::White);
	menu[1].setString("Player-One Avatar: 1");
	menu[1].scale(0.75, 0.75);
	menu[1].setPosition(sf::Vector2f(width * 0.01, height / (MAX_ITEMS + 1) * 2 + 50));
	menu[1].setCharacterSize(35);

	menu[2].setFont(font);
	menu[2].setColor(sf::Color::White);
	menu[2].setString("Player-Two Avatar: 1");
	menu[2].scale(0.75, 0.75);
	menu[2].setPosition(sf::Vector2f(width * 0.01, height / (MAX_ITEMS + 1) * 4));
	menu[2].setCharacterSize(35);

	menu[3].setFont(font);
	menu[3].setColor(sf::Color::White);
	menu[3].setString("Difficulty: Easy");
	menu[3].scale(0.75, 0.75);
	menu[3].setPosition(sf::Vector2f(width * 0.01, height / (MAX_ITEMS + 1) * 5 + 50));
	menu[3].setCharacterSize(35);

	menu[4].setFont(font);
	menu[4].setColor(sf::Color::White);
	menu[4].setString("Back");
	menu[4].setPosition(sf::Vector2f(width / 2 - 100, height / (MAX_ITEMS + 1) * 7));
	menu[4].setCharacterSize(45);

	menu[5].setFont(font);
	menu[5].setColor(sf::Color::White);
	menu[5].setString("Settings");
	menu[5].setPosition(sf::Vector2f(width / 2 - 200, height / (MAX_ITEMS) - 200));
	menu[5].setCharacterSize(60);

	menu[6].setFont(font);
	menu[6].setColor(sf::Color::Red);
	menu[6].setString("Player avatars cannot be the same");
	menu[6].scale( 0.5, 0.5);
	menu[6].setPosition(sf::Vector2f(width * 0.01, height / (MAX_ITEMS + 1) * 6));
	menu[6].setCharacterSize(40);

	spriteOne.setPosition(sf::Vector2f(width * 0.9, height/(MAX_ITEMS + 1) * 2 + 50));
	spriteOne.scale(sf::Vector2f(2, 2));

	spriteTwo.setPosition(sf::Vector2f(width * 0.9, height/(MAX_ITEMS + 1) * 4));
	spriteTwo.scale(sf::Vector2f(2, 2));

	selectedItemIndex = 0;
}

int MainSettingScreen::getAvatarOne() {
	return avatarOne;
}

int MainSettingScreen::getAvatarTwo() {
	return avatarTwo;
}

sf::Sprite MainSettingScreen::getSpriteOne() {
	return spriteOne;
}

sf::Sprite MainSettingScreen::getSpriteTwo() {
	return spriteTwo;
}

bool MainSettingScreen::visible() {
	return isVisible;
}

bool MainSettingScreen::sameAvatar() {
	return avatarSame;
}

void MainSettingScreen::setAvatarCheck() {
	if(avatarOne == avatarTwo) {
		avatarSame = true;
	}
	if(avatarOne != avatarTwo) {
		avatarSame = false;
	}
}

void MainSettingScreen::draw(sf::RenderWindow &window) {
	for (int i = 0; i < MAX_ITEMS - 1; i++) {
		window.draw(menu[i]);
	}
	sf::Texture textureOne;
	sf::Texture textureTwo;
	switch(avatarOne) {
	case 1:
		textureOne.loadFromFile("textures/player/femalePlayerSmall.png");
		break;
	case 2:
		textureOne.loadFromFile("textures/player/femalePlayer2Small.png");
		break;
	case 3:
		textureOne.loadFromFile("textures/player/femalePlayer3Small.png");
		break;
	case 4:
		textureOne.loadFromFile("textures/player/malePlayerSmall.png");
		break;
	case 5:
		textureOne.loadFromFile("textures/player/malePlayer2Small.png");
		break;
	case 6:
		textureOne.loadFromFile("textures/player/malePlayer3Small.png");
		break;
	}
	switch(avatarTwo) {
	case 1:
		textureTwo.loadFromFile("textures/player/femalePlayerSmall.png");
		break;
	case 2:
		textureTwo.loadFromFile("textures/player/femalePlayer2Small.png");
		break;
	case 3:
		textureTwo.loadFromFile("textures/player/femalePlayer3Small.png");
		break;
	case 4:
		textureTwo.loadFromFile("textures/player/malePlayerSmall.png");
		break;
	case 5:
		textureTwo.loadFromFile("textures/player/malePlayer2Small.png");
		break;
	case 6:
		textureTwo.loadFromFile("textures/player/malePlayer3Small.png");
		break;
	}
	spriteOne.setTexture(textureOne, true);
	spriteTwo.setTexture(textureTwo, true);
	window.draw(getSpriteOne());
	if(visible() == true) {
		window.draw(getSpriteTwo());
	}
	setAvatarCheck();
	if(sameAvatar() == true) {
		window.draw(menu[6]);
	}
	window.display();
}

//check if multiplayer is selected, if not, skip
void MainSettingScreen::MoveUp() {

	if(menu[0].getString() == "Number of Players: 1") {
		//***make it so that it skips over selectedItemIndex 2
		if(selectedItemIndex - 1 >= 0) {
			menu[selectedItemIndex].setColor(sf::Color::White);
			if(selectedItemIndex == 3) {
				selectedItemIndex--;
				selectedItemIndex--;
			}
			else {
				selectedItemIndex--;
			}
			menu[selectedItemIndex].setColor(sf::Color::Red);
		}
	}
	else {
		if(selectedItemIndex - 1 >= 0) {
			menu[selectedItemIndex].setColor(sf::Color::White);
			selectedItemIndex--;
			menu[selectedItemIndex].setColor(sf::Color::Red);
		}
	}
}

//check if multiplayer is selected, if not, skip
void MainSettingScreen::MoveDown() {
	if(menu[0].getString() == "Number of Players: 1") {
		if(selectedItemIndex + 1 < MAX_ITEMS - 1) {
			menu[selectedItemIndex].setColor(sf::Color::White);
			if(selectedItemIndex == 1) {
				selectedItemIndex++;
				selectedItemIndex++;
			}
			else {
				selectedItemIndex++;
			}
			menu[selectedItemIndex].setColor(sf::Color::Red);
		}
	}
	else {
		if(selectedItemIndex + 1 < MAX_ITEMS - 1) {
			menu[selectedItemIndex].setColor(sf::Color::White);
			selectedItemIndex++;
			menu[selectedItemIndex].setColor(sf::Color::Red);
		}
	}
}

void MainSettingScreen::MoveLeft(sf::RenderWindow &window) {
	if(selectedItemIndex == ONE) {
		if(menu[1].getString() == "Player-One Avatar: 1") {
			menu[1].setString("Player-One Avatar: 6");
			avatar1 = 6;
			avatarOne = 6;
		}
		else if(menu[1].getString() == "Player-One Avatar: 6") {
			menu[1].setString("Player-One Avatar: 5");
			avatar1 = 5;
			avatarOne = 5;
		}
		else if(menu[1].getString() == "Player-One Avatar: 5") {
			menu[1].setString("Player-One Avatar: 4");
			avatar1 = 4;
			avatarOne = 4;
		}
		else if(menu[1].getString() == "Player-One Avatar: 4") {
			menu[1].setString("Player-One Avatar: 3");
			avatar1 = 3;
			avatarOne = 3;
		}
		else if(menu[1].getString() == "Player-One Avatar: 3") {
			menu[1].setString("Player-One Avatar: 2");
			avatar1 = 2;
			avatarOne = 2;
		}
		else if(menu[1].getString() == "Player-One Avatar: 2") {
			menu[1].setString("Player-One Avatar: 1");
			avatar1 = 1;
			avatarOne = 1;
		}
	}
	if(selectedItemIndex == TWO) {
		if(menu[2].getString() == "Player-Two Avatar: 1") {
			menu[2].setString("Player-Two Avatar: 6");
			avatar2 = 6;
			avatarTwo = 6;
		}
		else if(menu[2].getString() == "Player-Two Avatar: 6") {
			menu[2].setString("Player-Two Avatar: 5");
			avatar2 = 5;
			avatarTwo = 5;
		}
		else if(menu[2].getString() == "Player-Two Avatar: 5") {
			menu[2].setString("Player-Two Avatar: 4");
			avatar2 = 4;
			avatarTwo = 4;
		}
		else if(menu[2].getString() == "Player-Two Avatar: 4") {
			menu[2].setString("Player-Two Avatar: 3");
			avatar2 = 3;
			avatarTwo = 3;
		}
		else if(menu[2].getString() == "Player-Two Avatar: 3") {
			menu[2].setString("Player-Two Avatar: 2");
			avatar2 = 2;
			avatarTwo = 2;
		}
		else if(menu[2].getString() == "Player-Two Avatar: 2") {
			menu[2].setString("Player-Two Avatar: 1");
			avatar2 = 1;
			avatarTwo = 1;
		}
	}
	if(selectedItemIndex == ZERO) {
		if(menu[0].getString() == "Number of Players: 1") {
			menu[0].setString("Number of Players: 2");
			playerAmount = 2;
			isVisible = true;
		}
		else if(menu[0].getString() == "Number of Players: 2") {
			menu[0].setString("Number of Players: 1");
			playerAmount = 1;
			avatar2 = 0;
			isVisible = false;
		}
	}
	if(selectedItemIndex == THREE) {
		if(menu[3].getString() == "Difficulty: Easy") {
			menu[3].setString("Difficulty: Hard");
			difficulty = 2;
		}
		else if(menu[3].getString() == "Difficulty: Hard") {
			menu[3].setString("Difficulty: Medium");
			difficulty = 1;
		}
		else if(menu[3].getString() == "Difficulty: Medium") {
			menu[3].setString("Difficulty: Easy");
			difficulty = 0;
		}
	}
}

void MainSettingScreen::MoveRight(sf::RenderWindow &window) {
	if(selectedItemIndex == ONE) {
		if(menu[1].getString() == "Player-One Avatar: 1") {
			menu[selectedItemIndex].setString("Player-One Avatar: 2");
			avatar1 = 2;
			avatarOne = 2;
		}
		else if(menu[1].getString() == "Player-One Avatar: 2") {
			menu[selectedItemIndex].setString("Player-One Avatar: 3");
			avatar1 = 3;
			avatarOne = 3;
		}
		else if(menu[1].getString() == "Player-One Avatar: 3") {
			menu[selectedItemIndex].setString("Player-One Avatar: 4");
			avatar1 = 4;
			avatarOne = 4;
		}
		else if(menu[1].getString() == "Player-One Avatar: 4") {
			menu[selectedItemIndex].setString("Player-One Avatar: 5");
			avatar1 = 5;
			avatarOne = 5;
		}
		else if(menu[1].getString() == "Player-One Avatar: 5") {
			menu[selectedItemIndex].setString("Player-One Avatar: 6");
			avatar1 = 6;
			avatarOne = 6;
		}
		else if(menu[1].getString() == "Player-One Avatar: 6") {
			menu[selectedItemIndex].setString("Player-One Avatar: 1");
			avatar1 = 1;
			avatarOne = 1;
		}
	}
	if(selectedItemIndex == TWO) {
		if(menu[2].getString() == "Player-Two Avatar: 1") {
			menu[2].setString("Player-Two Avatar: 2");
			avatar2 = 2;
			avatarTwo = 2;
		}
		else if(menu[2].getString() == "Player-Two Avatar: 2") {
			menu[2].setString("Player-Two Avatar: 3");
			avatar2 = 3;
			avatarTwo = 3;
		}
		else if(menu[2].getString() == "Player-Two Avatar: 3") {
			menu[2].setString("Player-Two Avatar: 4");
			avatar2 = 4;
			avatarTwo = 4;
		}
		else if(menu[2].getString() == "Player-Two Avatar: 4") {
			menu[2].setString("Player-Two Avatar: 5");
			avatar2 = 5;
			avatarTwo = 5;
		}
		else if(menu[2].getString() == "Player-Two Avatar: 5") {
			menu[2].setString("Player-Two Avatar: 6");
			avatar2 = 6;
			avatarTwo = 6;
		}
		else if(menu[2].getString() == "Player-Two Avatar: 6") {
			menu[2].setString("Player-Two Avatar: 1");
			avatar2 = 1;
			avatarTwo = 1;
		}
	}
	if(selectedItemIndex == ZERO) {
		if(menu[0].getString() == "Number of Players: 1") {
			menu[0].setString("Number of Players: 2");
			playerAmount = 2;
			isVisible = true;
		}
		else if(menu[0].getString() == "Number of Players: 2") {
			menu[0].setString("Number of Players: 1");
			playerAmount = 1;
			avatar2 = 0;
			isVisible = false;
		}
	}
	if(selectedItemIndex == THREE) {
		if(menu[3].getString() == "Difficulty: Easy") {
			menu[3].setString("Difficulty: Medium");
			difficulty = 1;
		}
		else if(menu[3].getString() == "Difficulty: Medium") {
			menu[3].setString("Difficulty: Hard");
			difficulty = 2;
		}
		else if(menu[3].getString() == "Difficulty: Hard") {
			menu[3].setString("Difficulty: Easy");
			difficulty = 0;
		}
	}
}

void MainSettingScreen::Enter() {
	if(selectedItemIndex == FOUR) {
		if(sameAvatar() == false) {
		// go back to main screen
		}
	}
}

MainSettingScreen::~MainSettingScreen() {}



TitleScreen::TitleScreen(float titleWidth, float titleHeight) : MainSettingScreen(titleWidth, titleHeight) {
	this->titleWidth = titleWidth;
	this->titleHeight = titleHeight;
	if (!titleFont.loadFromFile("fonts/game.ttf")) {
		// handle error
	}
	titleMenu[0].setFont(titleFont);
	titleMenu[0].setColor(sf::Color::Magenta);
	titleMenu[0].setString("WATERMELON QUEST 64");
	titleMenu[0].setPosition(sf::Vector2f(titleWidth / 10, titleHeight / (MAX_ITEMS + 1) * 1));

	titleMenu[1].setFont(titleFont);
	titleMenu[1].setColor(sf::Color::Green);
	titleMenu[1].setString("PLAY");
	titleMenu[1].setPosition(sf::Vector2f(titleWidth / 10, titleHeight / (MAX_ITEMS + 1) * 2));

	titleMenu[2].setFont(titleFont);
	titleMenu[2].setColor(sf::Color::Green);
	titleMenu[2].setString("SETTINGS");
	titleMenu[2].setPosition(sf::Vector2f(titleWidth / 10, titleHeight / (MAX_ITEMS + 1) * 3));

	titleMenu[3].setFont(titleFont);
	titleMenu[3].setColor(sf::Color::Green);
	titleMenu[3].setString("EXIT");
	titleMenu[3].setPosition(sf::Vector2f(titleWidth / 10, titleHeight / (MAX_ITEMS + 1) * 4));

	titleMenu[4].setFont(titleFont);
	titleMenu[4].setColor(sf::Color::Blue);
	titleMenu[4].setString("Team Zuse Inc, 2016.");
	titleMenu[4].setPosition(sf::Vector2f(titleWidth / 10, titleHeight / (MAX_ITEMS + 1) * 6));

	selectedItemIndex = 1;
}


void TitleScreen::draw(sf::RenderWindow & window) {
	for (int i = 0; i < FIVE; i++)
		window.draw(titleMenu[i]);
}

void TitleScreen::MoveUp() {
	cout << "Selected Item Index: " << selectedItemIndex<<endl;

	if (selectedItemIndex > 2 || selectedItemIndex == 4) {
		selectedItemIndex--;
		titleMenu[selectedItemIndex-1].setColor(sf::Color::White);
		titleMenu[selectedItemIndex].setColor(sf::Color::Green);
	}
	cout <<" Menu choice: " << selectedItemIndex << endl;
}

void TitleScreen::MoveDown() {
	cout << "Selected Item Index: " << selectedItemIndex<<endl;
	if (selectedItemIndex == 1) {
		titleMenu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex++;
	}

	else if (selectedItemIndex + 1 < 5 && selectedItemIndex > 1) {
		titleMenu[selectedItemIndex].setColor(sf::Color::White);
		titleMenu[selectedItemIndex-1].setColor(sf::Color::Green);
		selectedItemIndex++;
	}

	cout << "Menu Choice: " <<selectedItemIndex << endl;
}


void TitleScreen::Enter() {}

TitleScreen::~TitleScreen() {
	cout<<"Title screen destroyed";
}

GameOverScreen::GameOverScreen(float gameOverWidth, float gameOverHeight) : MainSettingScreen(gameOverWidth, gameOverHeight) {
	this->gameOverWidth = gameOverWidth;
	this->gameOverHeight = gameOverHeight;
	if (!gameOverFont.loadFromFile("fonts/game.ttf")) {
			// handle error
		}
		gameOverMenu[0].setFont(gameOverFont);
		gameOverMenu[0].setColor(sf::Color::Red);
		gameOverMenu[0].setString("GAME OVER");
		gameOverMenu[0].scale(2,2);
		gameOverMenu[0].setPosition(sf::Vector2f(gameOverWidth / 2 - 225, gameOverHeight / (MAX_ITEMS + 1) * 1));

		gameOverMenu[1].setFont(gameOverFont);
		gameOverMenu[1].setColor(sf::Color::Green);
		gameOverMenu[1].setString("And some watermelons...");
		gameOverMenu[1].scale(0.75, 0.75);
		gameOverMenu[1].setPosition(sf::Vector2f(gameOverWidth / 10, gameOverHeight * 0.8));

		gameOverMenu[2].setFont(gameOverFont);
		gameOverMenu[2].setColor(sf::Color::Green);
		gameOverMenu[2].setString("Were never seen again.");
		gameOverMenu[2].scale(0.75, 0.75);
		gameOverMenu[2].setPosition(sf::Vector2f(gameOverWidth / 10, gameOverHeight * 0.9));
		selectedItemIndex = 0;
}

void GameOverScreen::draw(sf::RenderWindow & window) {
	sf::Texture gameOverPic;
	gameOverPic.loadFromFile("textures/images/nomoremelons.jpg");
	sf::Sprite sprite(gameOverPic);
	sprite.setPosition(gameOverWidth * 0.01, gameOverHeight * 0.25);
	sprite.scale(2,2);
	window.draw(sprite);

	for (int i =0; i< MAX_ITEMS; i++)
		window.draw(gameOverMenu[i]);
}

GameOverScreen::~GameOverScreen() {
	cout<<"Game over screen destroyed";
}

YouWinScreen::YouWinScreen(float youWinWidth, float youWinHeight) : MainSettingScreen(youWinWidth, youWinHeight) {
	this->youWinWidth = youWinWidth;
	this->youWinHeight = youWinHeight;
	if (!winFont.loadFromFile("fonts/game.ttf")) {} // handle error

	winMenu[0].setFont(winFont);
	winMenu[0].setColor(sf::Color::Red);
	winMenu[0].setString("YOU WIN!");
	winMenu[0].scale(2,2);
	winMenu[0].setPosition(sf::Vector2f(youWinWidth / 2 - 175, youWinHeight * 0.1));
	/*youWinHeight / (MAX_ITEMS + 1) * 2)*/
	winMenu[1].setFont(winFont);
	winMenu[1].setColor(sf::Color::Red);
	winMenu[1].setString("now... enjoy a watermelon!");
	winMenu[1].scale(0.9, 0.9);
	winMenu[1].setPosition(sf::Vector2f(youWinWidth * 0.001 + 10, youWinHeight * 0.9));
}
	//youWinHeight / (MAX_ITEMS + 1) * 6)
void YouWinScreen::draw(sf::RenderWindow & window) {
	sf::Texture youWinPic;
	youWinPic.loadFromFile("textures/images/happy_melon.jpg");
	sf::Sprite sprite(youWinPic);
	sprite.setPosition(youWinWidth * 0.0001, youWinHeight * 0.25 );
	sprite.scale(2,2);
	window.draw(sprite);

	for (int i =0; i< MAX_ITEMS; i++)
		window.draw(winMenu[i]);
}

YouWinScreen::~YouWinScreen() {}
