#ifndef _SCENE_H_
#define _SCENE_H_

// CPP files
#include <memory>
#include <vector>

// My files
#include "Camera.h"
#include "Light.h"
#include "WorldModel.h"
#include "Material.h"
#include "MatManager.h"
#include "BoxCollider.h"

// GLM
#include <glm/glm.hpp>

////////////////////////////////////////////////////////////////////////////////
/// @class Class for the scene on the screen
////////////////////////////////////////////////////////////////////////////////
class Scene {
	public:
    ////////////////////////////////////////////////////////////////////////////
		/// @brief Initialize scene
		void Initialize();

    ////////////////////////////////////////////////////////////////////////////
		/// @brief Construct scened data
		Scene(const std::string& location);

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Update current scene
<<<<<<< HEAD
    void Update(float deltaTime);
=======
    /// @param _dt Delta time
    void Update(float _dt);
>>>>>>> db98d9eea21feed3218ebda7a6f886fd58834551

    ////////////////////////////////////////////////////////////////////////////
		/// @brief Draw scene
		void Draw(GLuint _program);

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Handle keys being pressed
		bool specialKeyPressed(GLint _key, GLint _x, GLint _y);
		bool keyPressed(GLubyte _key, GLint _x, GLint _y);

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Set scene projection
		void SetProjection(const glm::mat4& _p) {projection = _p;}

	private:
		glm::mat4 projection; //< Projection
		Camera camera; //< Camera
		std::vector<std::unique_ptr<Light>> lights; //< Lights
		std::vector<std::unique_ptr<WorldModel>> models; //< World models
    BoxCollider collider;
    std::vector<int> physicsModels; //< List of models by physics type
		glm::vec3 background_color; //< Background colors
		bool physics_Toggle; //< Physics enabled
};

#endif
