/*
 * TextureLoader.h
 *
 *  Created on: Aug 12, 2018
 *      Author: chrisluttio
 */

#ifndef UTIL_TEXTURELOADER_H_
#define UTIL_TEXTURELOADER_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../libraries/stb_image.h"

class TextureLoader {
public:
	GLuint load(const char* name, GLenum type);
};

#endif /* UTIL_TEXTURELOADER_H_ */
