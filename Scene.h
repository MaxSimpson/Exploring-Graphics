#ifndef _SCENE_H_
#define _SCENE_H_

#include <memory>
#include <vector>
#include <GL/glut.h>

#include "Camera.h"
#include "Light.h"
#include "WorldModel.h"

class Scene {
	public:
		//Constructor
		Scene(const std::string& location);

		// Drawing methods
		void Draw();

		// Event handlers
		bool specialKeyPressed(GLint _key, GLint _x, GLint _y);

		//Add Model
		void Add_Model(const std::string& location);

	private:
		Camera camera;
		Light light;
		//Actual Model
		std::unique_ptr<Model> model; 
		
		//Testing World Models
		std::vector<std::unique_ptr<WorldModel>> models;
		
};

#endif
