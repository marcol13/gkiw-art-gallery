#version 330

uniform sampler2D textureMap0; //zmienna reprezentująca jednostkę teksturującą

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

in vec2 iTexCoord0; //Zmienna do interpolacji współrzędnych teksturowania
in vec3 newNormal;
in vec3 FragPos;

void main(void) {
	vec4 texColor=texture(textureMap0,iTexCoord0); //Pobranie koloru
	
	//ambient
	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * vec3(1.0, 1.0, 1.0);

	//diffuse
	vec3 norm = normalize(newNormal.xyz);
	vec3 lightDir = normalize(vec3(-5.0, 5.0, 25.0) - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * vec3(1.0, 1.0, 1.0);


	pixelColor = vec4((ambient + diffuse) * texColor.xyz, texColor.w);
	//pixelColor = vec4((diffuse) * texColor.xyz, texColor.w);
}