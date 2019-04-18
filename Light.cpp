#include "Light.h"

// GL
#include <GL/glut.h>

// Streams
// #include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Light::
Light(ifstream& ifs){
	while(ifs) {
		string line;
		getline(ifs, line);
		istringstream iss(line);
		string tag;
		iss >> tag;
    	if(tag[0] == '#'){
      		// Comment
    	}else if (tag == "position"){
        	iss >> position.x;
			iss >> position.y;
			iss >> position.z;
    	}else if (tag == "direction"){
      		iss >> direction.x;
			iss >> direction.y;
			iss >> direction.z;
	 		glm::normalize(direction);
		}else if (tag == "color_rgb"){
			iss >> color.x;
			iss >> color.y;
			iss >> color.z;
		}else if (tag == "positional_light"){
			iss >> positional; 
   		}else if (tag == " "){
      		// Blank
    	}else if (tag == "end_light"){
     		break;
    	}
	}
}

void
Light::
Draw(){
	static GLfloat lightPosition[] = { 0.5f, 1.0f, 1.5f, 0.0f };
  	static GLfloat whiteLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
  	static GLfloat darkLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
  	glEnable(GL_LIGHTING);
  	glEnable(GL_LIGHT0);
  	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
  	glLightfv(GL_LIGHT0, GL_AMBIENT, darkLight);
  	glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteLight);
}
