/*
 * Map.h
 *
 */

#ifndef MAP_H_
#define MAP_H_

#include "Room.h"
#include <vector>
#include <cstdlib>
#include <ctime>

class Map {
public:
	Map(const std::string& tileset, int windowTileSize, int width, int height);
	~Map();
	Room* nextRoom();
	Room* getRoom(int roomNum);


private:
	std::vector<Room*> map;// = nullptr; //TODO DELETE IN DISTRUCTOR
	int currentRoom;
	int numRooms;
	int numRoomsSeen;
};

#endif /* MAP_H_ */
