#include "Light.h"

// GL
#include "GLInclude.h"

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
		}else if (tag == "ambient_color"){
			iss >> ambientColor.x;
			iss >> ambientColor.y;
			iss >> ambientColor.z;
		}else if (tag == "diffuse_color"){
			iss >> diffuseColor.x;
			iss >> diffuseColor.y;
			iss >> diffuseColor.z;
		}else if (tag == "specular_color"){
			iss >> specularColor.x;
			iss >> specularColor.y;
			iss >> specularColor.z;		
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
Draw(GLuint _program){
	GLuint lightIndex = glGetUniformLocation(_program, "light");
	glm::vec4 positionData = glm::vec4(position, positional);
	glUniform4fv(lightIndex, 1, &positionData[0]);
}
