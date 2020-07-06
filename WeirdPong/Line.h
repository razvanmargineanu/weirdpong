#pragma once
#include <glew.h>
#include <glm.hpp>
#include <vector>
#include "Shader.h"
#include <iostream>

using namespace std;

class Line
{
private:
	GLuint VBOvertexBuffer;
	GLuint VAObuffer;
	vector<glm::vec3> vertices;
	Shader shd;
	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 model;



public:
	Line();
	Line(glm::vec3 point1, glm::vec3 point2, glm::mat4 projection, glm::mat4 view, glm::mat4 model);
	void initGl();
	void Update(glm::vec3 point1, glm::vec3 point2, glm::mat4 projection, glm::mat4 view, glm::mat4 model);
	void Draw();
	~Line();
};

