#include "Model.h"


Model::Model(const char* file_name, const char* tex_name, const char* shader_name)
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
	shader_model.reset(new ShaderProgram(shader_name, NULL, shader_name));
	tex = Textureprogram(tex_name);
	//this->tex = tex;
}

void Model::draw()
{
	shader_model->use();
	glUniformMatrix4fv(shader_model->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(shader_model->u("V"), 1, false, glm::value_ptr(Camera::instance().getMatrix()));
	glUniformMatrix4fv(shader_model->u("M"), 1, false, glm::value_ptr(M));

	glEnableVertexAttribArray(shader_model->a("vertex"));  //W��cz przesy�anie danych do atrybutu vertex
	glVertexAttribPointer(shader_model->a("vertex"), 4, GL_FLOAT, false, 0, vertices.get()); //Wska� tablic� z danymi dla atrybutu vertex

	glEnableVertexAttribArray(shader_model->a("color"));  //W��cz przesy�anie danych do atrybutu color
	glVertexAttribPointer(shader_model->a("color"), 4, GL_FLOAT, false, 0, colors.get()); //Wska� tablic� z danymi dla atrybutu color

	glEnableVertexAttribArray(shader_model->a("normal"));  //W��cz przesy�anie danych do atrybutu normal
	glVertexAttribPointer(shader_model->a("normal"), 4, GL_FLOAT, false, 0, vertex_normals.get()); //Wska� tablic� z danymi dla atrybutu normal

	glEnableVertexAttribArray(shader_model->a("texCoord0"));  //W��cz przesy�anie danych do atrybutu texCoord
	glVertexAttribPointer(shader_model->a("texCoord0"), 2, GL_FLOAT, false, 0, textures.get()); //Wska� tablic� z danymi dla atrybutu texCoord

	tex.drawTextures(shader_model);

	glDrawArrays(GL_TRIANGLES, 0, vertexCount); //Narysuj obiekt

	glDisableVertexAttribArray(shader_model->a("vertex"));  //Wy��cz przesy�anie danych do atrybutu vertex
	glDisableVertexAttribArray(shader_model->a("color"));  //Wy��cz przesy�anie danych do atrybutu color
	glDisableVertexAttribArray(shader_model->a("normal"));  //Wy��cz przesy�anie danych do atrybutu normal
	glDisableVertexAttribArray(shader_model->a("texCoord0"));  //Wy��cz przesy�anie danych do atrybutu texCoord0

	return;
}

void Model::rotate(float angle, glm::vec3 vec)
{
	M = glm::rotate(M, angle, vec);

	return;
}

void Model::scale(glm::vec3 vec)
{
	M = glm::scale(M, vec);

	return;
}

void Model::translate(glm::vec3 vec) 
{
	M = glm::translate(M, vec);

	return;
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

