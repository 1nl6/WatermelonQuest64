/*
 * Enemy.h
 *
 */

#ifndef ENEMY_H_
#define ENEMY_H_

#include "Weapon.h"
#include "Player.h"
#include "RoomElement.h"
/*
 * Enemy class will never directly be used,
 * but actual enemies in the game will inherit
 * from the Enemy class (for example, we may
 * make a Zombie class, which inherits from Enemy)
 *
 */

#define DROP_NUM 7

class Enemy : public RoomElement{
public:
	Enemy(int num, int tileSize);
	void attack(); // play Enemy's attack animation (stored as a series of sprites that change from frame to frame and as a sound file. Also creates a hurtbox that will cause damage to the Player if they collide with it)
	//void die();  //play Enemy's dying animation (stored as a series of sprites that change from frame to frame and as a sound file. Also reduces radius to 0 once animation begins so Player isn't hurt by Enemies in the middle of their death animations).

	void setDropRates(int difficulty); // set drop rates based on difficulty
	int* getDropRates();
	int dropItem(); // generates a random item based on the dropRates probabilities and gets index to initialize item with, follows the item class constructor order of items
	std::string dropWeapon(int dropIndex);

	bool doAction(RoomElement *element);
	int getType();

	void setSpriteCount(int spriteValue);
	int getSpriteCount();
	void setDirectionDuration(int direction);
	int getDirectionDuration();

	sf::Clock walkClock;

private:
	int dropRates[DROP_NUM]; // Probabilities of each item dropping which follows the Item class order in the constructor, last one is probability of dropping nothing
	//int visibility;
	int type;

	int directionDuration;
	int spriteCount;
};

#endif /* ENEMY_H_ */
