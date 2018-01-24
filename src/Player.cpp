/*
 * Player.cpp
 *
 */

#include "Player.h"
#include <string>
#include <sstream>

Player::Player(int avatar, int difficulty, int playerNumber, int tileSize) {
	//Load avatar
	setAvatar(avatar,tileSize);

	//Set position of avatar based on player number
	if(playerNumber == 1){
		SetPosition(0,400);
		setName("Player 1");
	}else{
		SetPosition(50,250);
		setName("Player 2");
	}

	//Set initial HP based on difficulty
	if(difficulty == 0){
		setMaximumHP(100);
		setCurrentHP(100);
		std::cout << getCurrentHP() << std::endl;
	}
	else if(difficulty == 1){
		setMaximumHP(75);
		setCurrentHP(75);
	}
	else if(difficulty == 2){
		setMaximumHP(50);
		setCurrentHP(50);
	}

	setSpeed(0.1);
	score = 0;
	attackBonus = 0;
	watermelonCount = 0;
	invincibility = false;
	modified = false;
	setWeapon(Weapon(20, "default weapon",tileSize));
}

Player::~Player() {}

//Load appropriate avatar
void Player::setAvatar(int avatar, int tileSize){
	switch(avatar){
	case 0:
		return;
	case 1:
		Load("textures/player/femalePlayer.png",3,4,1,0,tileSize);
		break;
	case 2:
		Load("textures/player/femalePlayer2.png",3,4,1,0,tileSize);
		break;
	case 3:
		Load("textures/player/femalePlayer3.png",3,4,1,0,tileSize);
		break;
	case 4:
		Load("textures/player/malePlayer.png",3,4,1,0,tileSize);
		break;
	case 5:
		Load("textures/player/malePlayer2.png",3,4,1,0,tileSize);
		break;
	case 6:
		Load("textures/player/malePlayer3.png",3,4,1,0,tileSize);
		break;
	}
}

void Player::setWeapon(Weapon newWeapon){
	weapon = newWeapon;
	setDamage(getWeapon().getDamage());
	cout << "Weapon Set!" << endl;
	modified = true;
}
/*
void Player::addToInventory(Item newItem){
	// Should we clone?
	inventory.push_back(newItem);
}
 */

void Player::setScore(int newScore){
	score = newScore;
	modified = true;
}

//Cap on speed for player is 0.15
void Player::setSpeed(float newSpeed){
	if(newSpeed < 0.15)
		RoomElement::setSpeed(newSpeed);
	else
		RoomElement::setSpeed(0.15);
}

// Cap on Max HP for player is 150
void Player::setMaximumHP(int newMaxHP){
	if(newMaxHP < 150)
		RoomElement::setMaximumHP(newMaxHP);
	else
		RoomElement::setMaximumHP(150);
	modified = true;
}

void Player::attack(){

}

Weapon Player::getWeapon(){
	return weapon;
}

// Increase attack by 1 (Cap of 10)
void Player::increaseAttackBonus(){
	if(attackBonus < 10)
		attackBonus++;
	cout << "Before increasing damage: " << getDamage() << endl;
	setDamage(getDamage()+1);
	cout << "After increasing damage: " << getDamage() << endl;
	modified = true;

}

// Cap watermelons in inventory to 10
void Player:: increaseWatermelonCount(){
	if(watermelonCount < 10)
		watermelonCount++;
	modified = true;
}

int Player::getAttackBonus(){
	return attackBonus;
}

int Player::getWatermelonCount(){
	return watermelonCount;
}

int Player::getScore(){
	return score;
}

void Player::useWatermelon(){
	if(watermelonCount > 0 && getCurrentHP() != getMaximumHP()){
		setCurrentHP(getCurrentHP() + 5);
		cout << "Used watermerlon. Current HP is " << getCurrentHP() << endl;
		watermelonCount--;
		modified = true;
	}else
		return;
}

bool Player::doAction(RoomElement *element){
	if(dynamic_cast<Player *>(element))
		return false;
	else if(dynamic_cast<Enemy *>(element)){
		setCurrentHP(getCurrentHP() - element->getDamage());
		setInvincibility(true);
		return false;
	}return true;	//return false
}

void Player::setDamage(int weaponDamage){
	RoomElement::setDamage(weaponDamage + attackBonus);
}


void Player::setInvincibility(bool set){
	//If invincibility is already turned on, do nothing
	if(set==true && invincibility == true){
		return;
	}//invincibility turned off and set is true
	else if(set== true && invincibility == false){
		invincibility = true;
		invincibilityTimer.restart();
		getSprite()->setColor(sf::Color(255,128,128,128));
	}
	else if(set == false){
		invincibility = false;
		getSprite()->setColor(sf::Color(255,255,255,255));
	}
}

bool Player::getInvincibility(){
	return invincibility;
}


void Player::setUnmodified(){
	modified = false;
}

bool Player::getModified(){
	return modified;
}
