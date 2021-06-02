#include "Camera.h"
#include "constants.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() :position(0, 0, -2.5f), center(0, 0, 0), noseVector(0, 1.0f, 0), mouse_angle(PI / 2, 0) {
	return;
}

Camera& Camera::instance()
{
	static Camera onlyInstance;

	return onlyInstance;
}

void Camera::rotate(float camera_x, float camera_y) {
	mouse_angle.x += camera_x;
	mouse_angle.y = glm::clamp(mouse_angle.y + camera_y, -PI / 2 + 0.5f, PI / 2 - 0.01f);

	return;
}

void Camera::move(float move_x, float move_y, float move_z) {
	position.x += move_z * cos(mouse_angle.x) + move_x * sin(mouse_angle.x);
	position.y += move_y;
	position.z += move_z * sin(mouse_angle.x) - move_x * cos(mouse_angle.x);

	return;
}

const glm::mat4& Camera::getMatrix() const
{
	glm::vec3 direction = glm::vec3(cos(mouse_angle.y) * cos(mouse_angle.x), sin(mouse_angle.y), sin(mouse_angle.x) * cos(mouse_angle.y));
	center = glm::normalize(direction);
	glm::vec3 right = glm::normalize(glm::cross(center, glm::vec3(0, 1.0f, 0)));
	noseVector = glm::normalize(glm::cross(right, center));
	V = glm::lookAt(position, position + center, noseVector);
	
	return V;
}

Camera::operator const glm::mat4& () const
{
	return getMatrix();
}

