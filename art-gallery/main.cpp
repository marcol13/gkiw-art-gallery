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
Model* pedestal_venus;
Model* pedestal_venus2;
Model* pedestal_nature1;
Model* pedestal_nature2;
Model* pedestal_nature3;
Model* pedestal_nature4;
Model* big_frame1;
Model* floor1;
Model* column1;
Model* column2;

Model* frame1_v1;
Model* frame2_v1;
Model* frame3_v1;
Model* frame4_v1;
Model* frame5_v1;
Model* frame6_v1;
Model* frame7_v1;
Model* frame8_v1;
Model* frame9_v1;
Model* frame10_v1;

Model* frame1_v2;
Model* frame2_v2;

Model* canvas1_stanczyk;
Model* canvas2_karabin;
Model* canvas3_wenus;
Model* canvas4_bacchus;

//LIGHTING
//glm::vec3 lightPos = glm::vec3(0.0, 5.0, 0.0);


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
			temp_x += 10;
		if (key == GLFW_KEY_D)
			temp_x -= 10;
		if (key == GLFW_KEY_W)
			temp_z += 10;
		if (key == GLFW_KEY_S)
			temp_z -= 10;
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

	venus = new Model("Venus", "Venus", "simplest");
	venus->translate(glm::vec3(-8, 3.2, -9));
	venus->scale(glm::vec3(1.7, 1.7, 1.7));

	pedestal_venus = new Model("Pedestal2", "Marble019", "simplest");
	pedestal_venus->scale(glm::vec3(0.3, 0.25, 0.3));
	pedestal_venus->translate(glm::vec3(-26, 6.85, -30));

	pedestal_venus2 = new Model("Pedestal2", "Marble019", "simplest");
	pedestal_venus2->scale(glm::vec3(0.3, 0.25, 0.3));
	pedestal_venus2->translate(glm::vec3(-26, 6.85, 240));

	pedestal_nature1 = new Model("Pedestal3", "Marble019", "simplest");
	pedestal_nature1->translate(glm::vec3(3, 1.65, 3));
	pedestal_nature1->scale(glm::vec3(2.5, 2.5, 2.5));
	pedestal_nature1->rotate(90.0f * PI / 180.0f, glm::vec3(1, 0, 0));
	pedestal_nature1->rotate(45.0f * PI / 180.0f, glm::vec3(0, 0, 1));

	pedestal_nature2 = new Model("Pedestal3", "Marble019", "simplest");
	pedestal_nature2->translate(glm::vec3(3, 1.65, -19));
	pedestal_nature2->scale(glm::vec3(2.5, 2.5, 2.5));
	pedestal_nature2->rotate(90.0f * PI / 180.0f, glm::vec3(1, 0, 0));
	pedestal_nature2->rotate(45.0f * PI / 180.0f, glm::vec3(0, 0, 1));

	pedestal_nature3 = new Model("Pedestal3", "Marble019", "simplest");
	pedestal_nature3->translate(glm::vec3(-18, 1.65, 3));
	pedestal_nature3->scale(glm::vec3(2.5, 2.5, 2.5));
	pedestal_nature3->rotate(90.0f * PI / 180.0f, glm::vec3(1, 0, 0));
	pedestal_nature3->rotate(45.0f * PI / 180.0f, glm::vec3(0, 0, 1));

	pedestal_nature4 = new Model("Pedestal3", "Marble019", "simplest");
	pedestal_nature4->translate(glm::vec3(-18, 1.65, -19));
	pedestal_nature4->scale(glm::vec3(2.5, 2.5, 2.5));
	pedestal_nature4->rotate(90.0f * PI / 180.0f, glm::vec3(1, 0, 0));
	pedestal_nature4->rotate(45.0f * PI / 180.0f, glm::vec3(0, 0, 1));

	big_frame1 = new Model("BigFrame", "Metal007", "simplest");
	big_frame1->rotate(90.0f * PI / 180.0f, glm::vec3(1, 0, 0));
	big_frame1->rotate(90.0f * PI / 180.0f, glm::vec3(0, 1, 0));
	big_frame1->rotate(90.0f * PI / 180.0f, glm::vec3(1, 0, 0));
	big_frame1->scale(glm::vec3(13,13,17));
	//big_frame1->scale(glm::vec3(10, 1, 1));
	//big_frame1->translate(glm::vec3(1.5, 1.65, 0.65));
	big_frame1->translate(glm::vec3(1.35, 3.97, 0.5));

	floor1 = new Model("Floor", "Tiles074", "simplest");
	floor1->translate(glm::vec3(0, -1, 0));
	floor1->scale(glm::vec3(100, 100, 100));

	column1 = new Model("Column2", "DoricColumn", "simplest");
	column1->scale(glm::vec3(0.7, 0.73, 0.7));
	column1->translate(glm::vec3(70, -0.6, 20));

	column2 = new Model("Column2", "DoricColumn", "simplest");
	column2->scale(glm::vec3(0.7, 0.73, 0.7));
	column2->translate(glm::vec3(70, -0.6, -45));
	
	frame1_v1 = new Model("Frame2", "Planks011", "simplest");
	frame1_v1->scale(glm::vec3(0.5, 0.5, 0.5));
	frame1_v1->rotate(90.0f * PI / 180.0f, glm::vec3(0, 1, 0));
	//frame1_v1->translate(glm::vec3(-54, 20, 65));
	frame1_v1->translate(glm::vec3(-53.9, 25, 80));

	frame2_v1 = new Model("Frame2", "Planks011", "simplest");
	frame2_v1->scale(glm::vec3(0.5, 0.5, 0.5));
	frame2_v1->rotate(90.0f * PI / 180.0f, glm::vec3(0, 1, 0));
	frame2_v1->translate(glm::vec3(87.8, 25, 80));

	frame3_v1 = new Model("Frame2", "Planks011", "simplest");
	frame3_v1->scale(glm::vec3(0.5, 0.5, 0.5));
	frame3_v1->rotate(90.0f * PI / 180.0f, glm::vec3(0, 1, 0));
	frame3_v1->translate(glm::vec3(-53.9, 25, 50));

	frame4_v1 = new Model("Frame2", "Planks011", "simplest");
	frame4_v1->scale(glm::vec3(0.5, 0.5, 0.5));
	frame4_v1->rotate(90.0f * PI / 180.0f, glm::vec3(0, 1, 0));
	frame4_v1->translate(glm::vec3(87.8, 25, 50));

	frame5_v1 = new Model("Frame2", "Planks011", "simplest");
	frame5_v1->scale(glm::vec3(0.5, 0.5, 0.5));
	frame5_v1->translate(glm::vec3(-4.45,15,38));

	frame6_v1 = new Model("Frame2", "Planks011", "simplest");
	frame6_v1->scale(glm::vec3(0.5, 0.5, 0.5));
	frame6_v1->translate(glm::vec3(-26.15, 15, 38));

	frame7_v1 = new Model("Frame2", "Planks011", "simplest");
	frame7_v1->scale(glm::vec3(0.5, 0.5, 0.5));
	frame7_v1->translate(glm::vec3(-4.45, 15, 63));

	frame8_v1 = new Model("Frame2", "Planks011", "simplest");
	frame8_v1->scale(glm::vec3(0.5, 0.5, 0.5));
	frame8_v1->translate(glm::vec3(-26.15, 15, 63));

	frame9_v1 = new Model("Frame2", "Planks011", "simplest");
	frame9_v1->scale(glm::vec3(0.5, 0.5, 0.5));
	frame9_v1->translate(glm::vec3(-4.45, 15, 88));

	frame10_v1 = new Model("Frame2", "Planks011", "simplest");
	frame10_v1->scale(glm::vec3(0.5, 0.5, 0.5));
	frame10_v1->translate(glm::vec3(-26.15, 15, 88));


	frame1_v2 = new Model("Frame2", "Planks011", "simplest");
	frame1_v2->scale(glm::vec3(0.5, 0.5, 0.5));
	frame1_v2->rotate(90.0f * PI / 180.0f, glm::vec3(1, 0, 0));
	frame1_v2->translate(glm::vec3(-47,-14,-13));

	frame2_v2 = new Model("Frame2", "Planks011", "simplest");
	frame2_v2->scale(glm::vec3(0.5, 0.5, 0.5));
	frame2_v2->rotate(90.0f * PI / 180.0f, glm::vec3(1, 0, 0));
	frame2_v2->rotate(90.0f * PI / 180.0f, glm::vec3(0, 0, 1));
	frame2_v2->translate(glm::vec3(-48.5,21,-13));
	

	canvas1_stanczyk = new Model("Stanczyk", "Stanczyk", "simplest");
	canvas1_stanczyk->rotate(90.0f * PI / 180.0f, glm::vec3(-1, 0, 0));
	canvas1_stanczyk->translate(glm::vec3(41.225, -26.7, 10));
	canvas1_stanczyk->scale(glm::vec3(2.55,2.5,2.5));

	canvas2_karabin = new Model("Stanczyk", "Karabin", "simplest");
	canvas2_karabin->rotate(90.0f * PI / 180.0f, glm::vec3(-1, 0, 0));
	canvas2_karabin->translate(glm::vec3(26.18, -26.7, 10));
	canvas2_karabin->scale(glm::vec3(2.55, 2.5, 2.5));

	canvas3_wenus = new Model("Stanczyk", "NarodzinyWenus", "simplest");
	canvas3_wenus->rotate(90.0f * PI / 180.0f, glm::vec3(-1, 0, 0));
	canvas3_wenus->translate(glm::vec3(26.18, 44.18, 10));
	canvas3_wenus->scale(glm::vec3(2.55, 2.5, 2.5));
	
	canvas4_bacchus = new Model("Stanczyk", "Bacchus", "simplest");
	canvas4_bacchus->rotate(90.0f * PI / 180.0f, glm::vec3(-1, 0, 0));
	canvas4_bacchus->translate(glm::vec3(41.225, 44.18, 10));
	canvas4_bacchus->scale(glm::vec3(2.55, 2.5, 2.5));

	swiatlo = new Model("LightsourceCube", "bricks066", "lightsource");
	swiatlo->translate(glm::vec3(0.0, 5.0, 0.0));
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
	venus->draw();
	pedestal_venus->draw();
	pedestal_venus2->draw();
	pedestal_nature1->draw();
	pedestal_nature2->draw();
	pedestal_nature3->draw();
	pedestal_nature4->draw();
	big_frame1->draw();
	floor1->draw();
	column1->draw();
	column2->draw();

	frame1_v1->draw();
	frame2_v1->draw();
	frame3_v1->draw();
	frame4_v1->draw();
	frame5_v1->draw();
	frame6_v1->draw();
	frame7_v1->draw();
	frame8_v1->draw();
	frame9_v1->draw();
	frame10_v1->draw();

	frame1_v2->draw();
	frame2_v2->draw();

	canvas1_stanczyk->draw();
	canvas2_karabin->draw();
	canvas3_wenus->draw();
	canvas4_bacchus->draw();

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

		std::cout << Camera::instance().position.x << " " << Camera::instance().position.z << std::endl;


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