/*
 * RoomElement.h
 *
 */

#pragma once

#ifndef ROOMELEMENT_H_
#define ROOMELEMENT_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Room.h"

using namespace std;

class RoomElement{
public:
	RoomElement();
	virtual ~RoomElement();

	virtual void Load(std::string filename, int tileSize);
	//Split texture into parts, based on number of columns and rows. Specify first texture used with x and y.
	virtual void Load(std::string filename, unsigned int columns,unsigned int rows, unsigned int columnNum, unsigned int rowNum,int tileSize);
	virtual void Draw(sf::RenderWindow & window);

	virtual void SetPosition(float x, float y);
	void RotateWeapon(float x, float y);
	sf::Vector2<float> getPosition();
	//Test for collision with all elements in room
	void move(double deltaX, double deltaY, Room &room, vector<RoomElement *>& o);

	//bool collision(sf::Vector2<float> pos, float deltaX, float deltaY, vector<RoomElement> elementsInRoom);
	//Test for twoplayer collision
	bool collision(sf::IntRect current, sf::IntRect other);

	int getCurrentHP();
	int getMaximumHP();

	void setX(float X);
	void setY(float Y);
	void setRotation(int newRotation);
	// void setSprite(Sprite newSprite);
	virtual void setSpeed(float newSpeed);
	void setCurrentHP(int newCurrentHP);
	virtual void setMaximumHP(int newMaximumHP);
	void walk(int x,int y, int width, int height); 	// play RoomElement's walking animation and sound (stored as a series of sprites that change from frame to frame and as a sound file)
	void hurt(); 	// play RoomElement's hurt animation (stored as a series of sprites that change from frame to frame and as a sound file)
	unsigned int getTextureWidth();
	unsigned int getTextureHeight();
	unsigned int getElementWidth();
	unsigned int getElementHeight();
	int getRotation();
	void setName(string n);
	string getName();
	float getSpeed();
	float getScale();
	float getxPos();
	float getyPos();

	sf::Vector2u getElementSize();
	sf::Sprite *getSprite();
	sf::Texture getTexture();

	virtual bool doAction(RoomElement *element); //Determines if element can walk over the class element, and does action
	virtual void setDamage(int newDamage);
	int getDamage();
	//void die();

private:
	std::string name;
	float xPos;		// Current x coordinate (centre of the Room is 0)
	float yPos;		// Current y coordinate (centre of the Room is 0)
	float speed;	// Current speed in units per second
	float radius;	// Current size (RoomElement has a circular hitbox, if an opposing hurtbox comes in that hitbox, RoomElement takes damage)
	int currentHP;	// Current Hit Points
	int maximumHP;	// Maximum Hit Points
	int rotation;	// which direction the RoomElement is facing (used to orient RoomElement's sprite, 1 is North, 2 is North-East, 3 is East, ... 8 is North-West)
	sf::Sprite  _sprite; // What the RoomElement looks like
	sf::Texture _texture; // store the room element texture
	std::string _filename; // store the file name that we will need to draw. Need if we want to animate object
	bool _isLoaded; // check if texture has been loaded
	sf::Vector2u _textureSize; // store the size of the Room element
	sf::Vector2u _elementSize; // store the size of the element, for when the size is not the size of the texture.
	float _scale;
	int damage;
	int visibility;

};

#endif /* ROOMELEMENT_H_ */
