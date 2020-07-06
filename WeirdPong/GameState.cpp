#include "GameState.h"



GameState::GameState()
{
}




void GameState::init()
{
	this->currentState.cameraMoveEnabled = false;
	this->reset();
	this->settings.aspectRatio = 1.0f;
	this->settings.screenRez.height = 900;
	this->settings.screenRez.width = 900;

}



void GameState::reset() {
	

	this->currentState.mouseclick = false;
	this->currentState.mouseX = 0;
	this->currentState.mouseY = 0;
	this->currentState.player1Down = false;
	this->currentState.player1Up = false;
	this->currentState.relMouseX = 0;
	this->currentState.relMouseY = 0;
	this->currentState.camDir = NONE;

}

void GameState::toggleCameraLock()
{
	this->currentState.cameraMoveEnabled = !this->currentState.cameraMoveEnabled;
}

GameState::~GameState()
{
}
