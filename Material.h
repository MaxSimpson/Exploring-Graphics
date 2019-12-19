#ifndef _MATERIAL_H_
#define _MATERIAL_H_

// Includes
#include "GLInclude.h"

#include <fstream>
#include <sstream>
#include <memory>

#include "Image.h"

////////////////////////////////////////////////////////////////////////////////
/// @class Class for storing materials
////////////////////////////////////////////////////////////////////////////////
class Material{
  public:
    ////////////////////////////////////////////////////////////////////////////
    /// @brief Constructor for material
    /// @param _name The name of the material
    /// @param _kd Diffuse value for materials
    /// @param _ka Ambient value for materials
    /// @param _ks Specular value for materials
    /// @param image_tag Image tag for diffuse map
    Material(std::string _name, glm::vec3 _kd, glm::vec3 _ka, glm::vec3 _ks, 
             std::string image_tag);
    ////////////////////////////////////////////////////////////////////////////
    /// @brief Initialization
    void Initialize();
    ////////////////////////////////////////////////////////////////////////////
    /// @brief Drawing of material
    /// @param _program Shader program for rendering
    void Draw(GLuint _program);

  private:
    glm::vec3 ka; //< Ambient factor
    glm::vec3 ks; //< Specular factor
    glm::vec3 kd; //< Diffuse factor
    std::string mat_name; //< Material 
    std::unique_ptr<Image> image; //< Texture
    GLuint texture{0}; //< GL Image storage
    ////////////////////////////////////////////////////////////////////////////
    /// @brief Parse data
    void Parse (const std::string& location);
};

#endif
