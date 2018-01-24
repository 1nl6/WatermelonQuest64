/*
 * Room.cpp
 *
 */

#include "Room.h"

//Room::Room(const std::string& tileset, int windowTileSize, const int* tiles, int width, int height) {
Room::Room(const std::string& tileset, int windowTileSize, const int* tiles, int width, int height, int num) {
	roomNum = num;
	//std::cout<< roomNum<<std::endl;
	numDoors = 0; // doesnt do anything just removes warnings
	this->windowTileSize = windowTileSize;
	if (!this->loadBackground(tileset, tiles, width, height)){
		std::cout << "Back ground did not load" << std::endl;
	}
	_isLoaded = true;

	_windowSize.x = width * windowTileSize;
	_windowSize.y = height * windowTileSize;
	this->exitRoom();
}

Room::~Room(){
	delete [] level;
	std::cout << "Room has been destroyed" << std::endl;
}

void Room::loadTexture(std::string filename){
	// Try to load texture from file
	if(m_tileset.loadFromFile(filename) == false)
	{	// Send error message to console if we cannot load
		_filename = "";
		_isLoaded = false;
		std::cout << "Failed to load " << filename << std::endl;
	}
	else
	{
		_filename = filename;
		_isLoaded = true;
	}
}

bool Room::loadBackground(const std::string& tileset, const int* tiles, int width, int height){
	// load tile set
	loadTexture(tileset);


	int levelSize = height * width;
	delete [] level;
	level = new int[levelSize];

	for(int i = 0 ; i < levelSize; i++){
		level[i] = tiles[i];
	}



	// resize the vertex array to fit the level size
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(width * height * 4);

	int numCols = m_tileset.getSize().x / tileSize;

	// populate the vertex array, with one quad per tile
	for (int i = 0; i < width; ++i)
		for (int j = 0; j < height; ++j)
		{
			// get the current tile number
			int tileNumber = level[i + j * width];

			// Math to calculate to map the tile number to a tile on the texture
			int tu = tileNumber % numCols;
			int tv = (tileNumber - (tileNumber % numCols)) / numCols;

			// If the tile is a door add it to our vector
			if((tileNumber == 12) || (tileNumber == 13)){
				// store the location of the doors
				doors.push_back(sf::Vector2<int>(i * windowTileSize,j * windowTileSize));
			}

			// get a pointer to the current tile's quad
			sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

			// define its 4 corners
			quad[0].position = sf::Vector2f(i * windowTileSize, j * windowTileSize);
			quad[1].position = sf::Vector2f((i + 1) * windowTileSize, j * windowTileSize);
			quad[2].position = sf::Vector2f((i + 1) * windowTileSize, (j + 1) * windowTileSize);
			quad[3].position = sf::Vector2f(i * windowTileSize, (j + 1) * windowTileSize);

			// define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(tu * tileSize, tv * tileSize);
			quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize, tv * tileSize);
			quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize, (tv + 1) * tileSize);
			quad[3].texCoords = sf::Vector2f(tu * tileSize, (tv + 1) * tileSize);
		}
	numDoors = doors.size();

	return true;
}

void Room::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// apply the tileset texture
	states.texture = &m_tileset;

	// draw the vertex array
	target.draw(m_vertices, states);
}

bool Room::walkable(sf::Vector2<float> position, sf::Vector2u elementSize){

	// What the program sees

	//--------//--------//
	//		  //		//
	//		  //		//
	//		* //		//
	//--------//--------//
	//		  //		//
	//		  //		//
	//		  //		//
	//--------//--------//

	// What we want to see

	//--------//--------//
	//		  //		//
	//		  //		//
	//		*******		//
	//------*******-----//
	//		*******		//
	//		*******		//
	//		  //		//
	//--------//--------//

	/*
	 * let the star be the origin of the sprite (the place where it will be drawn)
	 * The sprite is not a single point but of size "elementSize" by "elementSize"
	 * Therefore we have to check that each corner of the image can be placed on
	 * the tile that it is at.
	 */

	// Calculating the tile position (in room array) of each corner of the sprite
	sf::Vector2<int> topLeft(position.x / windowTileSize, position.y / windowTileSize);
	sf::Vector2<int> topRight((position.x + elementSize.x)/ windowTileSize, position.y / windowTileSize);
	sf::Vector2<int> bottomRight((position.x + elementSize.x) / windowTileSize, (position.y + elementSize.y) / windowTileSize);
	sf::Vector2<int> bottomLeft(position.x /windowTileSize, (position.y + elementSize.x) / windowTileSize);

	// Finding the texture type at each corner
	int textureTopLeft = level[topLeft.x + topLeft.y * 10];
	int textureTopRight = level[topRight.x + topRight.y * 10];
	int textureBottomRight = level[bottomRight.x + bottomRight.y * 10];
	int textureBottomLeft = level[bottomLeft.x + bottomLeft.y * 10];

	// Now to check that every tile is valid
	if((textureTopLeft < 11) && (textureTopRight < 11) && (textureBottomRight < 11) && (textureBottomLeft < 11)){
		// returns true if we can walk there
		return true;
	}

	return false;
}


sf::Vector2u Room::getRoomSize(){
	return _windowSize;
}

sf::Vector2<int> Room::getRandDoor(){
	// TODO Test to see if any aliasing occurs
	std::srand(std::time(0)); // use current time as seed for random generator
	int doorNum = std::rand() % numDoors;
	// Choose a random door and make the position that you enter that room.
	entryPos.x = doors[doorNum].x;
	entryPos.y = doors[doorNum].y;
	return entryPos;
}

int Room::getNumDoors(){
	return numDoors;
}

bool Room::byDoor(sf::Vector2<float> position){
	// cast the current position to ints
	// The position is a float value of where the sprite is positioned on
	// the screen with the ogrigin being the top left corner of the sprite
	// we do not care about the parts of the decimal since you can have a
	// non integer pixel number
	// TODO change the position input into an int to avoid casting
	int xpos(static_cast<int>(position.x));
	int ypos(static_cast<int>(position.y));

	// go through every door in the room
	for(int i = 0; i < numDoors; i++){
		// If it is not the same door
		if(!((doors[i].x == entryPos.x) && (doors[i].y == entryPos.y))){
			// check x direction
			if((xpos >= doors[i].x) && (xpos <  doors[i].x + windowTileSize) &&
					(ypos >= doors[i].y) && (ypos < doors[i].y + windowTileSize*1.20)){
				// leave the room
				this->exitRoom();
				return true;
			}
		}

	}
	return false;
}

sf::Vector2<int> Room::getEntryPos(){
	return entryPos;
}

void Room::exitRoom(){
	// Just set to zero so when we go back in the room we dont "lock" two doors
	// there is never a door at (0,0)
	entryPos.x = 0;
	entryPos.y = 0;
}

int Room::getRoomNum(){
	return roomNum;
}

vector<sf::Vector2<int>>& Room::getDoors(){
	return doors;
}

/*(
bool Room::areEnemiesDead(){
	if(enemies.empty())
		return true;

	return false;
}


 */



