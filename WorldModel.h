#ifndef _WorldModel_H_
#define _WorldModel_H_

// My libraries
#include "Model.h"

#include <memory>

// GLM
#include "GLInclude.h"

using namespace std;

class WorldModel{
	public:
    ////////////////////////////////////////////////////////////////////////////
    /// @brief Constructor
    /// @param ifs Stream to read in model data
    ///
    /// Constructor to make world model and maintain organization
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

    unique_ptr<Model> model;

		glm::vec3 translation; //< Location in 3d space
		glm::vec3 scale; //< Scale of object
		float angle; //< Rotation angle
		glm::vec3 rotation_axis; //< Rotation Axis
		glm::vec3 color; //< World color

    // Physics
		bool physics_toggle; //< Physics on or off
		void Physics(); //< Calculates physics
		int mass; //< Mass of object
		glm::vec3 force; //< Physics force

};

#endif
