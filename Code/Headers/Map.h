/**
The purpose of this class is to differentiate between the "Level" and the "Map"
which goes in the level. The map will abstract all the contents of the level
and the functionality pertaining to those contents.

UI functionality will have its own handler class.

**/

#ifndef MAP_H
#define MAP_H

//includes for other classes
#include "PlayerOverworld.h"
#include "tinyxml2.h"

class Map
{
public:
	//default constructor
	Map();

	bool loadMap(std::string const& filePath);

	//destructor
	~Map();

private:
	//create some primitives to hold attributes of the TMX map
	int mLevelWidth, mLevelHeight, mTileWidth, mTileHeight;

	//Then we create some datastructures to hold the other objects within the map
	//vector<TileSet> tileSets;
	//vector<Layer> mapLayers;
	
	//create some classes to hold collision and objects
	//CollisionObjects mapCollision;
	//ObjectsMap mapObjects;

	//since we most likely aren't going to have a map without a player
	PlayerOverworld *mPlayer;
};

#endif