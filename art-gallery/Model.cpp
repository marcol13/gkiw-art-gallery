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

	glEnableVertexAttribArray(shader_model->a("vertex"));  //W³¹cz przesy³anie danych do atrybutu vertex
	glVertexAttribPointer(shader_model->a("vertex"), 4, GL_FLOAT, false, 0, vertices.get()); //Wska¿ tablicê z danymi dla atrybutu vertex

	glEnableVertexAttribArray(shader_model->a("color"));  //W³¹cz przesy³anie danych do atrybutu color
	glVertexAttribPointer(shader_model->a("color"), 4, GL_FLOAT, false, 0, colors.get()); //Wska¿ tablicê z danymi dla atrybutu color

	glEnableVertexAttribArray(shader_model->a("normal"));  //W³¹cz przesy³anie danych do atrybutu normal
	glVertexAttribPointer(shader_model->a("normal"), 4, GL_FLOAT, false, 0,	normals.get()); //Wska¿ tablicê z danymi dla atrybutu normal

	glEnableVertexAttribArray(shader_model->a("texCoord0"));  //W³¹cz przesy³anie danych do atrybutu texCoord
	glVertexAttribPointer(shader_model->a("texCoord0"), 2, GL_FLOAT, false, 0, textures.get()); //Wska¿ tablicê z danymi dla atrybutu texCoord

	glUniform3fv(shader_model->u("viewPos"), 1, glm::value_ptr(Camera::instance().position));
	
	// Dome 1
	glUniform3fv(shader_model->u("pointLights[0].position"), 1, glm::value_ptr(pointLightPositions[0]));
	glUniform3fv(shader_model->u("pointLights[0].ambient"), 1, glm::value_ptr(glm::vec3(0.8f, 0.8f, 0.8f)));
	glUniform3fv(shader_model->u("pointLights[0].diffuse"), 1, glm::value_ptr(glm::vec3(0.8f, 0.8f, 0.8f)));
	glUniform3fv(shader_model->u("pointLights[0].specular"), 1, glm::value_ptr(glm::vec3(0.8f, 0.8f, 0.8f)));
	glUniform1f(shader_model->u("pointLights[0].constant"), 1.0f);
	glUniform1f(shader_model->u("pointLights[0].linear"), 0.09f);
	glUniform1f(shader_model->u("pointLights[0].quadratic"), 0.032f);
	//Thor 1
	glUniform3fv(shader_model->u("pointLights[1].position"), 1, glm::value_ptr(pointLightPositions[1]));
	glUniform3fv(shader_model->u("pointLights[1].ambient"), 1, glm::value_ptr(glm::vec3(0.6f, 0.6f, 0.6f)));
	glUniform3fv(shader_model->u("pointLights[1].diffuse"), 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
	glUniform3fv(shader_model->u("pointLights[1].specular"), 1, glm::value_ptr(glm::vec3(0.7f, 0.7f, 0.7f)));
	glUniform1f(shader_model->u("pointLights[1].constant"), 1.0f);
	glUniform1f(shader_model->u("pointLights[1].linear"), 0.09f);
	glUniform1f(shader_model->u("pointLights[1].quadratic"), 0.032f);
	//Thor 2
	glUniform3fv(shader_model->u("pointLights[2].position"), 1, glm::value_ptr(pointLightPositions[2]));
	glUniform3fv(shader_model->u("pointLights[2].ambient"), 1, glm::value_ptr(glm::vec3(0.6f, 0.6f, 0.6f)));
	glUniform3fv(shader_model->u("pointLights[2].diffuse"), 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
	glUniform3fv(shader_model->u("pointLights[2].specular"), 1, glm::value_ptr(glm::vec3(0.7f, 0.7f, 0.7f)));
	glUniform1f(shader_model->u("pointLights[2].constant"), 1.0f);
	glUniform1f(shader_model->u("pointLights[2].linear"), 0.09f);
	glUniform1f(shader_model->u("pointLights[2].quadratic"), 0.032f);
	//Thor 3
	glUniform3fv(shader_model->u("pointLights[3].position"), 1, glm::value_ptr(pointLightPositions[3]));
	glUniform3fv(shader_model->u("pointLights[3].ambient"), 1, glm::value_ptr(glm::vec3(0.6f, 0.6f, 0.6f)));
	glUniform3fv(shader_model->u("pointLights[3].diffuse"), 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
	glUniform3fv(shader_model->u("pointLights[3].specular"), 1, glm::value_ptr(glm::vec3(0.7f, 0.7f, 0.7f)));
	glUniform1f(shader_model->u("pointLights[3].constant"), 1.0f);
	glUniform1f(shader_model->u("pointLights[3].linear"), 0.09f);
	glUniform1f(shader_model->u("pointLights[3].quadratic"), 0.032f);
	//Thor 4
	glUniform3fv(shader_model->u("pointLights[4].position"), 1, glm::value_ptr(pointLightPositions[4]));
	glUniform3fv(shader_model->u("pointLights[4].ambient"), 1, glm::value_ptr(glm::vec3(0.6f, 0.6f, 0.6f)));
	glUniform3fv(shader_model->u("pointLights[4].diffuse"), 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
	glUniform3fv(shader_model->u("pointLights[4].specular"), 1, glm::value_ptr(glm::vec3(0.7f, 0.7f, 0.7f)));
	glUniform1f(shader_model->u("pointLights[4].constant"), 1.0f);
	glUniform1f(shader_model->u("pointLights[4].linear"), 0.09f);
	glUniform1f(shader_model->u("pointLights[4].quadratic"), 0.032f);
	//Eddie 1
	glUniform3fv(shader_model->u("pointLights[5].position"), 1, glm::value_ptr(pointLightPositions[5]));
	glUniform3fv(shader_model->u("pointLights[5].ambient"), 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
	glUniform3fv(shader_model->u("pointLights[5].diffuse"), 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
	glUniform3fv(shader_model->u("pointLights[5].specular"), 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
	glUniform1f(shader_model->u("pointLights[5].constant"), 1.0f);
	glUniform1f(shader_model->u("pointLights[5].linear"), 0.0009f);
	glUniform1f(shader_model->u("pointLights[5].quadratic"), 0.032f);
	//Eddie 2
	glUniform3fv(shader_model->u("pointLights[6].position"), 1, glm::value_ptr(pointLightPositions[6]));
	glUniform3fv(shader_model->u("pointLights[6].ambient"), 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
	glUniform3fv(shader_model->u("pointLights[6].diffuse"), 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
	glUniform3fv(shader_model->u("pointLights[6].specular"), 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
	glUniform1f(shader_model->u("pointLights[6].constant"), 1.0f);
	glUniform1f(shader_model->u("pointLights[6].linear"), 0.0009f);
	glUniform1f(shader_model->u("pointLights[6].quadratic"), 0.032f);
	//Eddie 3
	glUniform3fv(shader_model->u("pointLights[7].position"), 1, glm::value_ptr(pointLightPositions[7]));
	glUniform3fv(shader_model->u("pointLights[7].ambient"), 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
	glUniform3fv(shader_model->u("pointLights[7].diffuse"), 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
	glUniform3fv(shader_model->u("pointLights[7].specular"), 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
	glUniform1f(shader_model->u("pointLights[7].constant"), 1.0f);
	glUniform1f(shader_model->u("pointLights[7].linear"), 0.0009f);
	glUniform1f(shader_model->u("pointLights[7].quadratic"), 0.032f);
	//Eddie 4
	glUniform3fv(shader_model->u("pointLights[8].position"), 1, glm::value_ptr(pointLightPositions[8]));
	glUniform3fv(shader_model->u("pointLights[8].ambient"), 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
	glUniform3fv(shader_model->u("pointLights[8].diffuse"), 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
	glUniform3fv(shader_model->u("pointLights[8].specular"), 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
	glUniform1f(shader_model->u("pointLights[8].constant"), 1.0f);
	glUniform1f(shader_model->u("pointLights[8].linear"), 0.0009f);
	glUniform1f(shader_model->u("pointLights[8].quadratic"), 0.032f);	
	
	// Dome 2
	glUniform3fv(shader_model->u("pointLights[9].position"), 1, glm::value_ptr(pointLightPositions[9]));
	glUniform3fv(shader_model->u("pointLights[9].ambient"), 1, glm::value_ptr(glm::vec3(1.2f, 1.2f, 1.2f)));
	glUniform3fv(shader_model->u("pointLights[9].diffuse"), 1, glm::value_ptr(glm::vec3(1.2f, 1.2f, 1.2f)));
	glUniform3fv(shader_model->u("pointLights[9].specular"), 1, glm::value_ptr(glm::vec3(1.2f, 1.2f, 1.2f)));
	glUniform1f(shader_model->u("pointLights[9].constant"), 1.0f);
	glUniform1f(shader_model->u("pointLights[9].linear"), 0.09f);
	glUniform1f(shader_model->u("pointLights[9].quadratic"), 0.032f);

	tex.drawTextures(shader_model);

	glDrawArrays(GL_TRIANGLES, 0, vertexCount); //Narysuj obiekt
	


	glDisableVertexAttribArray(shader_model->a("vertex"));  //Wy³¹cz przesy³anie danych do atrybutu vertex
	glDisableVertexAttribArray(shader_model->a("color"));  //Wy³¹cz przesy³anie danych do atrybutu color
	glDisableVertexAttribArray(shader_model->a("normal"));  //Wy³¹cz przesy³anie danych do atrybutu normal
	glDisableVertexAttribArray(shader_model->a("texCoord0"));  //Wy³¹cz przesy³anie danych do atrybutu texCoord0

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

