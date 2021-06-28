#version 330

uniform sampler2D textureMap0; //zmienna reprezentująca jednostkę teksturującą

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

in vec2 iTexCoord0; //Zmienna do interpolacji współrzędnych teksturowania
in vec4 ic; 

void main(void) {
	vec4 texColor=texture(textureMap0,iTexCoord0); //Pobranie koloru

	pixelColor = ic;
}