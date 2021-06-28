#include "Model.h"

Model::Model(const char* file_name)
{
	std::vector<Vertex> temp_vertices = loadOBJ(file_name);
	vertexCount = temp_vertices.size();
	vertices.reset(new float[vertexCount*4]);
	normals.reset(new float[vertexCount*4]);
	vertex_normals.reset(new float[vertexCount*4]);
	textures.reset(new float[vertexCount*2]);
	colors.reset(new float[vertexCount*4]);
	for (int i = 0, j = 0; i < temp_vertices.size(); ++i, j+=4) {
		if (i == temp_vertices.size() - 1) {
			unpack4(vertices, temp_vertices[i].position, i);
			unpack4(normals, temp_vertices[i].normal, i, 0.0f);
			unpack4(vertex_normals, temp_vertices[i].position, i, 0.0f);
			unpack4(colors, glm::vec3(1,1,1), i);
			unpack2(textures, temp_vertices[i].texcoord, i);
		}
		else {
			unpack4(vertices, temp_vertices[i].position, i);
			unpack4(normals, temp_vertices[i].normal, i, 0.0f);
			unpack4(vertex_normals, temp_vertices[i].position, i, 0.0f);
			unpack4(colors, glm::vec3(1, 1, 1), i);
			unpack2(textures, temp_vertices[i].texcoord, i);
		}
	}
}

void Model::unpack4(std::shared_ptr <float>p, glm::vec3 v, int i, float value) {
	p.get()[i * 4 + 0] = v[0];
	p.get()[i * 4 + 1] = v[1];
	p.get()[i * 4 + 2] = v[2];
	p.get()[i * 4 + 3] = value;

	return;
}

void Model::unpack2(std::shared_ptr <float>p, glm::vec2 v, int i) {
	p.get()[i * 2 + 0] = v[0];
	p.get()[i * 2 + 1] = v[1];

	return;
}

