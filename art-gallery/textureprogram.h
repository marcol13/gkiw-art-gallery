#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <sstream>
#include "shaderprogram.h"
#include "readtexture.h"

class Textureprogram {
public:
	GLuint tex_color;
	GLuint tex_normal;
	GLuint tex_displacement;
	GLuint tex_roughness;

	Textureprogram();
	Textureprogram(const char*);
	void drawTextures(std::shared_ptr <ShaderProgram>);
};