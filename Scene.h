#ifndef _SCENE_H_
#define _SCENE_H_

#include "Camera.h"
#include "Light.h"

class Scene {
	public:
		Scene();
		Camera camera;
		Light light;
};

#endif
