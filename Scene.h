#ifndef _SCENE_H_
#define _SCENE_H_

// CPP files
#include <memory>
#include <vector>

// My files
#include "Camera.h"
#include "Light.h"
#include "WorldModel.h"

// GLM
#include <glm/glm.hpp>

class Scene {
	public:
		// Constructor
		Scene(const std::string& location);

		// Initialize
		void Initialize();

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
		// Projection
		glm::mat4 projection;
		// Camera
		Camera camera;
		// Lights
		std::vector<std::unique_ptr<Light>> lights;
		// World Models
		std::vector<std::unique_ptr<WorldModel>> models;
		// Background color
		glm::vec3 background_color;
};

#endif
