#include "Material.h"

// GL
#include "GLInclude.h"

// Streams
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Material::
Material(string _name,
         glm::vec3 _kd, glm::vec3 _ka, glm::vec3 _ks, string _image_tag){
  mat_name = _name;
  kd = _kd;
  ka = _ka;
  ks = _ks;
  image_tag = _image_tag;
  image = make_unique<Image>(_image_tag);
}

Material::
Material(const Material& _oldMat){
 ka = _oldMat.ka;
 ks = _oldMat.ks;
 kd = _oldMat.kd;
 mat_name = _oldMat.mat_name;
 image_tag = _oldMat.image_tag;
 image = make_unique<Image>(image_tag);
 texture = _oldMat.texture;
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
    glGetUniformLocation(_program, ("materials[" + ::to_string(0) + "].tex").c_str());

    glUniform1i(samplerIndex, 0);
    //glUniform1f(samplerIndex, m_sampler);
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
      //cout << kd.x << " " << kd.y << " " << kd.z << endl;
    } else if (tag == "Ks") {
      // Specular
      iss >> ks.x;
      iss >> ks.y;
      iss >> ks.z;
    } else if (tag == "map_Kd") {
      string filename;
      iss >> filename;
      cout << "New image: " << filename << endl;
      image = make_unique<Image>(dir + "/" + filename);
    } else{
      cout << "Tag: " << tag << endl;
    }
  }
  return;
}
