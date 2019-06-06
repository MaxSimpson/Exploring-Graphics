#ifndef _MATERIAL_H_
#define _MATERIAL_H_

// Includes
#include "GLInclude.h"

#include <fstream>
#include <sstream>

class Material{

    public:
    // Constructor
    Material(std::ifstream& ifs);
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
    // Parse data
    void Parse (const std::string& location);
};

#endif
