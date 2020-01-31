#ifndef _WorldModel_H_
#define _WorldModel_H_

// My libraries
#include "Model.h"
#include "Collider.h"
#include "SphereCollider.h"
#include "BoxCollider.h"

// STL
#include <memory>

// GLM
#include "GLInclude.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////
/// @class Worldmodel class for overlying model data
////////////////////////////////////////////////////////////////////////////////
class WorldModel{
	public:
    ////////////////////////////////////////////////////////////////////////////
    /// @brief Constructor
    /// @param ifs Stream to read in model data
    ///
    /// Constructor to make world model and maintain organization
		WorldModel(std::ifstream& ifs);

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Intialization for model and data
    void Initialize();

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Update model
    void Update();

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Drawing for models
    /// @param _program Shader program id
    /// @param _projection Camera projection
    /// @param _view Camera view matrix
		void Draw(GLuint _program, const glm::mat4& _projection, 
              const glm::mat4& _view);
		
    ////////////////////////////////////////////////////////////////////////////
    /// @brief Output data for debugging
    void Print_Data();
    
    ////////////////////////////////////////////////////////////////////////////
    /// @brief Gets rotation angle
    float getAngle() const;

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Gets physicsOn
    bool getPhysicsOn();

    ////////////////////////////////////////////////////////////////////////////
    

    // Collider (Public FOR NOW)
    Collider collider; //< Collider

	private:
    unique_ptr<Model> model; //< Model
		glm::vec3 translation; //< Location in 3d space
		glm::vec3 scale; //< Scale of object
		float angle; //< Rotation angle
		glm::vec3 rotation_axis; //< Rotation Axis
		glm::vec3 color; //< World color

    // Dedicated physics
    void Physics(); //< Calculates physics
		bool physicsOn = false; //< Physics on or off
		int mass = 0; //< Mass of object
		glm::vec3 velocity = glm::vec3(0, 0, 0); //< Physics velocity

    // Constants
    //
    // Note: all data is in metric system ex: 9.8m/s^2 = gravity
    const float gravity = 9.8; //< Force of gravity

};

#endif
