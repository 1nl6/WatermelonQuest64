/*
 * Player.h
 *
 */

#pragma once

#ifndef PLAYER_H_
#define PLAYER_H_

#include "Weapon.h"
#include "Enemy.h"
#include "RoomElement.h"

using namespace std;

class Player : public RoomElement{

public:
	//Constructor takes in tileSize
	Player(int avatar, int difficulty, int playerNumber, int tileSize);
	~Player();
	void setAvatar(int avatar,int tileSize);
	void setWeapon(Weapon newWeapon);
	//void addToInventory(Item newItem); // adds an Item to Inventory so player can see it by pressing �I�
	void setScore(int newScore);
	void setSpeed(float newSpeed);
	void setMaximumHP(int newMaxHP);

	void attack(); // play Player's attack animation (stored as a series of sprites that change from frame to frame and as a sound file. Also creates a hurtbox around the Player's weapon that will cause damage to any Enemy that it collides with).
//	void die(); // play Player's dying animation (stored as a series of sprites that change from frame to frame and as a sound file. Afterwards, also displays a Game Over screen)
	Weapon getWeapon();
	void increaseAttackBonus();
	void increaseWatermelonCount();
	int getAttackBonus();
	int getWatermelonCount();
	void useWatermelon();
	int getScore();

	//void move(double deltaX, double deltaY, Room &room, vector<RoomElement *>& o);
	bool doAction(RoomElement *element);
	void setDamage(int weaponDamage);
	sf::Clock invincibilityTimer;
	void setInvincibility(bool);
	bool getInvincibility();
	void setUnmodified();
	bool getModified();

private:
	Weapon weapon;	// weapon the Player currently has equipped
	int score;		// How much score the Player currently has (use the HUD to display)
	bool invincibility;
	bool modified; // for main to check whether the HUD bar needs to be updated or not
	int attackBonus;
	int watermelonCount;
	//vector<Item> inventory; // Used to track what Items the Player currently has (Player can press �I� to pause the game and look at their Inventory)
};

#endif /* PLAYER_H_ */
