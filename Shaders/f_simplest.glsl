#version 330

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
#define NR_POINT_LIGHTS 10

uniform sampler2D textureMap0; //zmienna reprezentująca jednostkę teksturującą
uniform vec3 viewPos; 
uniform PointLight pointLights[NR_POINT_LIGHTS];

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

in vec2 iTexCoord0; //Zmienna do interpolacji współrzędnych teksturowania
in vec3 newNormal;
in vec3 FragPos;


// function prototypes
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 tex);


void main(void) {
    vec3 tex = vec3(texture(textureMap0, iTexCoord0));
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 norm = normalize(newNormal.xyz);
    vec3 result = vec3(0);
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir, tex); 
    pixelColor = vec4(vec3(1.0) - exp(-result * 1.0f), 1.0);
    //vec3 hdr = vec3((1.0) - exp(-result * 0.3f));
    //pixelColor = vec4(pow(hdr, vec3(1.0 / 2.2)), 1.0f);
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 tex)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 128);
    // attenuation
    float dist = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));    
    // combine results
    vec3 ambient = light.ambient * tex;
    vec3 diffuse = light.diffuse * diff * tex;
    vec3 specular = light.specular * spec * tex;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return 4*(ambient + diffuse + specular);
}
