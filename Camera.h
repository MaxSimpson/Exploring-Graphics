#ifndef _Camera_H_
#define _Camera_H_

class Camera {
	private:
		float g_theta{0.f};
	public:
		void draw();
		void change_theta(float change);
		Camera();
};

#endif
