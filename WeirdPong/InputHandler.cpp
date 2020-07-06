#include "InputHandler.h"



InputHandler::InputHandler()
{

}




void InputHandler::init(GameState *gamestate, SDL_Window *mainWindow)
{
	//SDL_SetEventFilter(&this->filterEvents, mainWindow);
	this->mainWindow = mainWindow;
	this->gamestate = gamestate;
}

void InputHandler::checkKeyboard()
{
	if (keystate[SDL_SCANCODE_CAPSLOCK]) {
		//gamestate->toggleCameraLock();
	}

	if (keystate[SDL_SCANCODE_W]) {
		gamestate->currentState.camDir = FORWARD;
	}
	if (keystate[SDL_SCANCODE_A]) {
		gamestate->currentState.camDir = LEFT;
	}
	if (keystate[SDL_SCANCODE_S]) {
		gamestate->currentState.camDir = BACKWARD;
	}
	if (keystate[SDL_SCANCODE_D]) {
		gamestate->currentState.camDir = RIGHT;
	}

	if (keystate[SDL_SCANCODE_W] && keystate[SDL_SCANCODE_D]) {
		gamestate->currentState.camDir = FRONTRIGHT;
	}
	if (keystate[SDL_SCANCODE_W] && keystate[SDL_SCANCODE_A]) {
		gamestate->currentState.camDir = FRONTLEFT;
	}
	if (keystate[SDL_SCANCODE_UP]) {
		gamestate->currentState.player1Up = true;
	}
	if (keystate[SDL_SCANCODE_DOWN]) {
		gamestate->currentState.player1Down = true;

	}
}

void InputHandler::checkMouse()
{
}

int InputHandler::filterEvents(void * userdata, SDL_Event * event)
{

	static int boycott = 1;
	if ((event->type == SDL_QUIT) && boycott) {
		printf("Quit event filtered out -- try again.\n");
		boycott = 0;
		//Cleanup();
		return(0);
	}

	if (event->type == SDL_MOUSEMOTION && boycott) {

		boycott = 0;
		if (gamestate->currentState.cameraMoveEnabled) {
			SDL_WarpMouseInWindow(mainWindow, gamestate->settings.screenRez.width / 2, gamestate->settings.screenRez.height / 2);
		}
		gamestate->currentState.relMouseX = event->motion.xrel;
		gamestate->currentState.relMouseY = -1 * event->motion.yrel;

		return(0);    /* Drop it, we've handled it */
	}
	if (event->type == SDL_KEYUP) {
		if (event->key.keysym.scancode == SDL_SCANCODE_CAPSLOCK) {
			gamestate->toggleCameraLock();
			SDL_ShowCursor(!SDL_ShowCursor(SDL_QUERY));
		}
		gamestate->currentState.camDir = NONE;
		return(0);
	}

	if (event->type == SDL_MOUSEBUTTONUP) {
		std::cout << "InputHandler:mouseclick: " << event->motion.x << ":" << event->motion.y << std::endl;
		gamestate->currentState.mouseclick = true;
		gamestate->currentState.mouseX = event->motion.x;
		gamestate->currentState.mouseY = event->motion.y;

	}

	boycott = 1;

	return 1;

}



void InputHandler::update()
{
	this->checkKeyboard();
	this->checkMouse();
}


void InputHandler::poll()
{

	while (SDL_PollEvent(&event))
	{
		//if (event.type == SDL_QUIT)
			//loop = false;


	}
	SDL_PumpEvents();
	this->checkKeyboard();
}


InputHandler::~InputHandler()
{

}
