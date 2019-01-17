#include "Camera.h"
#include <cmath>
#include <GL/glut.h>
#include <iostream>

Camera::
Camera(){
	std::cout << "Camera created" << std::endl;
}

void
Camera::
draw(){
	glMatrixMode(GL_MODELVIEW);
  	glLoadIdentity();
  	gluLookAt(10*sin(g_theta), 0.f, 10*cos(g_theta),
              0.f, 0.f, 0.f, 0.f, 1.f, 0.f);
}

void 
Camera::
change_theta(float change){
	g_theta += change;
}
