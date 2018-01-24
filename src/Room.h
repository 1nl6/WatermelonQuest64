/*
 * Room.h
 *
 */

#ifndef ROOM_H_
#define ROOM_H_

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace sf;

class Room : public sf::Drawable, public sf::Transformable {
public:
	//Room(const std::string& tileset, int windowTileSize, const int* tiles, int width, int height);
	Room(const std::string& tileset, int windowTileSize, const int* tiles, int width, int height, int num);
	virtual ~Room();
	bool areEnemiesDead(); // returns true if all the Enemies in the Room are dead, false otherwise. Used to determine if the doors are open or closed (doors only open after every Enemy has been defeated).
	virtual bool loadBackground(const std::string& tileset, const int* tiles, int width, int height); // load background texture
	void loadTexture(std::string filename);
	bool walkable(sf::Vector2<float> position, sf::Vector2u elementSize); // function to see if a room object can be present at this location
	sf::Vector2u getRoomSize();
	sf::Vector2<int> getRandDoor();
	int getNumDoors();
	bool byDoor(sf::Vector2<float> position);
	sf::Vector2<int> getEntryPos();
	void exitRoom();
	int getRoomNum();
	vector<sf::Vector2<int>>& getDoors();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	//vector<Enemy> enemies; 			// vector of Enemies present in the Room.
	vector<sf::Vector2<int>> doors;
	sf::Texture m_tileset; // tileset texture
	sf::VertexArray m_vertices; // vertex array to store the room
	std::string _filename; // store the file name that we will need to draw. Need if we want to animate object
	bool _isLoaded; // check if texture has been loaded
	int* level = nullptr;
	sf::Vector2u _windowSize;
	int tileSize = 48;
	int windowTileSize;
	int numDoors;
	sf::Vector2<int> entryPos;
	int roomNum;

};

#endif /* ROOM_H_ */
