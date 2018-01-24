/*
 * HUD.cpp
 *
 */

#include "HUD.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <string>
#include <iostream>
#include <sstream>

// could scale the sprites as well
HUD::HUD(float width, float height, int numPlayers, Player *player1, Player *player2){

	int roomBoundary = height - (width/6);
	int HUDheight = height - roomBoundary;

	if (!font.loadFromFile("fonts/arial.ttf"))
	{
		std::cout << "Error loading font from file" << std::endl;
	}

	bg.setSize(sf::Vector2f(width, HUDheight));
	bg.setPosition(0,roomBoundary);
	bg.setFillColor(sf::Color::Yellow);
	bg.setOutlineColor(sf::Color::Black);

	// rectangle needs an outline, which isn't showing up
	// just make sure to pass in players and player number in the correct order so they're displayed correctly

	for (int i = 0; i < MAX_STATS; i++){
		menu[i].setFont(font);
		menu[i].setColor(sf::Color::Black);
		menu[i].setCharacterSize(width/30);
	}

	// GET RID OF ALL THESE MAGIC NUMBERS YOU FILTHY CODER

	menu[0].setString("Player 1");
	menu[0].setPosition(sf::Vector2f(width / 20, height - roomBoundary / 6));

	// watermelons
	if(wmTexture.loadFromFile(std::string("textures/items/i_watermellon.png")) == false){
		std::cout << "Error loading texture from file" << std::endl;
	}
	wmSprite.setTexture(wmTexture);
	wmSprite.setPosition(sf::Vector2f(width/20,height - roomBoundary / 15));

	menu[2].setString(toDrawable(player1->getWatermelonCount()));
	menu[2].setPosition(sf::Vector2f(width*3/20, height - roomBoundary / 15));

	weaponTexture = (player1->getWeapon()).getTexture();
	//weaponSprite = (player1->getWeapon()).getSprite();
	weaponSprite.setTexture(weaponTexture);
	weaponSprite.setPosition(sf::Vector2f(width/5, height - roomBoundary / 15));

	// need some more text, a plus?
	menu[3].setString(toDrawable((player1->getWeapon()).getDamage()));
	menu[3].setPosition(sf::Vector2f(width*3/10, height - roomBoundary/ 15));

	if(boosterTexture.loadFromFile(std::string("textures/items/booster.png")) == false){
			std::cout << "Error loading texture from file" << std::endl;
		}
	boosterSprite.setTexture(boosterTexture);
	boosterSprite.setPosition(width*7/20, height - roomBoundary / 15);

	menu[4].setString(toDrawable(player1->getAttackBonus()));
	menu[4].setPosition(sf::Vector2f(width*9/20, height - roomBoundary / 15));

	if (player2 != nullptr){

		scoreText = "Score: ";
		scoreText += toDrawable(player1->getScore());

		menu[1].setString(scoreText);
		menu[1].setPosition(sf::Vector2f(width / 20 + width/4, height - roomBoundary / 6));

		menu[5].setString("Player 2");
		menu[5].setPosition(sf::Vector2f(width / 20 + width/2, height - roomBoundary / 6));

		scoreText2 = "Score: ";
		scoreText2 += toDrawable(player2->getScore());

		menu[6].setString(scoreText2);
		menu[6].setPosition(sf::Vector2f(width / 20 + width/2 + width/4, height - roomBoundary / 6));

		// is aliasing a bad idea?
		wmSprite2 = wmSprite;
		wmSprite2.setPosition(sf::Vector2f(width/20 + width/2,height - roomBoundary / 15));

		menu[7].setString(toDrawable(player2->getWatermelonCount()));
		menu[7].setPosition(sf::Vector2f(width*3/20 + width/2, height - roomBoundary / 15));

		weaponTexture2 = (player2->getWeapon()).getTexture();
		//weaponSprite = (player1->getWeapon()).getSprite();
		weaponSprite2.setTexture(weaponTexture2);
		weaponSprite2.setPosition(sf::Vector2f(width/5 + width/2, height - roomBoundary / 15));

		menu[8].setString(toDrawable((player2->getWeapon()).getDamage()));
		menu[8].setPosition(sf::Vector2f(width*3/10 + width / 2, height - roomBoundary/ 15));

		boosterSprite2 = boosterSprite;
		boosterSprite2.setPosition(width*7/20 + width/2, height - roomBoundary / 15);

		menu[9].setString(toDrawable(player2->getAttackBonus()));
		menu[9].setPosition(sf::Vector2f(width*9/20 + width/2, height - roomBoundary / 15));
	}
	else {
		sf::String scoreText = "Score: ";
		scoreText += toDrawable(player1->getScore());

		menu[1].setString(scoreText);
		menu[1].setPosition(sf::Vector2f(width / 20 + width/2, height - roomBoundary / 6));
	}
}
HUD::~HUD(){

}

