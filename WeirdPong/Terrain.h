#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "stb_image.h"
#include "Shader.h"
#include <vector>

struct TerrainVertex {
	// position
	glm::vec3 Position;
	// normal
	glm::vec3 Normal;
	// texCoords
	glm::vec2 TexCoords;
	//color
	glm::vec3 VertexColor;
};

struct Indice {
	unsigned int x;
	unsigned int y;
	unsigned int z;
};



class Terrain
{
private:
	int length, width, lRes, wRes;
	int moduleSize;
	glm::mat4 transform;
	std::vector<TerrainVertex> vertices;
	std::vector<Indice> indices;
	//std::vector<Texture> textures;

	/*  Render data  */
	unsigned int VAO, VBO, EBO;
	

	void setupMesh();

	

public:
	Terrain();
	void UpdateMesh(float gameTime);
	void init(int wRes, int lRes, int width, int length);
	void Draw(Shader shader);
	glm::mat4 getTransform();
	~Terrain();
};

