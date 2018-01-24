/*
 * RoomElement.cpp
 *
 */

#include "RoomElement.h"
#include "Player.h"
#include "Enemy.h"
#include "Weapon.h"
#include "Item.h"

#include <iostream>

// Default constructor
RoomElement::RoomElement() {
	_isLoaded = false;
	setX(0);
	setY(0);
}

// Room element destructor
RoomElement::~RoomElement(){
	std::cout << "RoomElement destroyed" << std::endl;
}

void RoomElement::Load(std::string filename, int tileSize){
	// Try to load texture from file
	if(_texture.loadFromFile(filename) == false)
	{	// Send error message to console if we cannot load
		_filename = "";
		_isLoaded = false;
		std::cout << "Failed to load " << filename << std::endl;
	}
	else
	{	// otherwise load texture to sprite
		_filename = filename;

			_textureSize = _texture.getSize();
			_scale = 0.02*tileSize;
			//_elementSize = _textureSize;
			_elementSize.x = _textureSize.x;
			_elementSize.y = _textureSize.y ;
			_sprite.setTexture(_texture);
			_isLoaded = true;
			if (_filename == "textures/weapons/default_weapon.png")
			_sprite.scale(_scale,_scale);
/*
			if (rotation == 0)
				std::cout << rotation << std::endl;
			else if (rotation == 1)
				std::cout<< 1 <<endl;
			else if (rotation == 2)
				std::cout << 2 << std::endl;
			else
				std::cout << 3 << std::endl;*/
			visibility = 255;
	}
}

//Load and use part of texture
void RoomElement::Load(std::string filename, unsigned int columns,unsigned int rows, unsigned int columnNum, unsigned int rowNum, int tileSize){
	Load(filename, tileSize);
	_elementSize.x = (_textureSize.x/columns);
	_elementSize.y = (_textureSize.y/rows);
	_sprite.setTextureRect(sf::IntRect(columnNum*_elementSize.x, rowNum*_elementSize.y, _elementSize.x, _elementSize.y));
}

void RoomElement::Draw(sf::RenderWindow & window){
	if(_isLoaded)
	{
		window.draw(_sprite);
	}
	else
		std::cout << "Must load image first to " << std::endl;
}

void RoomElement::SetPosition(float x, float y){
	if(_isLoaded)
	{
		setX(x);
		setY(y);
		_sprite.setPosition(xPos,yPos);
	}
	else
		std::cout << "Must load image first" << std::endl;
}

void RoomElement::RotateWeapon(float x, float y) {
	if (_isLoaded) {
		setX(x);
		setY(y);
		_sprite.setPosition(xPos, yPos);

	}
	else
		std::cout<< "Must load image first" << std::endl;
}

sf::Vector2<float> RoomElement::getPosition(){
	sf::Vector2<float> temp(xPos, yPos);
	return temp;
}


