#ifndef _LIGHT_H_
#define _LIGHT_H_

//GLM
#include "GLInclude.h"

#include <fstream>
#include <sstream>

////////////////////////////////////////////////////////////////////////////////
/// @brief Light for scene
////////////////////////////////////////////////////////////////////////////////
class Light{
	public:
    ////////////////////////////////////////////////////////////////////////////
		/// @brief Constructor for light
    /// @param ifs Input stream for reading file data
		Light(std::ifstream& ifs);

    ////////////////////////////////////////////////////////////////////////////
		/// @brief Draws lighting
    /// @param _program Shader program for shading
		void Draw(GLuint _program);

	private:
		bool positional; //< Type of light (1 = pos, 0 = dirc)
		glm::vec3 position; //< Location in space
		glm::vec3 direction; //< Direction of light
		glm::vec3 ambientColor; //< Ambient color
		glm::vec3 diffuseColor; //< Diffuse color
		glm::vec3 specularColor; //< Specular color

};
#endif
