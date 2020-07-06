#pragma once
#include <glew.h>
#include <vector>
#include "Shader.h"
#include <stddef.h> 

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include "Mesh.h"
class Model
{



	int numVertices;
	int numIndices;

	vector<Mesh> meshes;


	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::string textureFileName;
	std::vector<float> vertVector;

	std::string textureDir;
	std::string modelDir;

	string directory;

	GLuint vertexBufferID;
	GLuint elementBufferObjectId;
	GLuint vertexArrayObjectId;
	GLuint vertexBufferId;
	GLuint texCoordBufferId;



	
public:

	Shader shader;

	Model();
	Model::Model(glm::vec3 pos);

	void init(vector<Mesh> meshes);

	void init(vector<Mesh> inMeshes, glm::vec3 pos);

	void init(string const & path);

	vector<Mesh> getMeshes();

	//bool bind();
	void xform(float deltatime, float totaltime, float x, float y, float z);
	void xform(glm::vec3 pos);

	glm::mat4 getTransform();


	void draw(Shader shader);

	~Model();

private:
	glm::mat4 transform;
	bool isInitialized;
	bool isBound;
	unsigned char *textureData;
	unsigned int texture;
	int width, height, nrChannels;

	bool bindTexture();
	GLint loadTexture(string filename);

	void loadModel(string const & path);

	Mesh processMesh(aiMesh *mesh, const aiScene *scene);

	void processNode(aiNode *node, const aiScene *scene);\

	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
		string typeName);
};

