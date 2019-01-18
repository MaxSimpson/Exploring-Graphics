#ifndef _Camera_H_
#define _Camera_H_

#include <GL/glut.h>
class Camera {
	private:
		float g_theta{0.f};
	public:
		void Draw();
		void change_theta(float change);
		Camera();
		bool specialKeyPressed(GLint _key, GLint _x, GLint _y);
};

#endif
