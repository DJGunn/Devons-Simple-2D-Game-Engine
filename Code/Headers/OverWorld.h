#ifndef OVERWORLD_H
#define OVERWORLD_H


#include "Camera.h"
#include "GeneralizedInclude.h"
#include "MenuButton.h"
//#include "Player.h"
#include "PlayerOverworld.h"
#include "Gamestate.h"
#include <iostream>

class OverWorld :
	public GameState
{
public:
	OverWorld(int prevState = NULL);

	//Handles overworld events
	void handleEvents();

	//Processes overworld logic
	void logic();

	//Renders overworld
	void render();

	~OverWorld(void);
private:
	//primitives
	int levelWidth, levelHeight;
	bool paused;
	
	//Non-Dynamic Objects
	SDL_Rect resizeOffset;

	//Mix_Music *music;
	
	//Dyanmic Memory Objects
	Camera *camera;
	//Player *player;
	PlayerParent *player;
	SDL_Surface *tileSheet;
	SDL_Surface *screen;

	//Menu Buttons
	MenuButton *title;
	MenuButton *exit;

	//tileset and level information//
	//how many tiles are in the tileset
	static const int NUM_TILE_SPRITES = 12;
	//how big each tile in the tilesheet is
	static const int TILE_WIDTH = 80, TILE_HEIGHT =  80;
	//how many tiles make up the level
	static const int TOTAL_TILES = 192;
	static const int LEVEL_COLUMNS = 16;
	static const int LEVEL_ROWS = 12;
	//the enumerated types
	const enum TileTypes
	{
		RED, GREEN, BLUE,
		TOP_LEFT, LEFT, BOTTOM_LEFT,
		TOP, CENTER, BOTTOM,
		TOP_RIGHT, RIGHT, BOTTOM_RIGHT
	};
	//array holding the clips of each tile
	SDL_Rect tileClips[NUM_TILE_SPRITES];//likely deprecated

	//the level builder
	//MapBuilder* level;

};

#endif