/*
 * Weapon.cpp
 *
 */

#include "Weapon.h"
#include "Player.h"
#include <string>

using namespace std;

Weapon::Weapon() {
	setDamage(0);
	//damage = 0;
	name = "default";
}

Weapon::Weapon(int dam, string n, int tileSize) {
	setDamage(dam);
	name = n;

	Load("textures/weapons/" + name + ".png",tileSize);
}

Weapon::~Weapon() {}

/*
int Weapon::getDamage(){
	return damage;
}
*/
bool Weapon::doAction(RoomElement *element){
	if(dynamic_cast<Player *>(element)){
		(dynamic_cast<Player *>(element))->setWeapon(*this);
		return true;
	}
	else if(dynamic_cast<Enemy *>(element))
		return false;
	return true;
}

string Weapon::getName(){
	return name;
}
