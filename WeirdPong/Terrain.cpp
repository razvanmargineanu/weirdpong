#include "Terrain.h"
#include "PerlinNoise.hpp"

Terrain::Terrain()
{
	moduleSize = 10;
	transform = glm::mat4(1.0);
}

void Terrain::init(int wRes, int lRes, int width, int length)
{
	this->width = width;
	this->length = length;
	this->lRes = lRes;
	this->wRes = wRes;
	const float w = (float) width, l = (float)length;
	int seed = 30;
	const siv::PerlinNoise perlin(seed);
	const double height = 100;

	int i = 0;
	//vertices
	for (int z = 0; z < lRes; z++) {
		for (int x = 0; x < wRes; x++) {
			TerrainVertex v;
			double y = perlin.octaveNoise0_1((double)x / (double)wRes*3, (double)z / (double)lRes*3, 6)*height;
			if (y <height/2) {
				y = 0;
			}
			else {
				y = y- height/2;
			}
			v.Position = glm::vec3(x / (float)wRes, y, z / (float)lRes);

			v.Position.x *= w;
			v.Position.z *= l;
			v.Position.x -= w / 2.0f;
			v.Position.z -= l / 2.0f;
			
			if (y > 0 && y < 1) {
				v.VertexColor = glm::vec3(0.278f, 0.709f, 1);
			}
			else if (y >1 && y < 6) {
				v.VertexColor = glm::vec3(1, 0.713f, 0.278f);
			}
			else if (y > 6 && y < 15) {
				v.VertexColor = glm::vec3(0.301f, 0.760f, 0.278f);
			}
			else if (y > 15 && y < 25) {
				v.VertexColor = glm::vec3(0.031f, 0.290f, 0.101f);
			}
			else if (y > 25 && y < 35) {
				v.VertexColor = glm::vec3(0.031f, 0.290f, 0.101f);
			}
			else if (y > 35 && y < 50) {
				v.VertexColor = glm::vec3(0.215f, 0.168f, 0.066f);
			}
			else if (y > 50 && y < 100) {
				v.VertexColor = glm::vec3(0.647f, 0.623f, 0.572f);
			}
			else {
				v.VertexColor = glm::vec3(0.278f, 0.709f, 1);
			}

			
			//v.VertexColor = glm::normalize(v.VertexColor);

			v.Normal = glm::vec3(0.0f, 1.0f, 0.0f);

			v.TexCoords = glm::vec2(v.Position.x/w, v.Position.z/l);
			this->vertices.push_back(v);

			if ((i + 1) % wRes != 0 && z + 1 < lRes) {
				Indice tri;
				Indice tri2;
				tri.x = i;
				tri.y = i + wRes;
				tri.z = i + 1;
				tri2.x = i + wRes;
				tri2.y = i+1;
				tri2.z = i+wRes+1;
				this->indices.push_back(tri);
				this->indices.push_back(tri2);
			}
			i++;
		}
	}

	this->setupMesh();

}

void Terrain::setupMesh() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	int size = this->indices.size() * sizeof(Indice);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size()*sizeof(TerrainVertex), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(Indice), &indices[0], GL_STATIC_DRAW);

	//vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(TerrainVertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(TerrainVertex), (void*)offsetof(TerrainVertex, Normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(TerrainVertex), (void*)offsetof(TerrainVertex, TexCoords));

	// vertex color
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(TerrainVertex), (void*)offsetof(TerrainVertex, VertexColor));

	glBindVertexArray(0);
}

void Terrain::UpdateMesh(float gameTime) {
	int seed = 30;
	const siv::PerlinNoise perlin(seed);
	//float y = perlin.octaveNoise0_1(x / (300.0), z / (300.1), 6)*200.0f;

	for (int z = 0; z < lRes; z++) {
		for (int x = 0; x < wRes; x++) {
			double y = perlin.octaveNoise0_1(x / (300.0), z / (300.1), 6)*(200.0f/ gameTime);
			TerrainVertex v;
			v = vertices[z*lRes + x];
			v.Position.y = (float)y;
		}
	}
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(TerrainVertex), &vertices[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	//gl
}

void Terrain::Draw(Shader shader)
{
	//glActiveTexture(GL_TEXTURE0);

	// draw mesh
	shader.use();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size()*3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}

glm::mat4 Terrain::getTransform() {
	return this->transform;
}

Terrain::~Terrain()
{
}
