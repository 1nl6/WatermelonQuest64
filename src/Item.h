/*
 * Item.h
 *
 */

#ifndef ITEM_H_
#define ITEM_H_

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#include "RoomElement.h"
#include "Weapon.h"
#include "Player.h"

using namespace std;

class Item : public RoomElement{

public:
	Item(int num, int tileSize);
	~Item();
	bool doAction(RoomElement *element); // called in the main method in order to apply the Item's rule to the game
private:
	 //string name; // user-readable name of the Item

};

#endif /* ITEM_H_ */
