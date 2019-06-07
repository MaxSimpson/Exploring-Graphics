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
    Material(std::ifstream& ifs);
    // Initialization
    void Initialize();
    // Send material data
    void Draw(GLuint _program);

    private:
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
