#include "OverWorld.h"

OverWorld::OverWorld(int prevState)
{
	//We are stealing a surface from the main window
	screen = SDL_GetWindowSurface(mainWindow);

	//Exit is our UI Anchor
	exit = new MenuButton(400, 520, "Exit", STATE_EXIT);
	title = new MenuButton(exit->getXPos(), exit->getYPos() - exit->height(), "Main Menu", STATE_TITLE);
	
	//If music is already playing, unload it
	if (Mix_PlayingMusic())
	{
		Mix_FreeMusic(music);
	}

	//Load overworld music
	music = loadMusic("Resources/Audio/Music/Overworld.ogg");
	
	//If it loaded correctly, play the music
	if (music != NULL)
	{
		Mix_PlayMusic(music, -1);
	}

	//The game does not start paused :P
	paused = false;

	//create/init the level
	//level = new MapBuilder("Resources/Overworld.png", 4, 3, TOTAL_TILES, LEVEL_COLUMNS, LEVEL_ROWS, TILE_WIDTH, TILE_HEIGHT);
	//level->loadMap("Resources/Overworld.map");
	//levelMap = new Map();
	//levelMap->loadMap("Resources/Maps/simpleMap.tmx");

	//Initialize the camera
	//camera = new Camera((background->w - screen->w) / 2, (background->h - screen->h) / 2, screen->w, screen->h, background->w, background->h);
	camera = new Camera(screen->w / 2, screen->h / 2, screen->w, screen->h, 960, 960);

	//Initialize the player
	player = new PlayerOverworld(100, 100, 960, 960);
}

void OverWorld::handleEvents()
{
	//line to handle character movement
	if (event.type == SDL_QUIT)
		setNextState(STATE_EXIT);
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
		paused = !paused;
	else if (event.window.event == SDL_WINDOWEVENT_RESIZED)
	{
		camera->scaleCamera(screen->w, screen->h);
	}

	//have apaused and an unpaused handler in the map an UI overlay handler
	//sound will be handled individually by each object it's most pertinent to
	//for example the level's music will stay here in overworld.cpp
	//differentiate between the 'level' and 'map'
	/*
	if (paused)
	{
		map->eventsPaused();
		UIhandler->eventsPaused();
	}
	else
	{
		map->events();
		UIhandler->events();
	}
	*/

	if (paused)
	{
		//should eventually create a data structure to house UI elements and iterate through them with handle events.
		//title UI button
		title->handleEvents();
		//exit UI button
		exit->handleEvents();
	}

	if (!paused)
	{
		//Going to need to iterate through data structure holding all objects which need to cycle events
		player->handleEvents();
	}
}

void OverWorld::logic()
{
	if (!paused)
	{
		//first we'll move the player
		//then we'll move monsters & objects

		//update the character's position
		player->move();
		//update everything else's position
	}

	//update the camera's position last
	camera->updateCamera(player->location());
}

void OverWorld::render()
{

	//first we'll render the map's background
	//then we render the player and objects
	//then we render the map's foreground
	//then finally we render the overlay

	//render the overworld at the camera's location
	//levelMap->renderMap(camera->location());

	//render the character in relation to viewport, not background
	player->render(camera->location());

	if (paused)
	{
		title->render();
		exit->render();
	}
}

OverWorld::~OverWorld(void)
{
	//Free resources

	//Release our screen surface
	SDL_FreeSurface(screen);
	
	//Delete and Null our buttons
	delete title;
	delete exit;

	title = NULL;
	exit = NULL;

	//Delete and Null our camera
	delete camera;
	camera = NULL;

	//Delete and Null our tilesheet
	delete tileSheet;
	tileSheet = NULL;

	//Delete and Null our player
	delete player;
	player = NULL;

	//Delete and Null our level map
	//delete levelMap;
	//levelMap = NULL;

	//Free and stop music
	Mix_FreeMusic(music);
}