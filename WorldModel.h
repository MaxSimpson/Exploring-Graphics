#ifndef _WorldModel_H_
#define _WorldModel_H_

// My libraries
#include "Model.h"

#include <memory>

// GLM
#include "GLInclude.h"

class WorldModel{
	public:
    ////////////////////////////////////////////////////////////////////////////
    /// @brief Constructor
    /// @param ifs Stream to read in model data
    ///
    /// Constructor to make world model and maintain orginization 
		WorldModel(std::ifstream& ifs);

		#ifdef GL_WITH_SHADERS
			void meshDraw(GLuint _program, const glm::mat4& _projection, const glm::mat4& _view);
		#elif defined(GL_WITHOUT_SHADERS)
			void meshDraw();	
		#endif

		void Print_Data();
    float getAngle() const;

	private:
		glm::vec3 translation; //< Location in 3d space
		glm::vec3 scale; //< Scale of object
		float angle; //< Rotation angle
		glm::vec3 rotation_axis; //< Rotation Axis
		glm::vec3 color; //< World colo
		bool physics_toggle; //< Physics on or off
		void Physics(); //< Calculates physics
		int mass; //< Mass of object
		glm::vec3 force; //< Physics force
		string mat_used; //< Material used

};

#endif