// Header
#include "Camera.h"

// Stuff
#include <cmath>
#include <limits>

// Glut
#include <GL/glut.h>

// Streams
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

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

bool
Camera::
keyPressed(GLubyte _key, GLint _x, GLint _y){
  switch(_key){
    // W key pressed
    case 119:
      if(radius > 1.1f)
        radius -= 0.1f;
      return true;

    // S key pressed
    case 115:
      if(radius < 49.9f)
        radius += 0.1f;
      return true;
    // Unhandled
    default:
      std::cout << "Unhandled key" << std::endl;
      return false;
    }
  }

void
Camera::
setup(ifstream& ifs){
  while(ifs) {
		string line;
		getline(ifs, line);
		istringstream iss(line);
		string tag;
		iss >> tag;
    if(tag[0] == '#'){
      // Comment
    }else if (tag == "theta_value"){
      iss >> theta;
      theta *= (pi / 180);
    }else if (tag == "phi_value"){
      iss >> phi;
      phi *= (pi / 180);
    }else if (tag == " "){
      // Blank
    }else if (tag == "end_camera"){
      break;
    }
  }
}

glm::mat4 
Camera::
getViewMatrix() const {
  float u = radius * cos(phi);
  float x = u*cos(theta);
  float y = radius * sin(phi);
  float z = u*sin(theta);
  return glm::lookAt(glm::vec3(x, y, z), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
}