#include "Title.h"

Title::Title(void)
{
	SDL_Surface *background = loadImage("Resources/Graphics/Backgrounds/Title.png");

	if (background == NULL)
		cerr << "STATE_TITLE: Could not load background image.";
	else
	{
		backgroundTexture = SDL_CreateTextureFromSurface(renderer, background);
		SDL_FreeSurface(background);
	}

	//I've decided to make exit the anchor point and build 'up' from it since it remains constant in the menus
	exit = new MenuButton(400, 520, "Exit", STATE_EXIT);
	credits = new MenuButton(exit->getXPos(), exit->getYPos() - exit->height(), "Credits", STATE_CREDITS);
	options = new MenuButton(credits->getXPos(), credits->getYPos() - credits->height(), "Options", STATE_OPTIONS);
	start = new MenuButton(options->getXPos(), options->getYPos() - options->height(), "Start", STATE_OVERWORLD);

	//If music is not playing, then we load a file into the global music channel
	if (!Mix_PlayingMusic())
	{
		music = loadMusic("Resources/Audio/Music/Title.ogg");

		//If the music file has been successfully loaded, we begin playing it
		if (music != NULL)
			Mix_PlayMusic(music, -1);
	}
}

void Title::handleEvents()
{
		if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
			setNextState(STATE_EXIT);

		start->handleEvents();
		options->handleEvents();
		credits->handleEvents();
		exit->handleEvents();
}

void Title::logic()
{
}

void Title::render()
{
	SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

	start->render();
	options->render();
	credits->render();
	exit->render();
}

Title::~Title(void)
{
	SDL_DestroyTexture(backgroundTexture);

	delete start;
	delete options;
	delete credits;
	delete exit;

	start = NULL;
	options = NULL;
	credits = NULL;
	exit = NULL;
}