//Testing collision with room and second player (Works. Test method for all elements)
void RoomElement::move(double deltaX, double deltaY, Room &room, vector<RoomElement *>& o){
	sf::Vector2<float> pos = getPosition();
	sf::Vector2u roomSize = room.getRoomSize();

	// Calculate new position
	pos.x += deltaX;
	pos.y += deltaY;

	// Calculate new position
	pos.x += deltaX;
	pos.y += deltaY;

	// To account for the size of the sprite
	roomSize.x -=_elementSize.x;
	roomSize.y -=_elementSize.y;

	// Don't move if new position is invalid within the room
	if (pos.y < 0 || pos.x < 0 || roomSize.x < pos.x || roomSize.y < pos.y)
		return;

	// Create a rectangular object at new positions of elements to check for collisions
	sf::IntRect mover(pos.x, pos.y, (_elementSize.x*_scale), (_elementSize.y*_scale));
	vector<sf::IntRect> rects;
	for (unsigned int i = 0; i < o.size(); ++i){
		float scale = o.at(i)->getScale();
		rects.push_back(sf::IntRect( o.at(i)->getPosition().x, o.at(i)->getPosition().y, (o.at(i)->getElementWidth())*scale, (o.at(i)->getElementHeight())*scale));
	}


	// Go through every RoomElement, check what kind of RoomElement it is, and if collision occurs, do as appropriate
	bool walkOver;
	for (unsigned int i = 0; i < o.size(); ++i)
	{
		// Don't check for collision with self
		if (o.at(i) != this && collision(mover, rects[i]))
		{
			//Rotate enemy if collides
			if(dynamic_cast<Enemy *> (this))
			{
					dynamic_cast<Enemy *> (this)->walkClock.restart();
					int newRotation = rand() %4;
					this->setRotation(newRotation);

			}
			//Do action when colliding with object, and check if you can walk over it
			walkOver = o.at(i)->doAction(this);
			if(!walkOver)
				return;
			//Players can pick up objects if they can walk over it
			if(dynamic_cast<Player *>(this)){
				o.erase(o.begin() + i);
				break;
			}
		}
	}

	if(room.walkable(pos, _elementSize)) //check if tile is valid
		SetPosition(pos.x, pos.y);

	else
	{
		//Rotate if enemy hits wall
		if(dynamic_cast<Enemy *> (this))
		{
				int newRotation = rand() %4;
				dynamic_cast<Enemy *> (this)->walkClock.restart();
				this->setRotation(newRotation);

		}
	}
}


// Test for collision between two elements
bool RoomElement::collision(sf::IntRect current, sf::IntRect other){
	bool collision = false;
	//Check for collisions
	if(current.intersects(other)){
		collision = true;
	}
	return collision;
}


void RoomElement::setX(float x){
	xPos = x;
}

void RoomElement::setY(float y){
	yPos = y;
}

/*void RoomElement::setSprite(Sprite newSprite){
	// should we clone this since its an object?
	sprite = newSprite;
}*/

void RoomElement::setSpeed(float newSpeed){
	speed = newSpeed;
}

//0 = down, 1 = left, 2 = right, 3 = up
void RoomElement::setRotation(int newRotation){
	rotation = newRotation;
}

void RoomElement::setCurrentHP(int newCurrentHP){
	if(newCurrentHP > maximumHP)
		currentHP = maximumHP;
	else if(newCurrentHP <=0){
		currentHP = 0;				// Changed to game over (or removal of avatar for 2 player) later
	}
	else{
		currentHP = newCurrentHP;
	}
}

void RoomElement::setMaximumHP(int newMaximumHP){
	maximumHP =  newMaximumHP;
}

unsigned int RoomElement::getTextureWidth(){
	return _textureSize.x;
}

unsigned int RoomElement::getTextureHeight(){
	return _textureSize.y;
}

unsigned int RoomElement::getElementWidth(){
	return _elementSize.x;
}

unsigned int RoomElement::getElementHeight(){
	return _elementSize.y;
}

sf::Vector2u RoomElement::getElementSize(){
	return _elementSize;
}

sf::Sprite* RoomElement::getSprite(){
	return &_sprite;
}

sf::Texture RoomElement::getTexture(){
	return _texture;
}

int RoomElement::getRotation(){
	return rotation;
}

void RoomElement::setName(string n){
	name = n;
}

string RoomElement::getName(){
	return name;
}

float RoomElement::getSpeed(){
	return speed;
}

//Animation to walk up. Supply values for vector.
void RoomElement::walk(int x,int y, int width, int height){
	_sprite.setTextureRect(sf::IntRect(x*width, y*height, width, height));
}

float RoomElement::getScale(){
	return _scale;
}

float RoomElement::getxPos(){
	return xPos;
}

float RoomElement::getyPos(){
	return yPos;
}

int RoomElement::getCurrentHP(){
	return currentHP;
}

int RoomElement::getMaximumHP(){
	return maximumHP;
}

bool RoomElement::doAction(RoomElement *element){
	return false;
}

void RoomElement::setDamage(int newDamage){
	damage = newDamage;
}

int RoomElement::getDamage(){
	return damage;
}

