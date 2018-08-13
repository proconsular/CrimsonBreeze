/*
 * BufferObject.h
 *
 *  Created on: Aug 12, 2018
 *      Author: chrisluttio
 */

#ifndef OBJECTS_BUFFEROBJECT_H_
#define OBJECTS_BUFFEROBJECT_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

class BufferObject {
public:
	BufferObject(float* vertices, unsigned int length, unsigned int sides);
	virtual ~BufferObject();

	void enableAttrib(GLuint id, GLuint size, GLuint stride, GLuint offset);
	void bind();
	void draw();
private:
	unsigned int VAO, VBO, length, sides;
};

#endif /* OBJECTS_BUFFEROBJECT_H_ */
