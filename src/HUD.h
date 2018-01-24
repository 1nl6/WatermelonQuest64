/*
 * HUD.h
 *
 */

#pragma once

#ifndef HUD_H_
#define HUD_H_

#include "Player.h"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <string>
#include <iostream>

#define MAX_STATS 10

class HUD {
public:
	HUD(float width, float height, int numPlayers, Player *player1, Player *player2);
	~HUD();

	void Draw(sf::RenderWindow &window); // draw on the window that we make in main

	void setScore(int newScore,int playerNumber);
	void setWatermelonCount(int newWmCount, int playerNumber);
	void setWeaponModifier(int newDamage, int playerNumber, Player *player);
	void setAttackBonus(int newAtkBonus, int playerNumber);

private:
	sf::Text menu[MAX_STATS];
	sf::RectangleShape bg;
	sf::Font font;

	sf::String scoreText;
	sf::String scoreText2;

	sf::Texture wmTexture;
	sf::Sprite wmSprite;
	sf::Sprite wmSprite2;

	sf::Texture weaponTexture;
	sf::Sprite weaponSprite;
	sf::Texture weaponTexture2;
	sf::Sprite weaponSprite2;

	sf::Texture boosterTexture;
	sf::Sprite boosterSprite;
	sf::Sprite boosterSprite2;
};

class HealthBar {
public:
	HealthBar(int maxHealth, float width, float height, int playerNumber);
	~HealthBar();

	void Draw(sf::RenderWindow &window);

	void changeHealth(int currentHealth, int maxHealth);
private:
	sf::Texture healthTexture;
	sf::Sprite healthSprite;
	sf::Text currHealth;
	sf::String hpFraction;
	sf::Font font;
	sf::Vector2f defaultScale;
	sf::RectangleShape maxBar;
};

static sf::String toDrawable(int toDisplay);

#endif /* HUD_H_ */
