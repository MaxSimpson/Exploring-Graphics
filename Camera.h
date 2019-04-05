#ifndef _Camera_H_
#define _Camera_H_

#include <GL/glut.h>
class Camera {
	private:
		float theta{0.f};
    float phi{0.f};
    float radius{10.f};

	public:
		Camera();

    void Draw();

    bool specialKeyPressed(GLint _key, GLint _x, GLint _y);
};

#endif
