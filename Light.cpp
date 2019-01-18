#include "Light.h"
#include <GL/glut.h>

Light::
Light(){}

void
Light:: 
draw(){
	static GLfloat lightPosition[] = { 0.5f, 1.0f, 1.5f, 0.0f };
  	static GLfloat whiteLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
  	static GLfloat darkLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
  	glEnable(GL_LIGHTING);
  	glEnable(GL_LIGHT0);
  	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
  	glLightfv(GL_LIGHT0, GL_AMBIENT, darkLight);
  	glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteLight);
}
