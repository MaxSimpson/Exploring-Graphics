#include "Material.h"

// GL
#include "GLInclude.h"

// Streams
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


Material::
Material(ifstream& ifs){
	while(ifs) {
        string line;
		getline(ifs, line);
		istringstream iss(line);
		string tag;
		iss >> tag;
    	if(tag[0] == '#'){
      		// Comment
        }else if (tag == ""){
            // Ignore
        }else if (tag == "file_location"){
            cout << "" << endl;
            // File location
            string location;
			iss >> location;
            Parse(location);
        }else if (tag == "end_material"){
            // End material
            return;
        }
    }
}

void
Material::
Initialize() {
  if(image != nullptr)
    texture = image->initialize();
}

void
Material::
Draw(GLuint _program){
    //"materials[" + id + "].ka"
    // Ambient
    GLuint kaIndex = glGetUniformLocation(_program, "ka");
    glUniform3fv(kaIndex, 1, &ka[0]);
    // Diffuse
    GLuint kdIndex = glGetUniformLocation(_program, "kd");
    glUniform3fv(kdIndex, 1, &kd[0]);
    // Specular
    GLuint ksIndex = glGetUniformLocation(_program, "ks");
    glUniform3fv(ksIndex, 1, &ks[0]);

    if(image != nullptr) {
      GLuint samplerIndex =
        glGetUniformLocation(_program, "textureSampler");
      //glUniform1f(samplerIndex, m_sampler);
      glUniform1i(samplerIndex, 0);

      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, texture);
    }
}

void
Material::
Parse(const string& location){
    string dir = location.substr(0, location.rfind('/'));
    std::string line;
    //Setup Input stream
    std::ifstream ifs{location};
    while(getline(ifs, line)) {
        std::string tag;
        std::istringstream iss{line};
        iss >> tag;
        if((tag[0] == '#') || (tag == " ")) {
            // Do nothing
        } else if (tag == "Ka") {
            // Ambient
            iss >> ka.x;
            iss >> ka.y;
            iss >> ka.z;
        } else if (tag == "Kd") {
            // Diffuse
            iss >> kd.x;
            iss >> kd.y;
            iss >> kd.z;
            cout << kd.x << " " << kd.y << " " << kd.z << endl;
        } else if (tag == "Ks") {
            // Specular
            iss >> ks.x;
            iss >> ks.y;
            iss >> ks.z;
        } else if (tag == "map_Kd") {
            string filename;
            iss >> filename;
            image = make_unique<Image>(dir + "/" + filename);

        } else{

        }


    }
    return;
}