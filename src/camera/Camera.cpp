/*
 * Camera.cpp
 *
 *  Created on: Aug 12, 2018
 *      Author: chrisluttio
 */

#include "Camera.h"

Camera::Camera() {
	pitch = 0;
	yaw = -90.0f;
	worldup = vec3(0.0f, 1.0f, 0.0f);
	update();
}

Camera::Camera(const vec3 position) {
	this->position = position;
	pitch = 0;
	yaw = -90.0f;
	worldup = vec3(0.0f, 1.0f, 0.0f);
	update();
}

mat4 Camera::getMatrix() {
	return lookAt(position, position + front, up);
}

void Camera::update() {
	vec3 front;
	front.x = cos(radians(yaw)) * cos(radians(pitch));
	front.y = sin(radians(pitch));
	front.z = sin(radians(yaw)) * cos(radians(pitch));
	this->front = normalize(front);
	right = normalize(cross(this->front, worldup));
	up = normalize(cross(right, this->front));
}
