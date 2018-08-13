/*
 * Shader.h
 *
 *  Created on: Aug 11, 2018
 *      Author: chrisluttio
 */

#ifndef SHADERS_SHADER_H_
#define SHADERS_SHADER_H_

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
	unsigned int id;

	Shader(const char* name);
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

	void use();

	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setVec3(const std::string &name, glm::vec3) const;
	void setMat4(const std::string &name, glm::mat4) const;

private:
	int compileShader(GLuint type, const char* source);
	const char* readFile(const char* name);
	void logLinkStatus(unsigned int);
	void logShaderStatus(unsigned int, GLuint);
};

#endif /* SHADERS_SHADER_H_ */
