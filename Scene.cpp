#include "Scene.h"

#include <fstream>
#include <sstream>
using namespace std;

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
				iss >> background_color;
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

void
Scene::
Draw(){
	// Camera
    camera.Draw();
    // Light
    light.Draw();
    // Models
    for(int i = 0; i < models.size(); i++){
    		models[i]->Draw();
    }
    // Background
	glClearColor(background_color.getX(), background_color.getY(), background_color.getZ(), 0.0f);

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
