#include "MatManager.h"

#include <iostream>
using namespace std;

// Constructor
MatManager::
MatManager(){

}

void
MatManager::
makeMaterials(string mat_location, string tag, string mat_name, int _counter){
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
  int mat_counter = 0;
	while(mat_ifs){
		string mat_line;
		getline(mat_ifs, mat_line);
		istringstream mat_iss(mat_line);
		string mat_tag = "";
		mat_iss >> mat_tag;


		if(mat_tag == "newmtl"){
      // Create new material
			if(mat_counter != 0){
				materials.emplace_back(make_unique<Material>(mat_counter, mat_name, kd, ka, ks, image_tag));
			}
			mat_iss >> mat_name;
			mat_counter += 1;

    }else if(mat_tag == "Ka"){
      // Ambient color
			mat_iss >> ka.x;
			mat_iss >> ka.y;
			mat_iss >> ka.z;
      // cout << "Ka: " << ka.x << " " << ka.y << " " << ka.z << endl;
		}else if(mat_tag == "Kd"){
      // Diffuse color
			mat_iss >> kd.x;
			mat_iss >> kd.y;
			mat_iss >> kd.z;
      // cout << "Kd: " << kd.x << " " << kd.y << " " << kd.z << endl;
		}else if (mat_tag == "Ks"){
      // Specular color
			mat_iss >> ks.x;
			mat_iss >> ks.y;
			mat_iss >> ks.z;
      // cout << "Ks: " << ks.x << " " << ks.y << " " << ks.z << endl;
		}else if (mat_tag == "map_Kd") {
      // Diffuse map
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

    // int _counter, std::string _name, glm::vec3 _kd, glm::vec3 _ka, glm::vec3 _ks, std::string image_tag
  }
  materials.emplace_back(make_unique<Material>(_counter, mat_name, kd, ka, ks, image_tag));
}

