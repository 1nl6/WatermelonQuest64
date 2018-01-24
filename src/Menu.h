/*
 * Menu.h
 *
 */

#ifndef MENU_H_
#define MENU_H_

#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#define MAX_ITEMS 7
#define ZERO 0
#define ONE 1
#define TWO 2
#define THREE 3
#define FOUR 4
#define FIVE 5

extern int difficulty;
extern int playerAmount;
extern int avatar1;
extern int avatar2;

class MainSettingScreen
{
public:
	MainSettingScreen(float width, float height);
	virtual ~MainSettingScreen();
	virtual void draw(sf::RenderWindow &window);
	virtual void MoveUp();
	virtual void MoveDown();
	void MoveLeft(sf::RenderWindow &window);
	void MoveRight(sf::RenderWindow &window);
	virtual void Enter();
	virtual int GetPressedItem() { return selectedItemIndex; }
	sf::Sprite getSpriteOne();
	sf::Sprite getSpriteTwo();
	int getAvatarOne();
	int getAvatarTwo();
	void setAvatarCheck();
	void SetPosition(float x, float y);
	bool visible();
	bool sameAvatar();

protected:
	int selectedItemIndex;

private:
	int avatarOne;
	int avatarTwo;
	sf::Sprite spriteOne;
	sf::Sprite spriteTwo;
	bool isVisible;
	bool avatarSame;
	sf::Font font;
	sf::Text menu[MAX_ITEMS];
};

class TitleScreen: public MainSettingScreen {
public:
	TitleScreen(float titleWidth, float titleHeight);
	~TitleScreen();

	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	void Enter();
	int GetPressedItem() {return selectedItemIndex;}

private:
	float titleWidth, titleHeight;
	sf::Font titleFont;
	sf::Text titleMenu[FIVE];
};

class GameOverScreen: public MainSettingScreen {
public:
	GameOverScreen(float gameOverWidth, float gameOverHeight);
	~GameOverScreen();

	void draw(sf::RenderWindow &window);

private:
	float gameOverWidth, gameOverHeight;
	sf::Font gameOverFont;
	sf::Text gameOverMenu[MAX_ITEMS];
};

class YouWinScreen: public MainSettingScreen {
public:
	YouWinScreen(float youWinWidth, float youWinHeight);
	~YouWinScreen();

	void draw(sf::RenderWindow &window);

private:

	float youWinWidth, youWinHeight;
	sf::Font winFont;
	sf::Text winMenu[MAX_ITEMS];
};

#endif /* MENU_H_ */
