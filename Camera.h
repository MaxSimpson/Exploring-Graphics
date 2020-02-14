#ifndef _Camera_H_
#define _Camera_H_

// Includes
#include <memory>

#include "GLInclude.h"

////////////////////////////////////////////////////////////////////////////////
/// @brief Camera for scene
////////////////////////////////////////////////////////////////////////////////
class Camera {
	private:
		float theta{0.f}; //< Theta for rotation
    float phi{0.f}; //< Phi for rotation
    float radius{10.f}; //< Radius of rotation

	public:
    ////////////////////////////////////////////////////////////////////////////
    /// @brief Constructor for camera class
		Camera();

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Draws camera at location and rotation
    void Draw();

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Setup for camera 
    /// @param ifs Input stream to read camera data
    void setup(std::ifstream& ifs);

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Check for special key pressed
    /// @param _key ID of key pressed
    /// @param _x X cord of mouse
    /// @param _y Y cord of mouse
    bool specialKeyPressed(GLint _key, GLint _x, GLint _y);

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Check for regular key pressed
    /// @param _key ID of key pressed
    /// @param _x X cord of mouse
    /// @param _y Y cord of mouse
    bool keyPressed (GLubyte _key, GLint _x, GLint _y);

    glm::mat4 getViewMatrix() const; //< View matrix for shaders
};

#endif
