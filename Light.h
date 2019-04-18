#ifndef _LIGHT_H_
#define _LIGHT_H_

//GLM
#include <glm/glm.hpp>

class Light{
	public:
		// Constructer
		Light(std::ifstream& ifs);

		// Draw light
		void Draw();

	private:
		// Type of light
		bool positional;
		// Location in space
		glm::vec3 position;
		// Unit vector for direction facing
		glm::vec3 direction;
		// RGB float values
		glm::vec3 color;

};
#endif