void HUD::Draw(sf::RenderWindow &window){
	window.draw(bg);
	window.draw(wmSprite);
	window.draw(wmSprite2);
	window.draw(weaponSprite);
	window.draw(weaponSprite2);
	window.draw(boosterSprite);
	window.draw(boosterSprite2);

	for (int i = 0; i < MAX_STATS; i++)
		window.draw(menu[i]);
}

void HUD::setScore(int newScore, int playerNumber){
	if (playerNumber == 1){
		scoreText = "Score: ";
		scoreText += toDrawable(newScore);
		menu[1].setString(scoreText);
	}
	else if (playerNumber == 2){
		scoreText2 = "Score: ";
		scoreText2 += toDrawable(newScore);
		menu[6].setString(scoreText2);
	}
	else {
		std::cout << "Check your player number" << std::endl;
	}

}

void HUD::setWatermelonCount(int newWmCount, int playerNumber){
	if (playerNumber == 1){
			menu[2].setString(toDrawable(newWmCount));
		}
		else if (playerNumber == 2){
			menu[7].setString(toDrawable(newWmCount));
		}
		else {
			std::cout << "Check your player number" << std::endl;
		}
}

void HUD::setWeaponModifier(int newDamage, int playerNumber, Player *player){
	if (playerNumber == 1){
		weaponTexture = (player->getWeapon()).getTexture();
		weaponSprite.setTexture(weaponTexture);
		menu[3].setString(toDrawable(newDamage));
	}
	else if (playerNumber == 2){
		weaponTexture2 = (player->getWeapon()).getTexture();
		weaponSprite2.setTexture(weaponTexture2);
		menu[8].setString(toDrawable(newDamage));
	}
	else {
		std::cout << "Check your player number" << std::endl;
	}
}

void HUD::setAttackBonus(int newAtkBonus, int playerNumber){
	if (playerNumber == 1){
			menu[4].setString(toDrawable(newAtkBonus));
		}
		else if (playerNumber == 2){
			menu[9].setString(toDrawable(newAtkBonus));
		}
		else {
			std::cout << "Check your player number" << std::endl;
		}
}

HealthBar::HealthBar (int maxHealth, float width, float height, int playerNumber){
	int roomBoundary = height - (width/6);
	maxBar.setOutlineColor(sf::Color::Black);
	maxBar.setOutlineThickness(2);
	//maxBar.setSize(sf::Vector2f(width/4,width/24));
	maxBar.setSize(sf::Vector2f(150,25));

	if(!healthTexture.loadFromFile("textures/blood_red_bar.png")){
		std::cout << "Error loading texture from file" << std::endl;
	}
	healthTexture.setSmooth(true);
	healthSprite.setTexture(healthTexture);

//	int scaleFactor = 1;
//	if (width < 600){
//		scaleFactor = (600-width)/600;
//	}
//	else if (width > 600){
//		scaleFactor = scaleFactor + (width-600)/width;
//	}
	defaultScale = sf::Vector2f(0.5f,0.7f);
	healthSprite.setScale(defaultScale);

	if (!font.loadFromFile("fonts/arial.ttf"))
	{
	    std::cout << "Error loading texture from file" << std::endl;
	}
	currHealth.setFont(font);
	currHealth.setColor(sf::Color::Black);
	currHealth.setCharacterSize(width/30);

	hpFraction = toDrawable(maxHealth);
	hpFraction += "/";
	hpFraction += toDrawable(maxHealth);

	currHealth.setString(hpFraction);

	if (playerNumber == 1){
		maxBar.setPosition(sf::Vector2f(width / 20, height - roomBoundary / 8));
		healthSprite.setPosition(sf::Vector2f(width / 20, height - roomBoundary / 8));
		currHealth.setPosition(sf::Vector2f(width / 3, height - roomBoundary / 8));
	}
	else if (playerNumber == 2){
		maxBar.setPosition(sf::Vector2f(width / 20 + width / 2, height - roomBoundary / 8));
		healthSprite.setPosition(sf::Vector2f(width / 20 + width / 2, height - roomBoundary / 8));
		currHealth.setPosition(sf::Vector2f(width / 3 + width /2, height - roomBoundary / 8));
	}
	else
		std::cout << "Something weird happened here" << std::endl;

}

void HealthBar::Draw (sf::RenderWindow &window){
	window.draw(maxBar);
	window.draw(healthSprite);
	window.draw(currHealth);
}

void HealthBar::changeHealth(int currentHealth, int maxHealth){
	// HOLY FUCK IT WORKS YEEESSSSSSSS THANK YOU GOD ALL MIGHTY
	healthSprite.setScale(defaultScale.x*currentHealth/maxHealth, defaultScale.y);

	hpFraction = toDrawable(currentHealth);
	hpFraction += "/";
	hpFraction += toDrawable(maxHealth);
	currHealth.setString(hpFraction);

}

static sf::String toDrawable(int toDisplay){
	std::ostringstream ss;
	ss.clear();
	ss << toDisplay;
	sf::String s;
	s += ss.str();
	return s;
}
