#include "Map.h"


Map::Map()
{
}

bool Map::loadMap(std::string const& filePath)
{
	//load the map, yadda yadda

	//create our player based on the data parsed from the tmx
	mPlayer = new PlayerOverworld(100, 200, 960, 960);
}

Map::~Map()
{
	//delete pointers
	delete mPlayer;

	//null dangling pointers
	mPlayer = NULL;
}
