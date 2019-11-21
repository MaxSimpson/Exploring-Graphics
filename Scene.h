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

// GLM
#include <glm/glm.hpp>

class Scene {
	public:

		// Initialize
		void Initialize();

		// Constructor
		Scene(const std::string& location);

		// Drawing methods
		#ifdef GL_WITH_SHADERS
		void Draw(GLuint _program);
		#elif defined(GL_WITHOUT_SHADERS)
		void Draw();
		#endif

		// Event handlers
		bool specialKeyPressed(GLint _key, GLint _x, GLint _y);
		bool keyPressed(GLubyte _key, GLint _x, GLint _y);

		void SetProjection(const glm::mat4& _p) {projection = _p;}

	private:
		glm::mat4 projection; //< Projection
		Camera camera; //< Camera
		std::vector<std::unique_ptr<Light>> lights; //< Lights
		std::vector<std::unique_ptr<WorldModel>> models; //< World models
		glm::vec3 background_color; //< Background colors
		bool physics_Toggle; //< Physics enabled
		unique_ptr<MatManager> matManager; //< Material manager
};

#endif
