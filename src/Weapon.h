/*
 * Weapon.h
 *
 */

#pragma once

#ifndef WEAPON_H_
#define WEAPON_H_
#include <string>

//#include "Player.h"
#include "RoomElement.h"

using namespace std;
/* Weapon class will never directly be used, but actual
 * weapons in the game will inherit from the Weapon class
 * (for example, we may make a MagicSword class, which
 * inherits from Weapon)
 */

class Weapon : public RoomElement {

public:
	Weapon();
	Weapon(int dam, string n, int tileSize);
	~Weapon();
	//int getDamage();
	bool doAction(RoomElement *element);
	bool doAction(RoomElement *element, vector<RoomElement *> &o);
	string getName();
private:
	//int damage; // How much damage Enemies take when they are hit by the Weapon
	string name; //user-readable name of the Weapon (ex. �Excalibur�, �Holy Hand Grenade of Antioch�, etc.)
};

#endif /* WEAPON_H_ */
