#pragma once

#ifndef MODEL
#define MODEL

#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"

class Model
{

public:
	Model(const char* path) {
		LoadModel(path);
	}
	Model(const char* path, Shader* shader_pointer) : shader(shader_pointer) {
		LoadModel(path);
	}
	void Draw(Shader& shader);
	void Draw();
	void SetShader(Shader* shader_pointer) {
		shader = shader_pointer;
	}
private:
	// Fields
	vector<Mesh> meshes;
	vector<Texture> textures_loaded;
	string directory;
	Shader * shader;

	void LoadModel(string path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, string type_name);
};

unsigned int TextureFromFile(const char * path, const string &directory, bool gamma=false);

#endif   

