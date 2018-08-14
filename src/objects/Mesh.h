/*
 * Mesh.h
 *
 *  Created on: Aug 13, 2018
 *      Author: chrisluttio
 */

#ifndef OBJECTS_MESH_H_
#define OBJECTS_MESH_H_

#include "../shaders/Shader.h"
#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 coord;
};

struct Texture {
	unsigned int id;
	string type;
	string path;
};

class Mesh {
	public:
		vector<Vertex> vertices;
		vector<unsigned int> indices;
		vector<Texture> textures;

		Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
		void draw(Shader* shader);
	private:
		unsigned int VAO, VBO, EBO;
		void setupMesh();
};

#endif /* OBJECTS_MESH_H_ */
