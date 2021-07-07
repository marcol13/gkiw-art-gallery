#include "textureprogram.h"

Textureprogram::Textureprogram()
{
	return;
}

Textureprogram::Textureprogram(const char* name)
{
	std::stringstream ss;

	ss << "Textures/" << name << "/" << name << "_Color.png";
	tex_color = readTexture(ss.str().c_str());
	ss.clear();
	/*ss << "Textures/" << name << "/" << name << "_Normal.png";
	tex_normal = readTexture(ss.str().c_str());
	ss.clear();
	ss << "Textures/" << name << "/" << name << "_Displacement.png";
	tex_displacement = readTexture(ss.str().c_str());
	ss.clear();
	ss << "Textures/" << name << "/" << name << "_Roughness.png";
	tex_roughness = readTexture(ss.str().c_str());
	ss.clear();*/
}

void Textureprogram::drawTextures(std::shared_ptr <ShaderProgram> shader)
{
	glUniform1i(shader->u("textureMap0"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex_color);

	/*glUniform1i(shader->u("textureMap1"), 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tex_normal);

	glUniform1i(shader->u("textureMap2"), 2);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, tex_displacement);

	glUniform1i(shader->u("textureMap3"), 3);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, tex_roughness);*/
}
