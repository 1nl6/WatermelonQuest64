/* Tutorials used
 * Setting up the basics: https://www.youtube.com/channel/UC8C7ncaMYnXyu-pRU0S9FLg
 * general questions: http://www.gamefromscratch.com/page/Game-From-Scratch-CPP-Edition.aspx
 *
 * Game art available:
 * http://opengameart.org/
 *////////////

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "Player.h"
#include "Room.h"
#include "Enemy.h"
#include "Item.h"
#include "Attack.h"
#include "Map.h"
#include "Menu.h"
#include "HUD.h"
#include <Music.hpp>


void setPosition(int tileSize, Room &room, RoomElement &element, vector<RoomElement *> *elementsInRoom);
vector<RoomElement *>* createRoomElements(int tileSize, Room &room);

using namespace std;
vector<int> numEnimies(5);


int Title() {
	sf::RenderWindow window(sf::VideoMode(600, 700), "WaterMelon Quest 64");
	TitleScreen TitleScreen(window.getSize().x, window.getSize().y);
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::KeyReleased:
				switch (event.key.code)  {

				case sf::Keyboard::Up:
					cout << TitleScreen.GetPressedItem() << endl;
					TitleScreen.MoveUp();
					break;
				case sf::Keyboard::Down:
					cout << TitleScreen.GetPressedItem() << endl;
					TitleScreen.MoveDown();
					break;
				case sf::Keyboard::Return:
					switch (TitleScreen.GetPressedItem()) {
					case 2:
						window.close();
						cout << TitleScreen.GetPressedItem() << endl;
						return TitleScreen.GetPressedItem();
						break;
					case 3:
						return TitleScreen.GetPressedItem();
						break;
					case 4:
						exit(0);
					}
					TitleScreen.Enter();
					break;
				}
				break;

				case sf::Event::Closed:
					window.close();
					break;
			}
		}
		window.clear();
		TitleScreen.draw(window);
		window.display();
	}
}

void GameOver() {
	sf::RenderWindow window (sf::VideoMode(600, 700), "WaterMelon Quest 64", sf::Style::Close);
	GameOverScreen GameOverScreen(window.getSize().x, window.getSize().y);
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				exit(0);
				window.close();
				break;
			}
		}
		window.clear();
		GameOverScreen.draw(window);
		window.display();
	}
}


void SettingsMenu() {
	sf::RenderWindow window(sf::VideoMode(600, 700), "WaterMelon Quest 64");

	MainSettingScreen MainSettingScreen(window.getSize().x, window.getSize().y);
	window.setKeyRepeatEnabled(false);
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type)  {
			case sf::Event::KeyReleased:
				switch (event.key.code) {
				case sf::Keyboard::Up:
					MainSettingScreen.MoveUp();
					break;
				case sf::Keyboard::Down:
					MainSettingScreen.MoveDown();
					break;
				case sf::Keyboard::Left:
					MainSettingScreen.MoveLeft(window);
					break;
				case sf::Keyboard::Right:
					MainSettingScreen.MoveRight(window);
					break;
				case sf::Keyboard::Return:
					switch (MainSettingScreen.GetPressedItem()) {
					case 4:
						if (MainSettingScreen.sameAvatar() == true) {}
						else {
							window.close();
							Title();
							break;
						}
						break;
					}
					MainSettingScreen.Enter();
					break;
				}
				break;
				case sf::Event::Closed:
					window.close();
					// cout << "Difficulty:"<< difficulty << " Player Amount:" << playerAmount << " Avatar1:" << avatar1 << " Avatar2:" << avatar2 << endl;
					break;
			}
		}
		window.clear();
		MainSettingScreen.draw(window);
	}
}

void YouWin() {
	sf::RenderWindow window (sf::VideoMode(600, 700), "WaterMelon Quest 64", sf::Style::Close);
	YouWinScreen YouWinScreen(window.getSize().x, window.getSize().y);
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				exit(0);
				window.close();
				break;
			}
		}

		window.clear();
		YouWinScreen.draw(window);
		window.display();
	}

}

