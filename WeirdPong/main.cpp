#include <glew.h>
#include <sdl.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <glm.hpp>

#include "Timer.h"
#include "Pong.h"
#include "GameState.h"
#include "InputHandler.h"

std::string programName = "WeirdPong";
SDL_Window *mainWindow;
Timer gameTimer;
SDL_Event event;

GameState gamestate;
InputHandler inputHandler;


struct {
	int width =  900;
	int height = 900;
} screen;



// opengl context handle
SDL_GLContext mainContext;
bool SetOpenGLAttributes();
void PrintSDL_GL_Attributes();
void CheckSDLError(int line);
void RunGame();
void Cleanup();

//const Uint8 *keystate = SDL_GetKeyboardState(NULL);
Pong game = Pong(&inputHandler, &gamestate);

int inputWrapper(void * userdata, SDL_Event * event) {
	int x = inputHandler.filterEvents(userdata, event);
	return x;
}

bool SetOpenGLAttributes() {

	// Set OpenGL version.
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// 3.2 OpenGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	// double buffering with 24bit Z buffer.
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);
	
	return true;
}


bool Init() {

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Failed to init SDL\n";
		return false;
	}
	SetOpenGLAttributes();
	glEnable(GL_MULTISAMPLE);
	mainWindow = SDL_CreateWindow(
		programName.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		screen.width, screen.height,
		SDL_WINDOW_OPENGL | SDL_WINDOW_INPUT_GRABBED | SDL_WINDOW_MOUSE_FOCUS |SDL_WINDOW_MOUSE_CAPTURE | SDL_WINDOW_BORDERLESS
	);

	

	mainContext = SDL_GL_CreateContext(mainWindow);

	

	SDL_GL_SetSwapInterval(1); //framerate cap to 60; set to 0 for unlimited framerate;

	#ifndef __APPLE__
		glewExperimental = GL_TRUE;
		glewInit();
	#endif
	

	gamestate.init();
	inputHandler.init(&gamestate, mainWindow);
	SDL_SetEventFilter(inputWrapper, mainWindow);


	return true;

}


int main(int argc, char* argv[]) {

	if (!Init())
		return -1;

	RunGame();
	Cleanup();
	return 0;

}

void RunGame()
{

	bool loop = true;
	gameTimer.start();
	game.initGame();


	while (loop)
	{
	
		
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				loop = false;
			
			
		}
		SDL_PumpEvents();

		float tick = gameTimer.timeDelta;
		
		game.update((float)gameTimer.timeDelta, (float)gameTimer.getTicks());
		game.renderFrame((float)gameTimer.timeDelta, (float)gameTimer.getTicks());


		
		
		SDL_GL_SwapWindow(mainWindow);
		gameTimer.tick();
		SDL_Delay(1);

	}
}






void Cleanup()
{
	// Delete OpengL context
	SDL_GL_DeleteContext(mainContext);
	// Destroy window
	SDL_DestroyWindow(mainWindow);
	// Shutdown SDL 2
	SDL_Quit();
}

void CheckSDLError(int line = -1)
{
	const char* error = SDL_GetError();

	if (error != "")
	{
		std::cout << "SLD Error : " << error << std::endl;

		if (line != -1)
			std::cout << "\nLine : " << line << std::endl;

		SDL_ClearError();
	}
}

void PrintSDL_GL_Attributes()
{
	int value = 0;
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &value);
	std::cout << "SDL_GL_CONTEXT_MAJOR_VERSION : " << value << std::endl;

	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &value);
	std::cout << "SDL_GL_CONTEXT_MINOR_VERSION: " << value << std::endl;
}