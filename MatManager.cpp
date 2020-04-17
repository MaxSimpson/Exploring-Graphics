#include "MatManager.h"

#include <iostream>
#include <vector>
using namespace std;

MatManager& getMatManager() {
  static MatManager matManager;
  return matManager;
}

// Constructor
MatManager::MatManager(){}

// Initialize
void
MatManager::
initialize(){
  for(auto& material : materials)
		material.second->Initialize();
}

void
MatManager::
makeMaterials(string mat_location) {
  // Open location
	ifstream mat_ifs (mat_location);
	// Parse material
	cout << "    Parsing materials: " << mat_location << endl;
	// Material Data pre-contsruction
  string mat_name;
	glm::vec3 kd;
	glm::vec3 ka;
	glm::vec3 ks;
	string image_tag;
  int mat_counter = 0;
  vector<string> matTags;
	while(mat_ifs){
		string mat_line;
		getline(mat_ifs, mat_line);
		istringstream mat_iss(mat_line);
		string mat_tag = "";
		mat_iss >> mat_tag;

		if(mat_tag == "newmtl"){
      // Save last material
			if(mat_counter != 0){
        cout << "Adding mtl: " << mat_name << endl;
				materials.emplace(mat_name, make_unique<Material>(mat_name, kd, ka, ks, image_tag));
			}
			mat_iss >> mat_name;
			mat_counter += 1;
    }else if(mat_tag == "Ka"){
      // Ambient color
			mat_iss >> ka.x;
			mat_iss >> ka.y;
			mat_iss >> ka.z;
		}else if(mat_tag == "Kd"){
      // Diffuse color
			mat_iss >> kd.x;
			mat_iss >> kd.y;
			mat_iss >> kd.z;
		}else if (mat_tag == "Ks"){
      // Specular color
			mat_iss >> ks.x;
			mat_iss >> ks.y;
			mat_iss >> ks.z;
		}else if (mat_tag == "map_Kd") {
      // Diffuse map
      string filename;
      mat_iss >> filename;
      string dir = "ModelFiles";
      image_tag = dir + "/" + filename;
      cout << "        New image: " << image_tag << endl;
    }else if ((mat_tag == "")||(mat_tag == "#")){
			//Ignore
   	}else{
       matTags.emplace_back(mat_tag);
		}
  }
  cout << "        Adding mtl: " << mat_name << endl;
  materials.emplace(mat_name, make_unique<Material>(mat_name, kd, ka, ks, image_tag));
  cout << "        Materials: " << materials.size() << endl;
  cout << "        Unknown tags: ";
  for(string& matTag : matTags){
    cout << matTag + ", " ;
  }
  cout << endl;
}
