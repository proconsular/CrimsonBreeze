/*
 * Shader.cpp
 *
 *  Created on: Aug 11, 2018
 *      Author: chrisluttio
 */

#include "Shader.h"

Shader::Shader(const char* name) {
	id = 0;
	std::string common = "src/shader_source/";
	std::string vtx = common + name + ".vs";
	std::string fgx = common + name + ".fs";
	new (this) Shader(vtx.c_str(), fgx.c_str());
}

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	const char* vShaderCode = readFile(vertexPath);
	const char* fShaderCode = readFile(fragmentPath);

	unsigned int vertex = compileShader(GL_VERTEX_SHADER, vShaderCode);
	unsigned int fragment = compileShader(GL_FRAGMENT_SHADER, fShaderCode);

	delete vShaderCode;
	delete fShaderCode;

	id = glCreateProgram();
	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
	glLinkProgram(id);

	logLinkStatus(id);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

int Shader::compileShader(GLuint type, const char* source) {
	unsigned int shader_id = glCreateShader(type);
	glShaderSource(shader_id, 1, &source, NULL);
	glCompileShader(shader_id);

	logShaderStatus(shader_id, type);

	return shader_id;
}

void Shader::logShaderStatus(unsigned int shader_id, GLuint type) {
	int success = 0;
	char infoLog[512];

	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader_id, 512, NULL, infoLog);
		std::string kind = "";
		if (type == GL_VERTEX_SHADER)
			kind = "VERTEX";
		else
			kind = "FRAGMENT";
		std::cout << "ERROR::SHADER::" << kind << "::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void Shader::logLinkStatus(unsigned int program) {
	int success;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
}

const char* Shader::readFile(const char* name) {
	std::string code;
	std::ifstream file;

	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		file.open(name);
		std::stringstream string_stream;

		string_stream << file.rdbuf();

		file.close();

		code = string_stream.str();
	} catch (std::ifstream::failure &e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	return strdup(code.c_str());
}

void Shader::use() {
	glUseProgram(id);
}

void Shader::setBool(const std::string &name, bool value) const {
	glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const {
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setVec3(const std::string &name, glm::vec3 vector) const {
	glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(vector));
}

void Shader::setMat4(const std::string &name, glm::mat4 mat) const {
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}










