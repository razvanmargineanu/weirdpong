#include "Line.h"


Line::Line(){}
Line::Line(glm::vec3 _point1, glm::vec3 _point2, glm::mat4 _projection, glm::mat4 _view, glm::mat4 _model)
{
	this->vertices.push_back(_point2);
	this->vertices.push_back(_point1);
	this->projection = _projection;
	this->view = _view;
	this->model = _model;
	this->shd = Shader("../Resources/Shaders/line.vertex.glsl", "../Resources/Shaders/line.fragment.glsl");
	this->initGl();
}


void Line::initGl() {
	glGenVertexArrays(1, &this->VAObuffer);
	glGenBuffers(1, &this->VBOvertexBuffer);
	glBindVertexArray(this->VAObuffer);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBOvertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(glm::vec3), &this->vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	glBindVertexArray(0);
}


void Line::Update(glm::vec3 _point1, glm::vec3 _point2, glm::mat4 _projection, glm::mat4 _view, glm::mat4 _model) {
	this->vertices[0] = _point2;
	this->vertices[1] = _point1;
	this->projection = _projection;
	this->view = _view;
	this->model = _model;
	glBindVertexArray(this->VAObuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBOvertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(glm::vec3), &this->vertices[0], GL_STATIC_DRAW);
	glBindVertexArray(0);
}

void Line::Draw() {
	this->shd.use();
	this->shd.setMat4("view", view);
	this->shd.setMat4("projection", projection);
	this->shd.setMat4("model", model);
	glBindVertexArray(this->VAObuffer);
	glDrawArrays(GL_LINES, 0, vertices.size());
}


Line::~Line()
{
}
