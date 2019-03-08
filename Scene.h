#ifndef _SCENE_H_
#define _SCENE_H_

#include <memory>
#include <vector>
#include <GL/glut.h>

#include "Camera.h"
#include "Light.h"
#include "WorldModel.h"
#include "Vector.h"

class Scene {
	public:
		//Constructor
		Scene(const std::string& location);

		// Initialize
		void Initialize();
		
		// Drawing methods
		void Draw();

		// Event handlers
		bool specialKeyPressed(GLint _key, GLint _x, GLint _y);

	private:
		//Camera
		Camera camera;
		//Light
		Light light;
		//World Models
		std::vector<std::unique_ptr<WorldModel>> models;
		//Background color
		Vector3 background_color;
};

#endif
