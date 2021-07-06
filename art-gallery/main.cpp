#define GLM_FORCE_RADIANS
#define GLM_FORCE_SWIZZLE

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Camera.h"
#include "constants.h"
#include "lodepng.h"
#include "shaderprogram.h"
#include "Model.h"

float temp_x = 0;
float temp_y = 0;
float temp_z = 0;
float pos_x = 0;
float pos_y = 0;
float pos_z = -2.5;

float cursor_x = 0;
float cursor_y = 0;

double prev_mouse_x = double(window_width) / 2;
double prev_mouse_y = double(window_height) / 2;
//double prev_mouse_x = 0;
//double prev_mouse_y = 0;

float rotate_x = 0;
float rotate_y = 0;

glm::vec2 mAngle(PI / 2, 0);

glm::vec3 pos_observer = glm::vec3(pos_x, pos_y, pos_z);
glm::vec3 pos_center = glm::vec3(0, 0, 0);
glm::vec3 pos_noseVector = glm::vec3(0.0f, 1.0f, 0.0f);

float delta_time = 0.0f;
float aspectRatio = 1;

ShaderProgram* sp;
Model* EddieHall;
Model* HallThor;
Model* Dome1;
Model* Dome2;
Model* venus;
Model* swiatlo;


//Odkomentuj, żeby rysować czajnik
//float* vertices = myCorridor2Vertices;
//float* normals = myCorridor2VertexNormals;
//float* texCoords = myCorridor2TexCoords;
//float* colors = myCorridor2Colors;
//int vertexCount = myCorridor2VertexCount;



GLuint tex0;
GLuint tex1;

//Procedura obsługi błędów
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	cursor_x = mouse_sensitivity * (xpos - prev_mouse_x);
	cursor_y = mouse_sensitivity * (prev_mouse_y - ypos);
	prev_mouse_x = xpos;
	prev_mouse_y = ypos;

	return;
}


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_A)
			temp_x += 2;
		if (key == GLFW_KEY_D)
			temp_x -= 2;
		if (key == GLFW_KEY_W)
			temp_z += 2;
		if (key == GLFW_KEY_S)
			temp_z -= 2;
		if (key == GLFW_KEY_ESCAPE)
			exit(0);
	}
	if (action == GLFW_RELEASE) {
		if (key == GLFW_KEY_A || key == GLFW_KEY_D)
			temp_x = 0;
		if (key == GLFW_KEY_W || key == GLFW_KEY_S)
			temp_z = 0;
	}
}

void windowResizeCallback(GLFWwindow* window, int width, int height) {
	if (height == 0) return;
	aspectRatio = (float)width / (float)height;
	glViewport(0, 0, width, height);
}





//Procedura inicjująca
void initOpenGLProgram(GLFWwindow* window) {
	//************Tutaj umieszczaj kod, który należy wykonać raz, na początku programu************
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	glfwSetWindowSizeCallback(window, windowResizeCallback);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPos(window, prev_mouse_x, prev_mouse_y);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);


	aspectRatio = 1920.0f / 1080.0f;

	EddieHall = new Model("EddieHall", "painted_plaster_017", "simplest");
	HallThor = new Model("HallThor", "painted_plaster_017", "simplest");
	Dome1 = new Model("Dome1", "painted_plaster_017", "simplest");
	Dome2 = new Model("Dome2", "painted_plaster_017", "simplest");
	venus = new Model("Venus", "bricks066", "simplest");
	venus->translate(glm::vec3(0, 0, 0));
	
	swiatlo = new Model("LightsourceCube", "bricks066", "lightsource");
	swiatlo->translate(glm::vec3(-5, 5, 25));
}


//Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram(GLFWwindow* window) {
	//************Tutaj umieszczaj kod, który należy wykonać po zakończeniu pętli głównej************

	delete sp;
}


void walk() {

}


//Procedura rysująca zawartość sceny
void drawScene(GLFWwindow* window) {
	//************Tutaj umieszczaj kod rysujący obraz******************l
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	EddieHall->draw();
	HallThor->draw();
	Dome1->draw();
	Dome2->draw();
	//venus->draw();
	swiatlo->draw();


	glfwSwapBuffers(window); //Przerzuć tylny bufor na przedni
}


int main(void)
{
	GLFWwindow* window; //Wskaźnik na obiekt reprezentujący okno

	glfwSetErrorCallback(error_callback);//Zarejestruj procedurę obsługi błędów

	if (!glfwInit()) { //Zainicjuj bibliotekę GLFW
		fprintf(stderr, "Nie można zainicjować GLFW.\n");
		exit(EXIT_FAILURE);
	}

	//***********************************
	// 	  widok pełnoekranowy / w oknie
	//***********************************
	//window = glfwCreateWindow(window_width, window_height, "Art gallery", glfwGetPrimaryMonitor(), NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.
	window = glfwCreateWindow(window_width, window_height, "Art gallery", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

	if (!window) //Jeżeli okna nie udało się utworzyć, to zamknij program
	{
		fprintf(stderr, "Nie można utworzyć okna.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje się aktywny i polecenia OpenGL będą dotyczyć właśnie jego.
	glfwSwapInterval(1); //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora

	if (glewInit() != GLEW_OK) { //Zainicjuj bibliotekę GLEW
		fprintf(stderr, "Nie można zainicjować GLEW.\n");
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window); //Operacje inicjujące

	//Główna pętla
	glfwSetTime(0); //Zeruj timer
	while (!glfwWindowShouldClose(window)) //Tak długo jak okno nie powinno zostać zamknięte
	{

		delta_time = glfwGetTime();

		Camera::instance().move(temp_x * delta_time, temp_y * delta_time, temp_z * delta_time);
		Camera::instance().rotate(cursor_x * delta_time, cursor_y * delta_time);


		cursor_x = 0;
		cursor_y = 0;

		glfwSetTime(0); //Zeruj timer - na razie nie potrzebny, później się wykorzysta
		drawScene(window); //Wykonaj procedurę rysującą
		glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
	exit(EXIT_SUCCESS);
}