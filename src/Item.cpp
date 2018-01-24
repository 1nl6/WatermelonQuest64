/*
 * Item.cpp
 *
 */

#include "Item.h"
#include "Weapon.h"

Item::Item(int num,int tileSize) {
	if (num == 0){
		setName("Watermelon");
		Load("textures/items/i_watermellon.png",tileSize);
		//SetPosition(100, 250);
	}
	else if (num == 1){
		setName("Armour");
		Load("textures/items/armour.png",tileSize);
		//SetPosition(150, 250);
	}
	else if (num == 2){
		setName("Boots");
		Load("textures/items/boots.png",tileSize);
		//SetPosition(200, 250);
	}
	else if (num == 3){
		setName("Booster");
		Load("textures/items/booster.png",tileSize);
		//SetPosition(300,250);
	}
	/*
	else if (num == 4){
		setName("Freeze");
		Load("textures/items/freeze.png",tileSize);
		//SetPosition(250,250);
	}
	else if (num == 5){
		setName("Push");
		Load("textures/items/push.png",tileSize);
		//SetPosition(350,250);
	}
	 */
	else {
		std::cout << "Something happened here" << std::endl;
	}
}

bool Item::doAction(RoomElement *element){
	//Items only affect players
	if(dynamic_cast<Player *>(element)){
		if(getName() == "Watermelon"){
			//Cannot pick up item if you have 10 watermelons
			if(dynamic_cast<Player *>(element)->getWatermelonCount() == 10)
				return false;
			else {
				(dynamic_cast<Player *>(element))->increaseWatermelonCount();
				cout << "Number of watermelons: " << (dynamic_cast<Player *>(element))->getWatermelonCount() << endl;
			}
		}else if (getName() == "Armour"){
			element->setMaximumHP(element->getMaximumHP() + 5);
			cout << "Max HP is " << element->getMaximumHP() << endl;
		}else if (getName() == "Boots"){
			element->setSpeed(element->getSpeed() * 1.1);
			cout << "Current speed is " << element->getSpeed() << endl;
		} else if (getName() == "Booster"){
			(dynamic_cast<Player *>(element))->increaseAttackBonus();
			cout<< "Attack bonus is " << (dynamic_cast<Player *>(element))->getAttackBonus() << endl;
		}else
			cout<< "Not an item" << endl;
	}
	else if(dynamic_cast<Enemy *>(element))
		return false;
	return true;
}

Item::~Item(){
	std::cout << "Item destroyed" << std::endl;
}
