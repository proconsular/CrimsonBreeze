/*
 * Model.h
 *
 *  Created on: Aug 13, 2018
 *      Author: chrisluttio
 */

#ifndef OBJECTS_MODEL_H_
#define OBJECTS_MODEL_H_

#include "../shaders/Shader.h"
#include "Mesh.h"

#include <vector>
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace std;

class Model {
public:
	Model(const char *path) {
		loadModel(path);
	}
	void draw(Shader* shader);
private:
	vector<Texture> loaded_textures;
	vector<Mesh> meshes;
	string directory;

	void loadModel(string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
	unsigned int TextureFromFile(const char* path, const string &directory);
};

#endif /* OBJECTS_MODEL_H_ */
