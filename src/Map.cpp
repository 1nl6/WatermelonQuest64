/*
 * Map.cpp
 *
 */

#include "Map.h"

Map::Map(const std::string& tileset, int windowTileSize, int width, int height){

	// hard coded the levels - automate in the future

	// Main
	int main[] =
		{
				14,	14,	12,	14, 14,	14,	15,	27,	27,	27,
				3,	2,	3,	3,	2,	3,	3,	14,	27,	27,
				3,	3,	3,	3,	3,	3,	3,	4,	27,	27,
				3,	3,	3,	3,	3,	3,	3,	4,	27,	27,
				3,	3,	3,	3,	3,	3,	3,	3,	16,	13,
				3,	3,	3,	3,	3,	3,	3,	3,	3,	0,
				3,	3,	3,	6,	19,	17,	3,	3,	3,	3,
				6,	19,	17,	18,	25,	25,	19,	17,	17,	17,
				18,	24,	24,	25,	30,	24,	24,	25,	24,	24,
				24,	24,	30,	24,	24,	24,	24,	24,	24,	24
		};

	// Final level
	int final[] =
		{
				27,	27,	27,	27, 16,	13,	15,	27,	27,	27,
				27,	32,	27,	27, 5,	0,	4,	27,	27,	27,
				27,	27,	27,	27, 5,	3,	4,	27,	32,	27,
				27,	27,	27,	27, 5,	3,	4,	27,	27,	27,
				27,	27,	27,	5, 	3,	3,	1,	4,	27,	27,
				27,	27,	27,	5, 	3,	3,	3,	4,	27,	27,
				27,	27,	27,	5, 	3,	3,	3,	4,	27,	27,
				27,	27,	27,	16, 14,	14,	14,	15,	27,	27,
				27,	27,	32,	27, 27,	27,	27,	27,	27,	27,
				27,	27,	27,	27, 27,	27,	27,	27,	27,	27,
		};

	// Water Room
	int water[] =
		{
				27,	15,	12,	14, 14,	14,	27,	27,	27,	27,
				27,	5,	3,	2,	3,	3,	14,	27,	27, 27,
				13,	5,	3,	3,	3,	3,	3,	4,	27,	27,
				0,	3,	3,	3,	3,	20,	20,	4,	27,	13,
				3,	3,	1,	3,	8,	26,	26,	9,	16,	0,
				3,	3,	3,	3,	8,	26,	26,	9,	3,	3,
				3,	3,	3,	3,	8,	26,	9,	3,	3,	3,
				8,	22,	20,	20,	21,	26,	22,	20,	20,	20,
				21,	26,	26,	26,	26,	26,	26,	26,	26,	26,
				26,	26,	26,	26,	26,	26,	26,	26,	26,	26,
		};

	// Connector
	int connector[] =
		{
				24,	24,	24,	24, 14,	12,	24,	24,	24,	12,
				24,	24,	12,	24, 7,	6,	24,	30,	24,	7,
				3,	3,	6,	24, 7,	6,	24,	24,	24,	7,
				6,	24,	24,	24, 7,	6,	24,	24,	24,	7,
				3,	3,	3,	3, 	3,	3,	3,	3,	3,	3,
				6,	24,	7,	24, 24,	24,	24,	24,	24,	24,
				6,	30,	7,	24, 24,	24,	13,	24,	24,	30,
				6,	24,	7,	24,	24,	24,	6,	24,	24,	24,
				3,	3,	3,	3,	3,	3,	6,	24,	24,	24,
				24,	24,	24,	24, 24,	30,	24,	24,	24,	24,
		};

	int doors[] =
		{
				25,	24,	24,	25,	25,	24,	24,	25,	24,	24,
				24,	24,	24,	24,	24,	24,	24,	24,	24,	24,
				14,	12,	14,	25,	25,	24,	24,	14,	14,	25,
				3,	3,	3,	14,	25,	25,	14,	3,	14,	25,
				3,	3,	3,	3,	14,	14,	3,	3,	14,	13,
				3,	3,	1,	3,	3,	3,	3,	3,	3,	0,
				3,	3,	3,	6,	19,	17,	3,	3,	3,	3,
				6,	19,	17,	18,	25,	25,	19,	17,	17,	17,
				18,	24,	24,	25,	30,	24,	24,	25,	24,	24,
				24,	24,	30,	24,	24,	24,	24,	24,	24,	24
		};

	// Create the rooms
	Room *mainRoom = new Room(tileset, windowTileSize, main, width, height, 0);
	Room *waterRoom = new Room(tileset, windowTileSize, water, width, height, 1);
	Room *doubleRoom = new Room(tileset, windowTileSize, doors, width, height, 2);
	Room *conectRoom = new Room(tileset, windowTileSize, connector, width, height, 3);
	Room *finalRoom = new Room(tileset, windowTileSize, final, width, height, 4);

	// Set the current Room to main room
	currentRoom = 0;

	// Put rooms into map
	map.push_back(mainRoom);
	map.push_back(waterRoom);
	map.push_back(doubleRoom);
	map.push_back(conectRoom);
	map.push_back(finalRoom);

	// get the humber of rooms
	numRooms = map.size();

	numRoomsSeen = 0;
}

Map::~Map(){

}

Room* Map::nextRoom(){
	int oldRoom = currentRoom;
	std::srand(std::time(0)); // use current time as seed for random generator

	// We have to do it like this because if we do it in a while loop
	// there is a chnace that this will take a really long time

	int rand[numRooms - 1];
	int index = 0;
	int max;

	if(numRoomsSeen >= 4){
		max = numRooms;
	}
	else{
		max = numRooms - 1;
	}

	// Fill rand array with rooms we can visit
	for(int i = 0; i < max; i++){
		if(i != oldRoom){
			rand[index] = i ;
			index++;
		}
	}

	// Choose from rooms we can visit
	currentRoom = rand[std::rand() % (numRooms - 1)];

	numRoomsSeen += 1;

	return map[currentRoom];
}

Room* Map::getRoom(int roomNum){
	return map[roomNum];
}
