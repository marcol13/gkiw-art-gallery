#version 330

uniform sampler2D textureMap0; //zmienna reprezentująca jednostkę teksturującą
uniform vec3 viewPos; 

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

in vec2 iTexCoord0; //Zmienna do interpolacji współrzędnych teksturowania
in vec3 newNormal;
in vec3 FragPos;
in vec3 lightPos;

void main(void) {
	vec4 texColor=texture(textureMap0,iTexCoord0); //Pobranie koloru
	
	//ambient
	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * vec3(1.0, 1.0, 1.0);

	//diffuse
	vec3 norm = normalize(newNormal.xyz);
	vec3 lightDir = normalize(vec3(0.0, 5.0, 0.0) - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * vec3(1.0, 1.0, 1.0);

	//specular
	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * vec3(1.0, 1.0, 1.0);

	//pixelColor = vec4(viewPos, 1);
	pixelColor = vec4((ambient + diffuse + specular) * texColor.xyz, texColor.w);
	///pixelColor = vec4((diffuse) * texColor.xyz, texColor.w);
}