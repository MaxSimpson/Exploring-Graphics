#include "Camera.h"
#include <cmath>
#include <limits>
#include <GL/glut.h>
#include <iostream>

const float pi = 3.1415926535f;

Camera::
Camera(){
	std::cout << "Camera created" << std::endl;
}

void
Camera::
Draw(){
    glMatrixMode(GL_MODELVIEW);
  	glLoadIdentity();
    float u = radius * cos(phi);
    float x = u*cos(theta);
    float y = radius * sin(phi);
    float z = u*sin(theta);
  	gluLookAt(x, y, z,
              0.f, 0.f, 0.f, 0.f, 1.f, 0.f);
}

bool
Camera::
specialKeyPressed(GLint _key, GLint _x, GLint _y) {
  switch(_key) {
    // Arrow keys
    case GLUT_KEY_RIGHT:
      theta -= 0.02f;
      if(theta < -pi)
        theta += 2*pi;
      return true;
    case GLUT_KEY_LEFT:
      theta += 0.02f;
      if(theta > pi)
        theta -= 2*pi;
      return true;
    case GLUT_KEY_UP:
      if(phi < pi/2 - 0.02f - std::numeric_limits<float>::epsilon())
        phi += 0.02f;
      return true;
    case GLUT_KEY_DOWN:
      if(phi > -pi/2 + 0.02f + std::numeric_limits<float>::epsilon())
        phi -= 0.02f;
      return true;
    // Unhandled
    default:
      return false;
  }
}
