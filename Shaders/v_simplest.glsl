#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

//Atrybuty
in vec4 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
in vec4 color; //kolor związany z wierzchołkiem
in vec2 texCoord0; //Atrybut do przekazania współrzędnych teksturowania


//Zmienne interpolowane
out vec2 iTexCoord0; //Zmienna do interpolacji współrzędnych teksturowania

void main(void) {
    iTexCoord0=texCoord0; //Przepisanie danych z atrybutu do zmiennej interpolowanej
    
    gl_Position=P*V*M*vertex;
}