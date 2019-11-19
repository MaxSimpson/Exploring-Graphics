#ifndef _MATERIAL_H_
#define _MATERIAL_H_

// Includes
#include "GLInclude.h"

#include <fstream>
#include <sstream>
#include <memory>

#include "Image.h"

class Material{

    public:
      // Constructor
      Material(int _counter, std::string _name, glm::vec3 _kd, glm::vec3 _ka, glm::vec3 _ks, std::string image_tag);
      // Initialization
      void Initialize();
      // Send material data
      void Draw(GLuint _program);

    private:
      // Which material
      int mat_place;
      // Ambient factor
      glm::vec3 ka;
      // Specular factor
      glm::vec3 ks;
      // Diffuse factor
      glm::vec3 kd;
      // Material name
      std::string mat_name;
      // Texture information
      std::unique_ptr<Image> image;
      GLuint texture{0};
      // Parse data
      void Parse (const std::string& location);
};

#endif
