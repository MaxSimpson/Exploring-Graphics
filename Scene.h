#ifndef _SCENE_H_
#define _SCENE_H_

#include <memory>

#include <GL/glut.h>

#include "Camera.h"
#include "Light.h"
#include "Model.h"

class Scene {
	public:
		Scene(const std::string& location);

		// Drawing methods
		void Draw();

		// Event handlers
		bool specialKeyPressed(GLint _key, GLint _x, GLint _y);

	private:
		Camera camera;
		Light light;
		std::unique_ptr<Model> model; 
};

#endif
