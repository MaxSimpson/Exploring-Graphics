#include "Scene.h"

using namespace std;

Scene::
Scene(const string& location){
    model = make_unique<Model>(location);
    //When Making model give normal
    //then vertex
    model->print_data();
}

void
Scene::
Draw(){
    camera.Draw();
    light.Draw();

    model->draw();
}

bool
Scene::
specialKeyPressed(GLint _key, GLint _x, GLint _y) {
    return camera.specialKeyPressed(_key, _x, _y);
}