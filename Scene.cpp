#include "Scene.h"

// STL
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

#include "GLInclude.h"

void
Scene::
MakeMaterials(string mat_location, string tag, string mat_name, int _counter){
	string image_tag;
  // Open location
	ifstream mat_ifs (mat_location);
	// Parse material
	cout << "Parsing materials" << endl;
	// unique_ptr<Image> image;
	// Material Data pre-contsruction
	glm::vec3 kd;
	glm::vec3 ka;
	glm::vec3 ks;
	while(mat_ifs){
		string mat_line;
		getline(mat_ifs, mat_line);
		istringstream mat_iss(mat_line);
		string mat_tag = "";
		mat_iss >> mat_tag;

		// if(mat_tag == "newmtl"){
		// 	if(mat_counter != 0){
		// 		materials.emplace_back(make_unique<Material>(mat_counter, mat_name, kd, ka, ks, image_tag));
		// 	}
		// 	mat_iss >> mat_name;
		// 	mat_counter += 1;
		if(mat_tag == "Ka"){
			mat_iss >> ka.x;
			mat_iss >> ka.y;
			mat_iss >> ka.z;
      // cout << "Ka: " << ka.x << " " << ka.y << " " << ka.z << endl;
		}else if(mat_tag == "Kd"){
			mat_iss >> kd.x;
			mat_iss >> kd.y;
			mat_iss >> kd.z;
      // cout << "Kd: " << kd.x << " " << kd.y << " " << kd.z << endl;
		}else if (mat_tag == "Ks"){
			mat_iss >> ks.x;
			mat_iss >> ks.y;
			mat_iss >> ks.z;
      // cout << "Ks: " << ks.x << " " << ks.y << " " << ks.z << endl;
		}else if (mat_tag == "map_Kd") {
      string filename;
      mat_iss >> filename;
      string dir = "ModelFiles";
      // image = make_unique<Image>(dir + "/" + filename);
      image_tag = dir + "/" + filename;
      cout << "New image: " << image_tag << endl;
    }else if ((mat_tag == "")||(mat_tag == "#")){
			//Ignore
   	}else{
			// cout << "Unknown tag: " << mat_tag << endl;
		}
		// cout << "Material parsing complete. " << mat_counter << " materials have been created." << endl;
	  //materials.emplace_back(make_unique<Material>(ifs, materials_count));
  }
  materials.emplace_back(make_unique<Material>(_counter, mat_name, kd, ka, ks, image_tag));
}

void
Scene::
Initialize() {
	for(auto& model : models)
		model->Initialize();
	for(auto& material : materials)
		material->Initialize();
}


Scene::
Scene(const string& location){

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
          MakeMaterials(mat_location, tag, mat_name, _counter);
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
