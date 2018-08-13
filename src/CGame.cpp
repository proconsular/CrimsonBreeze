//============================================================================
// Name        : CGame.cpp
// Author      : Chris Luttio
// Version     :
// Copyright   : Copyright 2018 Chris Luttio
// Description : Hello World in C, Ansi-style
//============================================================================

#include <math.h>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "libraries/stb_image.h"
#include "shaders/Shader.h"

#include "camera/Camera.h"

#include "objects/BufferObject.h"
#include "util/TextureLoader.h"

using namespace std;

void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void setup();
void render(GLFWwindow* window);

float vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

const float screenWidth = 800;
const float screenHeight = 600;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

float lastX = 400, lastY = 300;

bool firstMouse = true;

float fov = 60.0f;

Camera* camera;
Shader* lighting;
Shader* lamp;

glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f,  2.0f, -2.5f),
    glm::vec3( 1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

glm::mat4 model;

GLFWwindow* window;

BufferObject* cube;

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

int main(void) {
	setup();

	cube = new BufferObject(vertices, sizeof(vertices), 36);
	cube->enableAttrib(0, 3, 8, 0);
	cube->enableAttrib(1, 3, 8, 3);
	cube->enableAttrib(2, 2, 8, 6);

	camera = new Camera(glm::vec3(0, 1, 3));

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(60.0f), screenWidth / screenHeight, 0.1f, 100.0f);

	model = glm::mat4();
	model = glm::translate(model, lightPos);
	model = glm::scale(model, glm::vec3(0.2f));

	glm::vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);

	lighting = new Shader("spotlight");
	lighting->use();
	lighting->setMat4("projection", projection);
	lighting->setVec3("objectColor", glm::vec3(1.0f, 1.0f, 1.0f));
	lighting->setVec3("lightColor", lightColor);
	lighting->setVec3("viewPos", camera->position);

	lighting->setInt("material.diffuse", 0);
	lighting->setInt("material.specular", 1);
	lighting->setFloat("material.shininess", 32.0f);

	lighting->setVec3("light.ambient", vec3(0.2f, 0.2f, 0.2f));
	lighting->setVec3("light.diffuse", vec3(0.5f, 0.5f, 0.5f));
	lighting->setVec3("light.specular", vec3(1.0f, 1.0f, 1.0f));
	lighting->setVec3("light.position", camera->position);
	lighting->setVec3("light.direction", camera->front);
	lighting->setFloat("light.cutOff", glm::cos(glm::radians(18.5f)));
	lighting->setFloat("light.outerCutOff", glm::cos(glm::radians(20.5f)));

	lighting->setFloat("light.constant", 1.0f);
	lighting->setFloat("light.linear", 0.09f);
	lighting->setFloat("light.quadratic", 0.032f);

	lamp = new Shader("lamp");
	lamp->use();
	lamp->setVec3("color", lightColor);
	lamp->setMat4("model", model);
	lamp->setMat4("projection", projection);

	TextureLoader loader;

	GLuint diffuseMap = loader.load("res/container2.png", GL_RGBA);
	GLuint specularMap = loader.load("res/container2_specular.png", GL_RGBA);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseMap);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, specularMap);

	while(!glfwWindowShouldClose(window)) {
		render(window);
	}

	delete lighting;
	delete lamp;
	delete camera;
	delete cube;

	glfwTerminate();

	return 0;
}

void setup() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

	window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	glViewport(0, 0, 800, 600);
	glEnable(GL_DEPTH_TEST);
}

void render(GLFWwindow* window) {
	processInput(window);

	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//	lightPos.x += -0.5f * deltaTime;

	cube->bind();

	model = glm::mat4();
	model = glm::translate(model, lightPos);
	model = glm::scale(model, glm::vec3(0.2f));

	lamp->use();
	lamp->setMat4("model", model);
	lamp->setMat4("view", camera->getMatrix());
	cube->draw();

	glm::mat4 ml;
	ml = glm::translate(ml, glm::vec3(0, 0, 0));

	lighting->use();
	lighting->setVec3("light.position", camera->position);
	lighting->setVec3("light.direction", camera->front);
	lighting->setMat4("model", ml);
	lighting->setVec3("viewPos", camera->position);
	lighting->setMat4("view", camera->getMatrix());
//	cube->draw();

	for(unsigned int i = 0; i < 10; i++)
	{
	    glm::mat4 model;
	    model = glm::translate(model, cubePositions[i]);
	    float angle = 20.0f * i;
	    model = glm::rotate(model, glm::radians(angle) * (float)glfwGetTime() * 0.1f, glm::vec3(1.0f, 0.3f, 0.5f));
	    lighting->setMat4("model", model);

	    cube->draw();
	}

	glfwSwapBuffers(window);
	glfwPollEvents();
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if(firstMouse)
	{
	    lastX = xpos;
	    lastY = ypos;
	    firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	camera->yaw += xoffset;
	camera->pitch += yoffset;

	if(camera->pitch > 89.0f)
		camera->pitch =  89.0f;
	if(camera->pitch < -89.0f)
		camera->pitch = -89.0f;

	camera->update();
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
  if(fov >= 1.0f && fov <= 45.0f)
  	fov -= yoffset;
  if(fov <= 1.0f)
  	fov = 1.0f;
  if(fov >= 45.0f)
  	fov = 45.0f;
}

void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	float cameraSpeed = 2.5f * deltaTime; // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->position += cameraSpeed * camera->front;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->position -= cameraSpeed * camera->front;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->position -= glm::normalize(glm::cross(camera->front, camera->up)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->position += glm::normalize(glm::cross(camera->front, camera->up)) * cameraSpeed;
	camera->update();
}
