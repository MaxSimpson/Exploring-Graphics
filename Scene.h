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
#include "Prefab.h"

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
    /// @brief location Location of world file for reading in data
		Scene(const std::string& location);

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Update current scene
    /// @param _dt Delta time
    void Update(float _dt);

    ////////////////////////////////////////////////////////////////////////////
		/// @brief Draw scene
    /// @param _program Link to shader program
		void Draw(GLuint _program);

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Handle keys being pressed
    /// @param _key Key ID
    /// @param _x X cordinate of mouse when key clicked
    /// @param _y Y cordinate of mouse when key clicked
		bool specialKeyPressed(GLint _key, GLint _x, GLint _y);
		bool keyPressed(GLubyte _key, GLint _x, GLint _y);

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Set scene projection
		void SetProjection(const glm::mat4& _p) {projection = _p;}

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Generates models and materials at random points in a given area
    /// @param minCords The minimum xyz range for a planet to be created at
    /// @param maxCords The maximum xyz range for a planet to be created at
    /// @param totalPrefabs The total number of prefabs to be placed in the range
    /// @param spawn Chance Percentage chance that a planet spawns at any given point
    void generatePrefabs (glm::vec3 minCords, glm::vec3 maxCords,
                          int totalPrefabs, float spawnChance);

	private:
		glm::mat4 projection; //< Projection
		Camera camera; //< Camera
		std::vector<std::unique_ptr<Light>> lights; //< Lights
		std::vector<std::unique_ptr<WorldModel>> models; //< World models
    BoxCollider collider;
    std::vector<int> physicsModels; //< List of models by physics type
		glm::vec3 background_color; //< Background colors
		bool physics_Toggle; //< Physics enabled
    Prefab prefabs; //< Stores possible prefab data for making objects
};

#endif
