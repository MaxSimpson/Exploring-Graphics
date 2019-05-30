#ifndef _LIGHT_H_
#define _LIGHT_H_

//GLM
#include "GLInclude.h"

#include <fstream>
#include <sstream>

class Light{
	public:
		// Constructer
		Light(std::ifstream& ifs);

		// Draw light
		void Draw(GLuint _program);

	private:
		// Type of light 1 = position 0 = directional
		bool positional;
		// Location in space
		glm::vec3 position;
		// Unit vector for direction facing
		glm::vec3 direction;
		// Base Color
		glm::vec3 ambientColor;
		//Diffuse Color
		glm::vec3 diffuseColor;
		//Specular Color
		glm::vec3 specularColor;

};
#endif
