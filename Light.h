#ifndef _LIGHT_H_
#define _LIGHT_H_

// My libraries
#include "Vector.h"

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
		Vector3 position;
		// Unit vector for direction facing
		Vector3 direction;
		// RGB float values
		Vector3 color;

};
#endif
