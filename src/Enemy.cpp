/*
 * Enemy.cpp
 *
 */

#include <ctime>
#include <string>
#include "stdlib.h"
#include "Enemy.h"
#include "Attack.h"


Enemy::Enemy(int num,int tileSize) {
	//Load enemy (choose between different kinds)

	if(num == 0){
		type = num;
		setMaximumHP(50);
		setCurrentHP(50);
		setDamage(5);
		setDirectionDuration(1);
		Load("textures/enemy/enemy.png",3,4,1,0,tileSize);

		//dropRates = {40,25,8,5,15,5,2}; // follows order of item class, adds up to 100%
		// change these to only 5 instead of 7
		dropRates[0] = 40;
		dropRates[1] = 25;
		dropRates[2] = 8;
		dropRates[3] = 5;
		dropRates[4] = 15;
		dropRates[5] = 5;
		dropRates[6] = 2;

	}else if (num == 1){
		setMaximumHP(100);
		setCurrentHP(100);
		setDamage(10);
		setDirectionDuration(3);
		Load("textures/enemy/enemy2.png",3,4,1,0,tileSize);

		dropRates[0] = 35;
		dropRates[1] = 10;
		dropRates[2] = 25;
		dropRates[3] = 10;
		dropRates[4] = 8;
		dropRates[5] = 8;
		dropRates[6] = 4;
	}
	else if (num == 2){
		setMaximumHP(150);
		setCurrentHP(150);
		setDamage(15);
		setDirectionDuration(2);
		Load("textures/enemy/enemy3.png",3,4,1,0,tileSize);

		dropRates[0] = 30;
		dropRates[1] = 8;
		dropRates[2] = 15;
		dropRates[3] = 20;
		dropRates[4] = 15;
		dropRates[5] = 10;
		dropRates[6] = 2;
	}
	//Boss
	else if (num == 3){
		setMaximumHP(250);
		setCurrentHP(250);
		setDamage(25);
		setDirectionDuration(2);
		Load("textures/enemy/boss2Resize.png",4,4,1,0,tileSize);
	}
	else{
		std::cout << "No enemy" << std::endl;
		return;
	}
	type = num;
	setSpeed(0.04);

}

int Enemy::getType(){
	return type;
}

// decrease every probability and increase the last one (prob of dropping nothing)
void Enemy::setDropRates(int difficulty){
	int noDropProb = dropRates[DROP_NUM-1];
	if (difficulty == 0)
		return;
	else if (difficulty == 1){
		for (int i = 0; i < DROP_NUM-1; i++){
			int noDropAddition = dropRates[i] - dropRates[i]*0.8;
			int newDrop = dropRates[i]*0.8;
			dropRates[i] = newDrop;
			noDropProb += noDropAddition;
		}
	}
	else if (difficulty == 2){
		for (int i = 0; i < DROP_NUM-1; i++){
			int noDropAddition = dropRates[i] - dropRates[i]*0.65;
			int newDrop = dropRates[i]*0.65;
			dropRates[i] = newDrop;
			noDropProb += noDropAddition;
		}
	}
	else
		std::cout << "Something weird happened here" << std::endl;
}



int* Enemy::getDropRates(){
	return dropRates;
}

int Enemy::dropItem(){
	srand(static_cast<unsigned int>(time(NULL)));
	int randSeed(1+rand()%100); // generate a random number between 1 and 100

	int *dropRates = this->getDropRates();

	// each item has a range between 1 and 100
	// if randSeed falls between that range, that particular item drops
	int meter = 1; int item = 0;
	for (item = 0; item < DROP_NUM; item++){
		if (randSeed >= meter && randSeed < meter+dropRates[item]){
			break; // falls between the range we are currently in so drop this item
		}
		else if (item == (DROP_NUM-1)){ // if we have already reached the last element in the array, no dropped item
			break;
		}
		else {
			meter = meter+dropRates[item]; // move to the next item
			continue;
		}
	}
	return item; // index of item to put into constructor of a new item we're creating
}

//std::string Enemy::dropWeapon(int dropIndex){
//	std::string weaponName;
//	if (dropIndex == DROP_NUM-2)
//		weaponName = "sword";
//	else if (dropIndex == DROP_NUM-3)
//		weaponName = "mace";
//	else
//		std::cout << "You're using the wrong function; you shouldn't have even ended up here" << std::endl;
//	return weaponName;
//}

//drops the other one? - spawn that weapon you just had in main, one tile over with checks for boundaries?



/*
void Enemy::die(){
	getSprite().setColor(sf::Color(255,255,255,0));

}
 */

bool Enemy::doAction(RoomElement *element){
	if(dynamic_cast<Player *>(element)){
		//If the player isn't in invincibility mode, reduce HP
		if(!((dynamic_cast<Player *>(element))->getInvincibility())){
			element->setCurrentHP(element->getCurrentHP()- getDamage());
			cout <<"Current HP: " << element->getCurrentHP() <<endl;
			(dynamic_cast<Player *>(element))->setInvincibility(true);
		}
		return false;
	}
	else if(dynamic_cast<Enemy *>(element))
		return false;
	else if(dynamic_cast<Attack *>(element)){
		//Check if its a fatal blow and give points
		int newHP = getCurrentHP() - element->getDamage();
		if(newHP <= 0){
			int currentScore = dynamic_cast<Attack *>(element)->getPlayer()->getScore();
			dynamic_cast<Attack *>(element)->getPlayer()->setScore(currentScore + (type+1)*50);
		}
		//Reduce health of enemy
		setCurrentHP(newHP);
		cout << "Enemy's HP is " << getCurrentHP() << endl;
	}

	return true; //return false
}

void Enemy::setDirectionDuration(int direction)
{
	directionDuration = direction;
}
int Enemy::getDirectionDuration()
{
	return directionDuration;
}

void Enemy::setSpriteCount(int spriteValue)
{
	spriteCount = spriteValue;
}
int Enemy::getSpriteCount()
{
	return spriteCount;
}