int main(){
	sf::Music music;
	if (!music.openFromFile("Music/scary.wav"))
		return -1; // error
	music.play();

	int titleChoice = Title();
	cout << "Title choice: " << titleChoice<<endl;
	if (titleChoice == 3)
		SettingsMenu();


	/*
	sf::RenderWindow window(sf::VideoMode(1800, 1400), "test 5");

		MainSettingScreen MainSettingScreen(window.getSize().x, window.getSize().y);
		window.setKeyRepeatEnabled(false);
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::KeyReleased:
					switch (event.key.code)
					{
					case sf::Keyboard::Up:
						MainSettingScreen.MoveUp();
						break;
					case sf::Keyboard::Down:
						MainSettingScreen.MoveDown();
						break;
					case sf::Keyboard::Left:
						MainSettingScreen.MoveLeft(window);
						break;
					case sf::Keyboard::Right:
						MainSettingScreen.MoveRight(window);
						break;
					case sf::Keyboard::Return:
						MainSettingScreen.Enter();
						break;
					}
					break;
				case sf::Event::Closed:
					window.close();
					//cout << "Difficulty:"<< difficulty << " Player Amount:" << playerAmount << " Avatar1:" << avatar1 << " Avatar2:" << avatar2 << endl;
					break;
				}
			}
			window.clear();
			MainSettingScreen.draw(window);
		}
	 */
	sf::Vector2<int> lastEntryDoor;

	//Dimensions of everything
	int playerAlive = 1;						// Set to 2 if two-player mode and player 1 dies

	int screenWidth = 600;
	sf::Vector2u screenDimensions(screenWidth, screenWidth + screenWidth/6);	// Dimension of the screen
	int tileSize = screenDimensions.x /10;		// Dimension of each tile for room
	vector<RoomElement *> *allElementsInRoom = new vector<RoomElement *>[5];	// All elements in the room;

	srand(time(NULL));							// Used to generate random position in for roomElements
	sf::Clock lastAttack;						// Time of last attack for player 1
	sf::Clock lastAttack2; 					// Time of last attack for player 2

	// Creating Rendering window
	sf::RenderWindow window(sf::VideoMode(screenDimensions.x,screenDimensions.y),"WaterMelon Quest 64", sf::Style::Close);

	//Create map of game
	Map *map = new Map("textures/room/caveTileset21.png", tileSize, 10, 10);
	Room *room;
	sf::Vector2<int> entryDoor;
	vector<RoomElement*> elementsInRoom;

	int directionValue;

	room = map->getRoom(0);
	entryDoor = room->getRandDoor();


	//Determine number, type, and position of all elements in each room of map
	for(int r = 0; r < 5; r++){
		allElementsInRoom[r] = *createRoomElements(tileSize, *map->getRoom(r));
	}


	//Determine which roomElements vector is currently used
	elementsInRoom = allElementsInRoom[room->getRoomNum()];

	//Creating the player
	Player *player = new Player(avatar1,difficulty,1, tileSize);
	elementsInRoom.push_back(player);
	player->SetPosition(entryDoor.x, entryDoor.y + tileSize*1.2);

	Player *player2 = nullptr;
	HealthBar *bar2 = nullptr;
	if(playerAmount == 2){
		player2 = new Player(avatar2,difficulty,2, tileSize);
		elementsInRoom.push_back(player2);
		player2->SetPosition(entryDoor.x, entryDoor.y + tileSize*2);

		bar2 = new HealthBar(player2->getMaximumHP(), window.getSize().x, window.getSize().y, 2);
	}

	HUD *hud = new HUD(window.getSize().x, window.getSize().y, playerAmount, player, player2);
	HealthBar *bar = new HealthBar(player->getMaximumHP(),window.getSize().x,window.getSize().y, 1);

	//Setting the initial walking texture of avatar
	int x = 1;

	// Open window//
	while(window.isOpen()){
		sf::Event evnt; // creating event object
		while(window.pollEvent(evnt)){ // Check for events
			switch(evnt.type){
			case sf::Event::Closed: // Respond to closing of window
				window.close();
				break;
			default: // here to get rid of warnings
				break;
			}
		}

		bool p1door = room->byDoor(player->getPosition());
		bool p2door = false;
		if(playerAmount == 2 || playerAlive == 2){
			p2door = room->byDoor(player2->getPosition());
		}


		// Check if we should change rooms
		// are we by a door that we did not come out of?
		if(numEnimies[room->getRoomNum()] == 0 && (p1door || p2door) ){
			//
			//Remove player(s) from roomElements vector of previous room
			for(unsigned int e = 0; e < elementsInRoom.size(); e++){
				if (dynamic_cast<Player *>(elementsInRoom[e])){
					elementsInRoom.erase(elementsInRoom.begin() + e);
				}
			}
			allElementsInRoom[room->getRoomNum()] = elementsInRoom;
			room = map->nextRoom();

			if(room->getRoomNum() == 4){
				if (!music.openFromFile("Music/MyTimeIsNow.wav"))
					return -1; // error
				cout << "AND HIS NAME IS JOHN CENA" << endl;
				music.play();
			}

			entryDoor = room->getRandDoor();
			//Change roomElements vector and add player(s) to roomElements vector of current room
			elementsInRoom = allElementsInRoom[room->getRoomNum()];
			if(playerAlive != 2){
				elementsInRoom.push_back(player);
				player->SetPosition(entryDoor.x, entryDoor.y + tileSize*1.2);
			}
			if(playerAmount == 2 || playerAlive == 2){
				elementsInRoom.push_back(player2);
				player2->SetPosition(entryDoor.x, entryDoor.y + tileSize*2.2);
			}
			/*
			elementsInRoom.push_back(player);
			elementsInRoom.push_back(player2);
			entryDoor = room->getRandDoor();
			player->SetPosition(entryDoor.x, entryDoor.y + tileSize*1.2);
			player2->SetPosition(entryDoor.x, entryDoor.y + tileSize*2.2);
			 */
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)){
			room = map->getRoom(4);
			entryDoor = room->getRandDoor();
			elementsInRoom = allElementsInRoom[4];
			if(playerAlive != 2){
				elementsInRoom.push_back(player);
				player->SetPosition(entryDoor.x, entryDoor.y + tileSize*1.2);
			}
			if(playerAmount == 2 || playerAlive == 2){
				elementsInRoom.push_back(player2);
				player2->SetPosition(entryDoor.x, entryDoor.y + tileSize*2.2);
			}
			if (!music.openFromFile("Music/MyTimeIsNow.wav"))
				return -1; // error
			cout << "AND HIS NAME IS JOHN CENA" << endl;
			music.play();

		}


		// Player 1 - moving
		if(playerAlive != 2){		//Enable if player1 is alive
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
				player->setRotation(1);
				player->walk(x,player->getRotation(),player->getElementWidth(),player->getElementHeight());
				player->move(-(player->getSpeed()),0.0, *room, elementsInRoom);
				if(x*player->getTextureWidth() >= (player->getTextureWidth() - player->getElementWidth()))
					x = 0;
				else
					x++;
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
				player->setRotation(2);
				player->walk(x,player->getRotation(),player->getElementWidth(),player->getElementHeight());
				player->move((player->getSpeed()),0.0, *room, elementsInRoom);
				if(x*player->getTextureWidth() >= (player->getTextureWidth() - player->getElementWidth()))
					x = 0;
				else
					x++;
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
				player->setRotation(3);
				player->walk(x,player->getRotation(),player->getElementWidth(),player->getElementHeight());
				player->move(0.0,-(player->getSpeed()), *room, elementsInRoom);
				if(x*player->getTextureWidth() >= (player->getTextureWidth()-player->getElementWidth()))
					x = 0;
				else
					x++;
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
				player->setRotation(0);
				player->walk(x,player->getRotation(),player->getElementWidth(),player->getElementHeight());
				player->move(0.0,(player->getSpeed()), *room, elementsInRoom);
				if(x*player->getTextureWidth() >= (player->getTextureWidth()-player->getElementWidth()))
					x = 0;
				else
					x++;
			}
			//Player 1 Attack
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
				//Cannot attack more than once every second
				if(lastAttack.getElapsedTime().asSeconds() > 1){
					lastAttack.restart();
					//Get the player's damage
					switch(player->getRotation())
					{
					case 0: //if player is facing down, create attack below
						elementsInRoom.push_back(new Attack(player, tileSize, player->getxPos(), player->getyPos()+(player->getElementWidth()*player->getScale()), elementsInRoom));
						break;
					case 1: //if player is facing left, create attack left
						elementsInRoom.push_back(new Attack(player, tileSize, player->getxPos()-(player->getElementWidth()*player->getScale())-2, player->getyPos(), elementsInRoom));
						break;
					case 2: //if player is facing right, create attack right
						elementsInRoom.push_back(new Attack(player, tileSize, player->getxPos()+(player->getElementWidth()*player->getScale()), player->getyPos(), elementsInRoom));
						break;
					case 3: //if player is facing up, create attack above
						elementsInRoom.push_back(new Attack(player, tileSize, player->getxPos(), player->getyPos()-(player->getElementWidth()*player->getScale())-2, elementsInRoom));
						break;
					default:
						break;
					}
				}
			}
			//Player 1 using watermelons using left shift key
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
				player->useWatermelon();
			}
		}


		// Check for keyboard inputs and move player2
		if(playerAmount == 2 || playerAlive == 2){ //Enabled if two-player mode or only player 2 alive
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
				player2->setRotation(1);
				player2->walk(x,player2->getRotation(),player2->getElementWidth(),player2->getElementHeight());
				player2->move(-(player2->getSpeed()),0.0, *room, elementsInRoom);
				if(x*player2->getTextureWidth() >= (player2->getTextureWidth() - player2->getElementWidth()))
					x = 0;
				else
					x++;
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
				player2->setRotation(2);
				player2->walk(x,player2->getRotation(),player2->getElementWidth(),player2->getElementHeight());
				player2->move((player2->getSpeed()),0.0, *room, elementsInRoom);
				if(x*player2->getTextureWidth() >= (player2->getTextureWidth() - player2->getElementWidth()))
					x = 0;
				else
					x++;
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
				player2->setRotation(3);
				player2->walk(x,player2->getRotation(),player2->getElementWidth(),player2->getElementHeight());
				player2->move(0.0,-(player2->getSpeed()), *room, elementsInRoom);
				if(x*player2->getTextureWidth() >= (player2->getTextureWidth()-player2->getElementWidth()))
					x = 0;
				else
					x++;
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
				player2->setRotation(0);
				player2->walk(x,player2->getRotation(),player2->getElementWidth(),player2->getElementHeight());
				player2->move(0.0,(player2->getSpeed()), *room, elementsInRoom);
				if(x*player2->getTextureWidth() >= (player2->getTextureWidth()-player2->getElementWidth()))
					x = 0;
				else
					x++;
			}


			//Player 2 Attack
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
				//Cannot attack more than once every second
				if(lastAttack2.getElapsedTime().asSeconds() > 1){
					lastAttack2.restart();

					switch(player2->getRotation())
					{
					case 0: //if player is facing down, create attack below
						elementsInRoom.push_back(new Attack(player2, tileSize, player2->getxPos(), player2->getyPos()+(player2->getElementWidth()*player2->getScale()), elementsInRoom));
						break;
					case 1: //if player is facing left, create attack left
						elementsInRoom.push_back(new Attack(player2, tileSize, player2->getxPos()-(player2->getElementWidth()*player2->getScale())-2, player2->getyPos(), elementsInRoom));
						break;
					case 2: //if player is facing right, create attack right
						elementsInRoom.push_back(new Attack(player2, tileSize, player2->getxPos()+(player2->getElementWidth()*player2->getScale()), player2->getyPos(), elementsInRoom));
						break;
					case 3: //if player is facing up, create attack above
						elementsInRoom.push_back(new Attack(player2, tileSize, player2->getxPos(), player2->getyPos()-(player2->getElementWidth()*player2->getScale())-2, elementsInRoom));
						break;
					default:
						break;

					}
				}
			}

			//Player 2 using watermelons using left shift key
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSlash)){
				player2->useWatermelon();
			}

			for (unsigned int i = 0; i < elementsInRoom.size(); ++i)
			{

				if(dynamic_cast<Enemy *>(elementsInRoom.at(i))){

					//dynamic_cast<Enemy *>(elementsInRoom.at(i))->getDirectionDuration()

					if(dynamic_cast<Enemy *>(elementsInRoom.at(i))->walkClock.getElapsedTime().asSeconds() > 3)
					{
						dynamic_cast<Enemy *>(elementsInRoom.at(i))->walkClock.restart();
						while (directionValue==(elementsInRoom.at(i)->getRotation()))
						{
							srand (time(NULL));
							directionValue = rand() % 4;

						}
					}
					else
					{
						directionValue = elementsInRoom.at(i)->getRotation();
					}

					if (directionValue == 0)
					{
						elementsInRoom.at(i)->setRotation(0);
						elementsInRoom.at(i)->walk(dynamic_cast<Enemy *>(elementsInRoom.at(i))->getSpriteCount(),(elementsInRoom.at(i))->getRotation(),elementsInRoom.at(i)->getElementWidth(),elementsInRoom.at(i)->getElementHeight());
						elementsInRoom.at(i)->move(0.0,(elementsInRoom.at(i)->getSpeed()), *room, elementsInRoom);
						if((dynamic_cast<Enemy *>(elementsInRoom.at(i))->getSpriteCount()*elementsInRoom.at(i)->getTextureWidth()) >= (elementsInRoom.at(i)->getTextureWidth()-elementsInRoom.at(i)->getElementWidth()))
							dynamic_cast<Enemy *>(elementsInRoom.at(i))->setSpriteCount(0);
						else
							dynamic_cast<Enemy *>(elementsInRoom.at(i))->setSpriteCount(dynamic_cast<Enemy *>(elementsInRoom.at(i))->getSpriteCount()+1);

					}
					else if (directionValue == 1)
					{
						elementsInRoom.at(i)->setRotation(1);
						elementsInRoom.at(i)->walk(dynamic_cast<Enemy *>(elementsInRoom.at(i))->getSpriteCount(),elementsInRoom.at(i)->getRotation(),elementsInRoom.at(i)->getElementWidth(),elementsInRoom.at(i)->getElementHeight());
						elementsInRoom.at(i)->move(-(elementsInRoom.at(i)->getSpeed()),0.0, *room, elementsInRoom);
						if((dynamic_cast<Enemy *>(elementsInRoom.at(i))->getSpriteCount()*elementsInRoom.at(i)->getTextureWidth()) >= (elementsInRoom.at(i)->getTextureWidth()-elementsInRoom.at(i)->getElementWidth()))
							dynamic_cast<Enemy *>(elementsInRoom.at(i))->setSpriteCount(0);
						else
							dynamic_cast<Enemy *>(elementsInRoom.at(i))->setSpriteCount(dynamic_cast<Enemy *>(elementsInRoom.at(i))->getSpriteCount()+1);
					}
					else if (directionValue == 2)
					{
						elementsInRoom.at(i)->setRotation(2);
						elementsInRoom.at(i)->walk(dynamic_cast<Enemy *>(elementsInRoom.at(i))->getSpriteCount(),elementsInRoom.at(i)->getRotation(),elementsInRoom.at(i)->getElementWidth(),elementsInRoom.at(i)->getElementHeight());
						elementsInRoom.at(i)->move((elementsInRoom.at(i)->getSpeed()),0.0, *room, elementsInRoom);
						if((dynamic_cast<Enemy *>(elementsInRoom.at(i))->getSpriteCount()*elementsInRoom.at(i)->getTextureWidth()) >= (elementsInRoom.at(i)->getTextureWidth()-elementsInRoom.at(i)->getElementWidth()))
							dynamic_cast<Enemy *>(elementsInRoom.at(i))->setSpriteCount(0);
						else
							dynamic_cast<Enemy *>(elementsInRoom.at(i))->setSpriteCount(dynamic_cast<Enemy *>(elementsInRoom.at(i))->getSpriteCount()+1);
					}
					else if (directionValue == 3)
					{
						elementsInRoom.at(i)->setRotation(3);
						elementsInRoom.at(i)->walk(dynamic_cast<Enemy *>(elementsInRoom.at(i))->getSpriteCount(),elementsInRoom.at(i)->getRotation(),elementsInRoom.at(i)->getElementWidth(),elementsInRoom.at(i)->getElementHeight());
						elementsInRoom.at(i)->move(0.0,-(elementsInRoom.at(i)->getSpeed()), *room, elementsInRoom);
						if((dynamic_cast<Enemy *>(elementsInRoom.at(i))->getSpriteCount()*elementsInRoom.at(i)->getTextureWidth()) >= (elementsInRoom.at(i)->getTextureWidth()-elementsInRoom.at(i)->getElementWidth()))
							dynamic_cast<Enemy *>(elementsInRoom.at(i))->setSpriteCount(0);
						else
							dynamic_cast<Enemy *>(elementsInRoom.at(i))->setSpriteCount(dynamic_cast<Enemy *>(elementsInRoom.at(i))->getSpriteCount()+1);
					}

				}
			}
		}

		// Display shit
		window.clear();
		window.draw(*room);
		for (unsigned int i = 0; i < elementsInRoom.size(); ++i)
		{
			if(dynamic_cast<Attack *>(elementsInRoom.at(i))) //if a given element is an Attack, decrement the Attack's timer, and remove it if it reaches 0
			{
				if(dynamic_cast<Attack *>(elementsInRoom.at(i))->attackClock.getElapsedTime().asSeconds() > 0.3){
					elementsInRoom.erase(elementsInRoom.begin() + i);
					continue;
				}
			}

			if(dynamic_cast<Enemy *>(elementsInRoom.at(i))){
				if(elementsInRoom.at(i)->getCurrentHP() <=0){
					//Check if final boss defeated
					if(dynamic_cast<Enemy *>(elementsInRoom.at(i))->getType() == 3){
						cout<< "You win!" << endl;
						YouWin();
					}

					// spawn items
					RoomElement *spawned = nullptr;
					int itemIndex = dynamic_cast<Enemy *>(elementsInRoom.at(i))->dropItem();
					if (itemIndex == DROP_NUM-1)
						cout << "You got nothing muwahahaha" << endl;
					else if ((itemIndex == DROP_NUM-3)){ // should be a sword
						spawned = new Weapon(25, "sword", tileSize);
						spawned->SetPosition(elementsInRoom.at(i)->getPosition().x, elementsInRoom.at(i)->getPosition().y);
						cout << "Weapon spawned" << endl;
					}

					else if (itemIndex == DROP_NUM-2){ // should be amace
						spawned = new Weapon(28, "mace", tileSize);
						spawned->SetPosition(elementsInRoom.at(i)->getPosition().x, elementsInRoom.at(i)->getPosition().y);
						cout << "Weapon spawned" << endl;
					}
					else {
						spawned = new Item(itemIndex, tileSize);
						spawned->SetPosition(elementsInRoom.at(i)->getPosition().x, elementsInRoom.at(i)->getPosition().y);
						cout << "Item spawned" << endl;
					}

					elementsInRoom.erase(elementsInRoom.begin() + i);

					if (spawned != nullptr)
						elementsInRoom.push_back(spawned);

					if(numEnimies[room->getRoomNum()] > 0){
						numEnimies[room->getRoomNum()] = numEnimies[room->getRoomNum()] - 1;
						cout << "Removed enemy, current number: " << numEnimies[room->getRoomNum()] << endl;
					}
					continue;
				}
			}
			if(dynamic_cast<Player *>(elementsInRoom.at(i))){
				//Remove invincibility when needed
				if(dynamic_cast<Player *> (elementsInRoom.at(i))->getInvincibility() && dynamic_cast<Player *> (elementsInRoom.at(i))->invincibilityTimer.getElapsedTime().asMilliseconds() > 500){
					dynamic_cast<Player *> (elementsInRoom.at(i))->setInvincibility(false);
				}
				bar->changeHealth(player->getCurrentHP(), player->getMaximumHP());
				if (player2 != nullptr)
					bar2->changeHealth(player2->getCurrentHP(), player2->getMaximumHP());

				//Check if a player died
				if(elementsInRoom.at(i)->getCurrentHP() <=0){
					if (elementsInRoom.at(i)->getName() == "Player 1"){
						//Check if two player
						if(playerAmount == 2){
							playerAlive = 2;
							playerAmount = 1;
						} else
							GameOver();
					} else if(elementsInRoom.at(i)->getName() == "Player 2"){
						if(playerAmount == 2)
							playerAmount = 1;
						else
							GameOver();
					}

					elementsInRoom.erase(elementsInRoom.begin() + i);
					continue;
				}

			}
			elementsInRoom.at(i)->Draw(window);
		}
		// change all the stats things we need to change here
		// Weapon modifier destroying room elements for some reason
		if ((player->getModified()) == true){
			hud->setScore(player->getScore(), 1);
			hud->setWatermelonCount(player->getWatermelonCount(),1);
			hud->setWeaponModifier((player->getWeapon()).getDamage(), 1, player);
			hud->setAttackBonus(player->getAttackBonus(),1);
			bar->changeHealth(player->getCurrentHP(), player->getMaximumHP());
			cout << "Modified a player 1 stat" << endl;
		}

		if (player2 != nullptr){
			if ((player2->getModified()) == true){
				hud->setScore(player2->getScore(), 2);
				hud->setWeaponModifier(player2->getWeapon().getDamage(), 2, player2);
				hud->setWatermelonCount(player2->getWatermelonCount(),2);
				hud->setAttackBonus(player2->getAttackBonus(),2);
				bar2->changeHealth(player2->getCurrentHP(), player2->getMaximumHP());
				cout << "Modified a player 2 stat" << endl;
			}
		}

		hud->Draw(window);
		bar->Draw(window);
		if (player2 != nullptr){
			bar2->Draw(window);
			player2->setUnmodified();
		}
		player->setUnmodified();

		window.display();
	}

	return 0;
}

