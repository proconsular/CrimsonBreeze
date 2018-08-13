/*
 * Camera.h
 *
 *  Created on: Aug 12, 2018
 *      Author: chrisluttio
 */

#ifndef CAMERA_CAMERA_H_
#define CAMERA_CAMERA_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

using namespace glm;

class Camera {
public:
	Camera();
	Camera(const vec3);

	mat4 getMatrix();

	void update();

	vec3 position, front, up, right, worldup;
	float yaw, pitch;
private:

};

#endif /* CAMERA_CAMERA_H_ */
