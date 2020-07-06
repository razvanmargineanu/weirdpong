#pragma once
#include "camera.h"
#include "GameState.h"
#include <sdl.h>
#include <iostream>
class InputHandler
{



private:
	GameState *gamestate;

	SDL_Event event;
	
	const Uint8 *keystate = SDL_GetKeyboardState(NULL);

	void checkKeyboard();
	void checkMouse();
	SDL_Window *mainWindow;
public:
	InputHandler();
	void update();
	void init(GameState *gamestate, SDL_Window *mainWindow);
	void poll();
	int filterEvents(void* userdata, SDL_Event* event);
		
	~InputHandler();
};

