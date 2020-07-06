#pragma once
#include "model.h"
#include <vector>
#include "Shader.h"
#include "camera.h"
#include "Terrain.h"
#include "InputHandler.h"
#include "GameState.h"
#include "Line.h"
class Pong
{
private:
	vector<std::string>modelPaths;

	Terrain terrain;
	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 model;
	Camera camera;
	vector<Mesh> myCube;
	
	//bool cameraMoveEnabled;
	unsigned int depthMapFBO;
	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	unsigned int depthMap;
	InputHandler* inputHandler;
	GameState* gameState;

	glm::vec3 mpoint1;
	glm::vec3 mpoint2;
	Line line;
	
public:
	vector<Model> sceneModels;
	vector<Shader> shaders;
	struct {
		int relMouseX;
		int relMouseY;
		Camera_Movement camDir;
		bool player1Up;
		bool player1Down;
		bool cameraMoveEnabled;
		bool mouseclick;
		int mouseX;
		int mouseY;
	}gUpdateData;
	


	Pong();
	Pong(InputHandler*, GameState*);
	void mouseClick();
	void CheckIntersection(Model model);
	void toggleCameraMoveEnable();
	void initGame();
	void initGL();
	void update(float deltatime, float gameTime);
	void renderFrame(float deltatime, float gameTime);
	~Pong();
};

