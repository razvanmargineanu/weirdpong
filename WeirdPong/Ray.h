#pragma once
#include <glm.hpp>
#include <vector>
#include "GameState.h"
using namespace std;
class Ray
{
private:
	float worldX, worldY, worldZ, worldZ2, worldW;
	glm::mat4 matProjection;
	glm::mat4 matInverse;
	glm::vec4 viewport;
	glm::vec4 vIn;
	glm::vec4 vIn2;
	glm::vec4 mouseWorld;
	glm::vec4 mouseWorld2;
	glm::vec3 point2;
	glm::vec3 point1;
	glm::vec3 retArr[2];
public:
	Ray();
	void cast(glm::mat4 projection, glm::mat4 view, GameState *gameState, glm::vec3*);
	~Ray();
};

