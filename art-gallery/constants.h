#include <glm/gtc/matrix_transform.hpp>

#ifndef CONSTANTS_H
#define CONSTANTS_H

const float PI = 3.141592653589793f;
const glm::mat4 P = glm::perspective(50.0f * PI / 180.0f, 1920.0f/1080.0f, 0.01f, 50.0f); //Wylicz macierz rzutowania
const float movement_speed = 0.05;
const float mouse_sensitivity = 0.3;
const int window_width = 1920;
const int window_height = 1080;

#endif
