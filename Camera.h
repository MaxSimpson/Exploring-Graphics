#ifndef _Camera_H_
#define _Camera_H_

#include <memory>

#include "GLInclude.h"

class Camera {
	private:
		float theta{0.f};
    float phi{0.f};
    float radius{10.f};

	public:
		Camera();

    //Drawing
    void Draw();

    //Camera Creation
    void setup(std::ifstream& ifs);

    // Event Handlers
    bool specialKeyPressed(GLint _key, GLint _x, GLint _y);
    bool keyPressed (GLubyte _key, GLint _x, GLint _y);

    glm::mat4 getViewMatrix() const;
};

#endif
