#ifndef _WorldModel_H_
#define _WorldModel_H_

// My libraries
#include "Model.h"

#include <memory>

// GLM
#include <glm/glm.hpp>

class WorldModel{
	public:
		WorldModel(std::ifstream& ifs);

		void Initialize();
		void Draw();	
		void Print_Data();
		float getAngle() const;
	private:
		glm::vec3 translation;
		glm::vec3 scale;
		float angle;
		glm::vec3 rotation_axis;
		glm::vec3 color;
		std::unique_ptr<Model> model; 
};

#endif