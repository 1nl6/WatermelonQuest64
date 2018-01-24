/*
 * Attack.h
 *
 */

#ifndef ATTACK_H_
#define ATTACK_H_

#include "RoomElement.h"
#include "Enemy.h"
#include "Weapon.h"

/*
 * Attack class is created when a Player attacks, and lasts for a few
 * frames before being deleted. If it collides with an Enemy, it damages
 * it.
 */

class Attack : public RoomElement{
public:
	Attack(Player *player, int tileSize, int x, int y, vector<RoomElement *> elementsInRoom);
	~Attack();
	void setPlayer(Player *player);
	Player* getPlayer();
	sf::Clock attackClock;						// Attack timer
	//int getDamage();
private:
	Player* player;
	//int damage;
};



#endif /* ATTACK_H_ */
