#pragma once
#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "objloader.h"

class Model
{
private:
	void unpack4(std::shared_ptr <float>p, glm::vec3 v, int i, float value = 1.0f);
	void unpack2(std::shared_ptr <float>p, glm::vec2 v, int i);

public:
	std::shared_ptr <float> vertices;
	std::shared_ptr <float> normals;
	std::shared_ptr <float> vertex_normals;
	std::shared_ptr <float> textures;
	std::shared_ptr <float> colors;
	unsigned int vertexCount;

	Model(const char* file_name);
	//void rotate(float angle, glm::vec3);

};

