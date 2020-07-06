#include "Pong.h"
#include <gtc\type_ptr.hpp>
#include <thread>
#include "Ray.h"


void test() {
	std::cout << "thread ran:!" << std::endl;
}

Pong::Pong() {


}
Pong::Pong(InputHandler  *_inputHandler, GameState *_gameState)
{
	this->mpoint1 = glm::vec3(0.0f, 15.0f, 10.0f);
	this->mpoint2 = glm::vec3(0.0f, 15.0f,-10.0f);
	this->inputHandler = _inputHandler;
	this->gameState = _gameState;
}





void Pong::initGame()
{
	model = glm::mat4(1.0f);
	view = glm::mat4(1.0f);
	projection = glm::mat4(1.0f);
	camera = Camera(glm::vec3(0.0f, 22.0f, 16.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f,-54.0f);
	projection = glm::perspective(45.0f, 900.0f / 900.0f, 0.1f, 1000.0f);

	gUpdateData.camDir = NONE;

	modelPaths.push_back("stage.obj");
	modelPaths.push_back("monkey.obj");
	gUpdateData.cameraMoveEnabled = false;
	


	for (unsigned int i=0; i < modelPaths.size(); i++) {
		Model m = Model();
		m.init(modelPaths[i]);
		sceneModels.push_back(m);
	}
	Model* cubemesh = new Model();
	cubemesh->init("monkey.obj");
	myCube = cubemesh->getMeshes();
	delete cubemesh;

	Shader standardShader("../Resources/Shaders/basic.vertex.glsl", "../Resources/Shaders/basic.fragment.glsl");
	Shader terrainShader("../Resources/Shaders/terrain.vertex.glsl", "../Resources/Shaders/terrain.fragment.glsl");
	shaders.push_back(standardShader);
	shaders.push_back(terrainShader);


	terrain = Terrain();
	terrain.init(300,300,500,500);

	line = Line(this->mpoint2, this->mpoint1, projection, view, glm::mat4(1.0f));
	initGL();

}

void Pong::initGL()
{
	//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	glEnable(GL_DEPTH_TEST);


}

void Pong::update(float deltatime, float gameTime)
{
	view = camera.GetViewMatrix();
	this->inputHandler->update();


	//glm::vec4 viewVector = glm::vec4(camera.Position,1.0f);
	

	for (unsigned int i = 0; i < sceneModels.size(); i++) {
		Model *m = &sceneModels[i];
		
		if (gUpdateData.player1Up && i==1) {
			m->xform(deltatime, gameTime, 0.0f,0.0f, 15.0f);
		}
		if (gUpdateData.player1Down && i == 1) {
			m->xform(deltatime, gameTime, 0.0f, 0.0f, -15.0f);
		}

	}

	if (this->gameState->currentState.cameraMoveEnabled) {
		camera.ProcessKeyboard(this->gameState->currentState.camDir, deltatime);
		camera.ProcessMouseMovement(this->gameState->currentState.relMouseX*1.0f, this->gameState->currentState.relMouseY*1.0f, true);

	}

	if (this->gameState->currentState.mouseclick) {
		Ray r;
		glm::vec3 points[2];
		r.cast(projection, view, gameState, points);
		this->mpoint2 = points[0];
		this->mpoint1 = points[1];
	}
	line.Update(this->mpoint2, this->mpoint1, projection, view, glm::mat4(1.0f));



	

	this->gameState->reset();
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}




void Pong::renderFrame(float deltatime, float gameTime)
{

	//glm::vec3 sceneLight = glm::vec3(cos(gameTime / 300) * 20, 5.0f, sin(gameTime / 300) * 20);
	glm::vec3 sceneLight = glm::vec3(0.0f, sin(gameTime / 1000) * 80+130, 0.0f);

	shaders[0].use();

	shaders[0].setVec3("viewPos", camera.Position);
	shaders[0].setVec3("alightPos", sceneLight);
	
	shaders[0].setMat4("view", view);
	shaders[0].setMat4("projection", projection);

	
	for (unsigned int i=0; i < sceneModels.size();i++) {
		Model *m = &sceneModels[i];
		shaders[0].setMat4("model", m->getTransform());

		//sceneModels.at(i).draw(shaders[0]);
	}

	line.Draw();

	shaders[1].use();
	shaders[1].setVec3("viewPos", camera.Position);
	shaders[1].setVec3("alightPos", sceneLight);
	shaders[1].setMat4("view", view);
	shaders[1].setMat4("projection", projection);

	shaders[1].setMat4("model", terrain.getTransform());
	terrain.Draw(shaders[1]);
	


	

	

}


void Pong::CheckIntersection(Model model) {

}



Pong::~Pong()
{
}


