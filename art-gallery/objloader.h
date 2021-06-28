#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>
#include<algorithm>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>

#include"Vertex.h"

static std::string extract(std::string &buf, std::string separator = " ")
{
	size_t spacePos = buf.find(separator);
	std::string result = buf.substr(0, spacePos);
	buf = buf.substr(spacePos + 1);

	if (result == "")
	{
		result = "0";
	}

	return result;
}

static float getFloat(std::string &buf)
{
	size_t spacePos = buf.find(' ');
	std::string position = buf.substr(0, spacePos);
	buf = buf.substr(spacePos + 1);

	return std::stof(position);
}

static void loadVector(std::vector<glm::vec3>& container, std::string &buf)
{
	container.push_back(glm::vec3());

	container.back().x = getFloat(buf);
	container.back().y = getFloat(buf);
	container.back().z = getFloat(buf);

	return;
}

static void loadVector(std::vector<glm::vec2>& container, std::string &buf)
{
	container.push_back(glm::vec2());

	container.back().x = getFloat(buf);
	container.back().y = getFloat(buf);

	return;
}

static std::vector<Vertex> loadOBJ(std::string file_name) {
	std::ifstream file("Models/" + file_name + ".obj");
	std::string buf;
	std::vector <glm::vec3> position;
	std::vector <glm::vec3> normal;
	std::vector <glm::vec2> texcoords;
	std::vector <int> facesVertices;
	std::vector <int> facesTextures;
	std::vector <int> facesNormals;

	while (file.good())
	{
		std::getline(file, buf);

		std::string lineType = extract(buf);

		if (lineType == "v")
		{
			loadVector(position, buf);
		}
		if (lineType == "vt")
		{
			loadVector(texcoords, buf);
		}
		if (lineType == "vn")
		{
			loadVector(normal, buf);
		}
		if (lineType == "f")
		{
			for (size_t i = 0; i < 3; i++)
			{
				facesVertices.push_back(std::stoi(extract(buf, "/")) - 1);
				facesTextures.push_back(std::stoi(extract(buf, "/")) - 1);
				facesNormals.push_back(std::stoi(extract(buf)) - 1);
			}
		}
	}
	std::vector<Vertex> vertices;
	vertices.reserve(facesVertices.size());

	for (size_t i = 0; i < facesVertices.size(); i++)
	{
		Vertex temp;
		temp.position = position[facesVertices[i]];

		if (normal.size() > 0)
		{
			temp.normal = normal[facesNormals[i]];
		}

		if (texcoords.size() > 0)
		{
			temp.texcoord = texcoords[facesTextures[i]];
		}
		vertices.push_back(temp);
	}
	return vertices;
}