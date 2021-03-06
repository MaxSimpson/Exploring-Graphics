#include "Scene.h"

// STL
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

// Model generation
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "GLInclude.h"

#include "MatManager.h"

void
Scene::
Initialize() {
	getMatManager().initialize();
  // Collider init for now
  collider.Initialize();
  for(auto& m : models)
		m->Initialize();


}

Scene::
Scene(const string& location){

	ifstream ifs(location);

	while(ifs) {
		string line;
		getline(ifs, line);

		istringstream iss(line);
		string tag;
		iss >> tag;

		if(tag == "start_object") {
			// Create new object
      cout << "Reading object" << endl;
			models.emplace_back(make_unique<WorldModel>(ifs));
		}else if(tag == "background_rgb"){
			// cout << "Assigning Background rgb" << endl;
			// Background color
			iss >> background_color.x;
			iss >> background_color.y;
			iss >> background_color.z;
			background_color /= 255;
    }else if (tag == "start_camera"){
			// cout << "Assigning camera" << endl;
			camera.setup(ifs);
		}else if (tag == "") {
			// Ignore
		}else if (tag[0] == '#'){
			// Ignore
		}else if (tag == "physics"){
      // Physics toggle
			iss >> physics_Toggle;
		}else if (tag == "start_light"){
			// Create new light
      lights.emplace_back(make_unique<Light>(ifs));
    }else if(tag == "prefab_location"){
      // Read prefab location
      string location;
      iss >> location;
      prefabs.Initialize(location);
    }else {
			// Error
      cerr << "Unknown tag from creating Scene: '" << tag << "'" << endl;
			exit(1);
		}
	}
	// Make for loop print data
	for(int i = 0; i < models.size(); i++){
		models[i]->Print_Data();
	}
  // Setup list of objects with physics on
  for(int i = 0; i < models.size(); i++){
    if(models[i]->getPhysicsOn()){
      physicsModels.emplace_back(i);
    }
  }
}

void
Scene::
Update(float _dt){
  // Update models
  for(auto& m : models){
    m->Update(_dt, models);
  }
}

void
Scene::
Draw(GLuint _program){
	// Camera
  glm::mat4 view = camera.getViewMatrix();
	GLuint viewIndex = glGetUniformLocation(_program, "view");
  glUniformMatrix4fv(viewIndex, 1, GL_FALSE, &view[0][0]);
	// Light
	for(auto& l : lights)
		l->Draw(_program);
	// Models
	for(auto& m : models){
		m->Draw(_program, projection, view);
	}
  // Collider wireframe
  collider.Draw(_program, projection, view);

  // Background
	glClearColor(background_color.x, background_color.y, background_color.z, 0.0f);
}

bool
Scene::
specialKeyPressed(GLint _key, GLint _x, GLint _y) {
    return camera.specialKeyPressed(_key, _x, _y);
}

bool
Scene::
keyPressed(GLubyte _key, GLint _x, GLint _y){
	return camera.keyPressed(_key, _x, _y);
}

void
Scene::
generatePrefabs(glm::vec3 minCords, glm::vec3 maxCords, int totalPrefabs, float spawnChance){
  // while # of prefabs is less than total prefabs
  // for each point in the domain
  // if random number is lower than spawn chance
  // get and emplace prefab 
}
