#pragma once
#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

#include "objloader.h"
#include "shaderprogram.h"
#include "constants.h"
#include "Camera.h"
#include "textureprogram.h"

class Model
{
private:
	void unpack4(std::shared_ptr <float>p, glm::vec3 v, int i, float value = 1.0f);
	void unpack2(std::shared_ptr <float>p, glm::vec2 v, int i);

protected:
	glm::mat4 M = glm::mat4(1.0f);
	//GLuint tex;

public:
	mutable glm::vec3 pointLightPositions[4] = {
	   glm::vec3(35.0f, 15.0f, -10.0f),
	   glm::vec3(-7.0f, 5.0f, 8.0f),
	   glm::vec3(-5.0f,  5.0f, 30.0f),
	   glm::vec3(-10.0f,  7.0f, 60.0f)
	};
	std::shared_ptr <float> vertices;
	std::shared_ptr <float> normals;
	std::shared_ptr <float> vertex_normals;
	std::shared_ptr <float> textures;
	std::shared_ptr <float> colors;
	Textureprogram tex;
	unsigned int vertexCount;
	std::shared_ptr <ShaderProgram> shader_model;

	Model(const char* file_name, const char* tex_name, const char* shader_name);
	void draw();
	void rotate(float, glm::vec3);
	void scale(glm::vec3);
	void translate(glm::vec3);
};

