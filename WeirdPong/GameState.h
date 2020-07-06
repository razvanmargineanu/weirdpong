#pragma once
#include "camera.h"
class GameState
{
struct state {
		bool mouseclick;
		int mouseX;
		int mouseY;
		bool player1Up;
		bool player1Down;
		int relMouseX;
		int relMouseY;
		bool cameraMoveEnabled;
		Camera_Movement camDir;
	};
struct screenResolution {
	int x;
	int y;
	int width = x;
	int height = y;
};

struct settings {
	screenResolution screenRez;
	float aspectRatio;
};

private:
	
public:
	
	GameState();
	state currentState;
	settings settings;

	void init();
	void reset();
	void toggleCameraLock();
	~GameState();
};

