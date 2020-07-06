#include "Ray.h"



Ray::Ray()
{
	this->worldX, this->worldY, this->worldZ, this->worldZ2, this->worldW = 1.0f;
}

void Ray::cast(glm::mat4 projection, glm::mat4 view, GameState *gameState, glm::vec3* points) {
	matProjection = projection*view;
	this->matInverse = glm::inverse(matProjection);

	this->worldX = (((float)gameState->currentState.mouseX / 900.0f)*2.0f) - 1.0f;
	this->worldY = 1.0f - ((float)gameState->currentState.mouseY / 900.0f)*2.0f;
	this->worldZ = 1.0f;
	this->worldZ2 = -1.0f;
	this->worldW = 1.0f;


	this->vIn = glm::vec4(this->worldX, this->worldY, this->worldZ, this->worldW);
	this->vIn2 = glm::vec4(this->worldX, this->worldY, this->worldZ2, this->worldW);
	this->mouseWorld = this->matInverse * this->vIn;
	this->mouseWorld2 = this->matInverse * this->vIn2;

	mouseWorld.x *= 1.0f / mouseWorld.w;
	mouseWorld.y *= 1.0f / mouseWorld.w;
	mouseWorld.z *= 1.0f / mouseWorld.w;
	mouseWorld2.x *= 1.0f / mouseWorld2.w;
	mouseWorld2.y *= 1.0f / mouseWorld2.w;
	mouseWorld2.z *= 1.0f / mouseWorld2.w;
	this->retArr[0] = mouseWorld;
	this->retArr[1] = mouseWorld2;
	points[0] = retArr[0];
	points[1] = retArr[1];
}


Ray::~Ray()
{
}
