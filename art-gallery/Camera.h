#pragma once
#include <glm/glm.hpp>

class Camera {
private:
	mutable glm::mat4 V;
	mutable glm::vec3 position;
	mutable glm::vec3 center;
	mutable glm::vec3 noseVector;
	glm::vec2 mouse_angle;
	bool isMoving;

	Camera();
public:
	static Camera& instance();

	void initPosition();
	void initCenter();
	void rotate(float, float);
	void move(float, float, float);

	const glm::mat4& getMatrix() const;
	operator const glm::mat4& () const;
};
