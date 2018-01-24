/*
 * Attack.cpp
 */

#include "Attack.h"
Attack::Attack(Player* player, int tileSize, int x, int y, vector<RoomElement *> e) {
	int dam = player->getDamage();
	setPlayer(player);
	setDamage(dam);			//Need to set damage so that the doAction can access the Attack's damage through getDamage()

	//Load("textures/player_attack.png", tileSize);

	Load("textures/weapons/" + player->getWeapon().getName() + ".png", tileSize); //Axe sprite
	SetPosition(x, y);

	//Check if enemy is attacked
	for (unsigned int i = 0; i < e.size(); ++i){
		RoomElement* o = e.at(i);
		if(dynamic_cast<Enemy *>(o)){
			sf::IntRect attackRect = sf::IntRect(x,y,tileSize*getScale(), tileSize*getScale());
			sf::IntRect enemyRect = sf::IntRect(o->getPosition().x, o->getPosition().y,( o->getElementWidth())*(o->getScale()), (o->getElementHeight())*(o->getScale()));
			if(collision(attackRect, enemyRect)){
				o->doAction(this);
				/*
				o->setCurrentHP((o->getCurrentHP()) - damage);
				std::cout << "Enemy's curent HP: " << o->getCurrentHP() << std::endl;
				//Check if enemy has died
				if(o->getCurrentHP ()<=0){
					(dynamic_cast<Enemy *>(o))->die();
					cout<< "Enemy has died" << endl;
				}
				*/
			}
		}
	}
}

Attack::~Attack() {
}

void Attack::setPlayer(Player *p){
	player = p;
}

Player* Attack::getPlayer(){
	return player;
}
/*
int Attack::getDamage(){
	return damage;
}
*/