//Create the vector that will hold the RoomElements in the room
vector<RoomElement *>* createRoomElements(int tileSize, Room &room){
	vector<RoomElement *> *elementsInRoom = new vector<RoomElement *>;
	//Don't generate enemies in boss room
	if(room.getRoomNum() == 0){
		// Determine number of enemies (1-4)
		int enemyNum = 2; //(rand() % 4) + 1;
		// Store the number of enemies in the room
		int roomNum = room.getRoomNum();
		numEnimies[roomNum] = enemyNum;
		cout << "For Room: " << roomNum << " we have " << numEnimies[roomNum] << "Enemy" << endl;
		int enemyType;
		for(int e = 0; e < enemyNum; e++){
			// Randomly determine type of enemy (0-2)
			enemyType = rand() % 3;
			Enemy *enemy = new Enemy(enemyType, tileSize);
			enemy->setRotation(1);
			setPosition(tileSize, room, *enemy, elementsInRoom);

			// set drop tables based on difficulty - haven't tested this yet
			enemy->setDropRates(difficulty);
			elementsInRoom->push_back(enemy);
		}
	} //Generate boss in boss room
	else if (room.getRoomNum()==4){
		Enemy *enemy = new Enemy(3, tileSize);
		setPosition(tileSize, room, *enemy, elementsInRoom);
		elementsInRoom->push_back(enemy);

	}
	//Determine number of items (1-4)
	int itemNum = (rand() % 4)+1;
	int itemType;
	for(int i = 0; i < itemNum; i++){
		// Randomly determine type of items (0-3)
		itemType = rand() %4;
		Item *item = new Item(itemType, tileSize);
		setPosition(tileSize, room, *item, elementsInRoom);
		elementsInRoom->push_back(item);
	}

	return elementsInRoom;
}

