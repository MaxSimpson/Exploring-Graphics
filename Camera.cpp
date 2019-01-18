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
Draw(){
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

bool
Camera::
specialKeyPressed(GLint _key, GLint _x, GLint _y) {
  switch(_key) {
    // Arrow keys
    case GLUT_KEY_LEFT:
      g_theta -= 0.02f;
      return true;
    case GLUT_KEY_RIGHT:
      g_theta += 0.02f;
      return true;
    // Unhandled
    default:
      return false;
  }
}
