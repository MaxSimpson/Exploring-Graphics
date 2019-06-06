#ifndef _WorldModel_H_
#define _WorldModel_H_

// My libraries
#include "Model.h"

#include <memory>

// GLM
#include "GLInclude.h"

class WorldModel{
	public:
		WorldModel(std::ifstream& ifs);

		void Initialize();
		#ifdef GL_WITH_SHADERS
			void Draw(GLuint _program, const glm::mat4& _projection, const glm::mat4& _view);
		#elif defined(GL_WITHOUT_SHADERS)
			void Draw();	
		#endif
		void Print_Data();
		float getAngle() const;
	private:
		// Location
		glm::vec3 translation;
		// Size
		glm::vec3 scale;
		// Rotation Angle
		float angle;
		// Rotation along xyz
		glm::vec3 rotation_axis;
		// Model Color
		glm::vec3 color;
		// Model Data
		std::unique_ptr<Model> model; 
		// Physics on or off
		bool physics_toggle;
		// Calculates physics
		void Physics(bool physics_Toggle);
		// Physics mass
		int mass;
		// Physics force
		glm::vec3 force;
		// Material usded
		string mat_used;

};

#endif