//TODO: Check that the position is not already occupied by another element - will need to pass in current vector of roomElements
// Set the element at a random tile
void setPosition(int tileSize, Room &room, RoomElement &element, vector<RoomElement *> *elementsInRoom){
	sf::Vector2u elementSize(element.getElementWidth(), element.getElementHeight());
	Vector2<float> tilePos;
	vector<sf::Vector2<int>>& doors = room.getDoors();

	// ints to check bounds of door
	int xStart, xEnd, yStart, yEnd;

	bool done = false;
	while (!done){
		//Find position of random tile
		tilePos.x = (rand() % 10) * tileSize;
		tilePos.y = (rand() % 10) * tileSize;
		//Check if tile is valid (walkable, not by a door and not occupied by another element)
		if(room.walkable(tilePos, elementSize) && !(room.byDoor(tilePos))){
			bool occupied = false;
			//Check if position is occupied by another element or beneath a door
			for(int element = 0; element < elementsInRoom->size(); element++){
				for(int i = 0; i < doors.size(); i++){
					xStart 	= doors[i].x;
					xEnd	= doors[i].x + tileSize;
					yStart	= doors[i].y + tileSize;
					yEnd	= doors[i].y + (tileSize * 2.0);
					if(xStart <= tilePos.x && tilePos.x < xEnd && yStart <= tilePos.y && tilePos.y < yEnd){
						occupied = true;
						break;
					}
					if(elementsInRoom->at(element)->getxPos() == tilePos.x && elementsInRoom->at(element)->getyPos() == tilePos.y){
						occupied = true;
						break;
					}
				}
			}
			if(!occupied){
				element.SetPosition(tilePos.x, tilePos.y);
				done = true;
			}
		}
	};
}

