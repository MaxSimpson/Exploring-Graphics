#include "Scene.h"

// STL
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

#include "GLInclude.h"

void
Scene::
Initialize() {
	for(auto& material : materials)
		material->Initialize();
}

Scene::
Scene(const string& location){

  matManager = make_unique<MatManager>();

	ifstream ifs(location);
	// Counter for materials
  int _counter = 0;

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
		}else if (tag == "start_material"){
			// Materials
      // cout << "Reading material" << endl;
      bool end_Material = false;

      // Temporary Data for material
      string mat_location;
      string tag;
      string mat_name;

      while(!end_Material){
        // Material loop
        getline(ifs, line);
			  istringstream iss(line);
			  iss >> tag;
			  if(tag == "file_location"){
				  // Read location
				  iss >> mat_location;
				  // cout << "Found file location: " << mat_location << endl;
        }else if(tag == "mat_name"){
          iss >> mat_name;
			  }else if(tag == "end_material"){
          // End Material
          end_Material = true;
          matManager->makeMaterials(mat_location, tag, mat_name, _counter);
        }else{
          cerr << "Unkown tag from making materal: " << tag << endl;
          exit(1);
        }
      }
      _counter += 1;
		}else if (tag == "start_light"){
			// Create new light
      lights.emplace_back(make_unique<Light>(ifs));
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
  // Print # of materials
  cout << "Number of Materials: " << materials.size() << endl;

}


#ifdef GL_WITH_SHADERS
void
Scene::
Draw(GLuint _program){
	// Camera
  glm::mat4 view = camera.getViewMatrix();
	GLuint viewIndex = glGetUniformLocation(_program, "view");
  glUniformMatrix4fv(viewIndex, 1, GL_FALSE, &view[0][0]);
	// Materials
	for (auto& m : materials){
		m->Draw(_program);
	}
	// Light
	for(auto& l : lights)
		l->Draw(_program);
	// Models
	for(int i = 0; i < models.size(); i++){
			models[i]->meshDraw(_program, projection, view);
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
