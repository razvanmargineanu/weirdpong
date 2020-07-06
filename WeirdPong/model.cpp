#include "model.h"
#include "stb_image.h"
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>


Model::Model()

{
	isBound = false;
	isInitialized = false;
	transform = glm::mat4(1.0);
	modelDir = "../Resources/Models/";
	textureDir = "../Resources/Textures/";
}

Model::Model(glm::vec3 pos) {

	isBound = false;
	isInitialized = false;

	modelDir = "../Resources/Models/";
	textureDir = "../Resources/Textures/";
	transform = glm::mat4(1.0);
	//pos = glm::vec3(02.0f, 2.0f, -5.0f);
	xform(pos);

}

void Model::init(vector<Mesh> inMeshes) {

	for (unsigned int i = 0; i < inMeshes.size(); i++) {
		meshes.push_back(inMeshes[i]);
	}

}

void Model::init(vector<Mesh> inMeshes, glm::vec3 pos) {

	for (unsigned int i = 0; i < inMeshes.size(); i++) {
		meshes.push_back(inMeshes[i]);
	}
	xform(pos);
}

void Model::init(string const & path) {
	loadModel(path);
}

vector<Mesh> Model::getMeshes() {
	return meshes;
}

void Model::loadModel(string const &path) {
	// read file via ASSIMP
	Assimp::Importer importer;
	string fullpath = modelDir + path;
	const aiScene* scene = importer.ReadFile(fullpath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	// check for errors
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
		return;
	}
	// retrieve the directory path of the filepath
	modelDir = path.substr(0, path.find_last_of('/'));

	// process ASSIMP's root node recursively
	processNode(scene->mRootNode, scene);
}



GLint Model::loadTexture(string filename) {

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	textureData = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);

	if (textureData) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(textureData);

	return texture;
}

Mesh Model::processMesh(aiMesh * mesh, const aiScene * scene)
{
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{

		Vertex vertex;
		glm::vec3 vector;
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;

		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.Normal = vector;
		if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);
		vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
		// process material
		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
			vector<Texture> diffuseMaps = loadMaterialTextures(material,
				aiTextureType_DIFFUSE, "texture_diffuse");
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			vector<Texture> specularMaps = loadMaterialTextures(material,
				aiTextureType_SPECULAR, "texture_specular");
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		}

	return Mesh(vertices, indices, textures);
}

void Model::processNode(aiNode * node, const aiScene * scene)
{
	// process all the node's meshes (if any)
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
	// then do the same for each of its children
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

vector<Texture> Model::loadMaterialTextures(aiMaterial * mat, aiTextureType type, string typeName)
{
	vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		Texture texture;
		texture.id = TextureFromFile(str.C_Str(), directory);
		texture.type = typeName;
		texture.path = str;
		textures.push_back(texture);
	}
	return textures;
}

void Model::xform(glm::vec3 pos) {

	this->transform = glm::translate(this->transform, pos); //0.0f,1.0f,0.0f
																			
}


void Model::xform(float deltatime, float totaltime, float x, float y ,float z) {

	this->transform = glm::translate(this->transform, glm::vec3(x,y,z)*deltatime); //0.0f,1.0f,0.0f
	//this->transform = glm::rotate(this->transform, 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));

}

glm::mat4 Model::getTransform() {

	return this->transform;
}

void Model::draw(Shader shader)
{
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i].Draw(shader);
	}
}


Model::~Model()
{

}

