/*
 * BufferObject.cpp
 *
 *  Created on: Aug 12, 2018
 *      Author: chrisluttio
 */

#include "BufferObject.h"

BufferObject::BufferObject(float* vertices, unsigned int length, unsigned int sides) {
	this->length = length;
	this->sides = sides;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, length, vertices, GL_STATIC_DRAW);
}

void BufferObject::enableAttrib(GLuint id, GLuint size, GLuint stride, GLuint offset) {
	glVertexAttribPointer(id, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
	glEnableVertexAttribArray(id);
}

void BufferObject::bind() {
	glBindVertexArray(VAO);
}

void BufferObject::draw() {
	glDrawArrays(GL_TRIANGLES, 0, sides);
}

BufferObject::~BufferObject() {

}

