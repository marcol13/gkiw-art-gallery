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
Model* korytarz;
Model* venus;
Model* lawka;


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


//GLuint readTexture(const char* filename) {
//	GLuint tex;
//	glActiveTexture(GL_TEXTURE0);
//
//	//Wczytanie do pamięci komputera
//	std::vector<unsigned char> image;   //Alokuj wektor do wczytania obrazka
//	unsigned width, height;   //Zmienne do których wczytamy wymiary obrazka
//	//Wczytaj obrazek
//	unsigned error = lodepng::decode(image, width, height, filename);
//
//	//Import do pamięci karty graficznej
//	glGenTextures(1, &tex); //Zainicjuj jeden uchwyt
//	glBindTexture(GL_TEXTURE_2D, tex); //Uaktywnij uchwyt
//	//Wczytaj obrazek do pamięci KG skojarzonej z uchwytem
//	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
//		GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	return tex;
//}


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

	/*sp = new ShaderProgram("Shaders/v_simplest.glsl", NULL, "Shaders/f_simplest.glsl");*/
	/*tex0 = readTexture("Textures/metal.png");
	tex1 = readTexture("Textures/sky.png");*/

	aspectRatio = 1920.0f / 1080.0f;

	korytarz = new Model("Skeleton", "painted_plaster_017", "simplest");
	/*korytarz->scale(glm::vec3(0.5, 0.5, 0.5));
	korytarz->translate(glm::vec3(-5, 3, -2));
	korytarz->rotate(80.0f * PI / 180.0f, glm::vec3(1,1,1));*/

	venus = new Model("Venus", "bricks066", "simplest");
	venus->translate(glm::vec3(-5, 3, -2));
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

	/*glm::mat4 M = glm::mat4(1.0f);
	M = glm::rotate(M, 90.0f * PI / 180.0f, glm::vec3(0.0f, 1.0f, 0.0f));*/

	korytarz->draw();
	venus->draw();
	//sp->use();//Aktywacja programu cieniującego
	//Przeslij parametry programu cieniującego do karty graficznej
	//glUniformMatrix4fv(sp->u("P"), 1, false, glm::value_ptr(P));
	//glUniformMatrix4fv(sp->u("V"), 1, false, glm::value_ptr(Camera::instance().getMatrix()));
	//glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M));

	//glEnableVertexAttribArray(sp->a("vertex"));  //Włącz przesyłanie danych do atrybutu vertex
	//glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, korytarz->vertices.get()); //Wskaż tablicę z danymi dla atrybutu vertex

	//glEnableVertexAttribArray(sp->a("color"));  //Włącz przesyłanie danych do atrybutu color
	//glVertexAttribPointer(sp->a("color"), 4, GL_FLOAT, false, 0, korytarz->colors.get()); //Wskaż tablicę z danymi dla atrybutu color

	//glEnableVertexAttribArray(sp->a("normal"));  //Włącz przesyłanie danych do atrybutu normal
	//glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, korytarz->vertex_normals.get()); //Wskaż tablicę z danymi dla atrybutu normal

	//glEnableVertexAttribArray(sp->a("texCoord0"));  //Włącz przesyłanie danych do atrybutu texCoord
	//glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, korytarz->textures.get()); //Wskaż tablicę z danymi dla atrybutu texCoord

	/*glUniform1i(sp->u("textureMap0"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex0);

	glUniform1i(sp->u("textureMap1"), 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tex1);*/

	//glDrawArrays(GL_TRIANGLES, 0, korytarz->vertexCount); //Narysuj obiekt

	//glDisableVertexAttribArray(sp->a("vertex"));  //Wyłącz przesyłanie danych do atrybutu vertex
	//glDisableVertexAttribArray(sp->a("color"));  //Wyłącz przesyłanie danych do atrybutu color
	//glDisableVertexAttribArray(sp->a("normal"));  //Wyłącz przesyłanie danych do atrybutu normal
	//glDisableVertexAttribArray(sp->a("texCoord0"));  //Wyłącz przesyłanie danych do atrybutu texCoord0

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



		//std::cout << cursor_x * delta_time << std::endl;

		/*mAngle.x += cursor_x * delta_time;
		mAngle.y = glm::clamp(mAngle.y + cursor_y * delta_time, -PI / 2, PI / 2);*/

		/*pos_x += temp_z * delta_time * cos(mAngle.x) + temp_x * sin(mAngle.x) * delta_time;
		pos_y += temp_y * glfwGetTime();
		pos_z += temp_z * delta_time * sin(mAngle.x) - temp_x * delta_time * cos(mAngle.x);
		*/
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