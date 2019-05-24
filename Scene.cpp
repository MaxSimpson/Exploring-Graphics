#include "Scene.h"

// STL
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

#include "GLInclude.h"

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
			cout << "Reading object" << endl;
			models.emplace_back(make_unique<WorldModel>(ifs));
		}else if(tag == "background_rgb"){
			cout << "Assigning Background rgb" << endl;
			// Background color
			iss >> background_color.x;
			iss >> background_color.y;
			iss >> background_color.z;
			background_color /= 255;
		}else if (tag == "start_camera"){
			cout << "Assigning camera" << endl;
			camera.setup(ifs);
		}else if (tag == "") {
			// Ignore
		}else if (tag[0] == '#'){
			// Ignore
		}else if (tag == "start_light"){
			// Creat new light
      lights.emplace_back(make_unique<Light>(ifs));
		}else {
			cerr << "Unknown tag from creating Scene: '" << tag << "'" << endl;
			exit(1);
		}
	}

	// Make for loop print data
	for(int i = 0; i < models.size(); i++){
		models[i]->Print_Data();
	}

}

void
Scene::
Initialize() {
	for(auto& model : models)
	  model->Initialize();
}

#ifdef GL_WITH_SHADERS
void
Scene::
Draw(GLuint _program){
	// Camera
  glm::mat4 view = camera.getViewMatrix();

	GLuint viewIndex = glGetUniformLocation(_program, "view");
  glUniformMatrix4fv(viewIndex, 1, GL_FALSE, &view[0][0]);

    // Light
    for(auto& l : lights)
      l->Draw();
    // Models
    for(int i = 0; i < models.size(); i++){
    		models[i]->Draw(_program, projection, view);
    }
    // Background
	glClearColor(background_color.x, background_color.y, background_color.z, 0.0f);
}
#elif defined(GL_WITHOUT_SHADERS)
void
Scene::
Draw(){
	// Camera
    camera.Draw();
    // Light
    for(auto& l : lights)
      l->Draw();
    // Models
    for(int i = 0; i < models.size(); i++){
    		models[i]->Draw();
    }
    // Background
	glClearColor(background_color.x, background_color.y, background_color.z, 0.0f);
}
#endif

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
