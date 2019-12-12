#ifndef _WorldModel_H_
#define _WorldModel_H_

// My libraries
#include "Model.h"
#include "MatManager.h"

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

		#ifdef GL_WITH_SHADERS
			void meshDraw(GLuint _program, const glm::mat4& _projection, const glm::mat4& _view);
		#elif defined(GL_WITHOUT_SHADERS)
			void meshDraw();	
		#endif

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Returns name of material to draw
    string getMat();

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Sets reference of material
    void setMat(Material* newMatPtr);

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Draws material
    void matDraw(GLuint _program);

		void Print_Data();
    float getAngle() const;

	private:
		glm::vec3 translation; //< Location in 3d space
		glm::vec3 scale; //< Scale of object
		float angle; //< Rotation angle
		glm::vec3 rotation_axis; //< Rotation Axis
		glm::vec3 color; //< World color
    
    // Materials
		string mat_used; //< Material used
    Material* mat_ptr; //< Material reference

    // Physics
		bool physics_toggle; //< Physics on or off
		void Physics(); //< Calculates physics
		int mass; //< Mass of object
		glm::vec3 force; //< Physics force

};

#endif