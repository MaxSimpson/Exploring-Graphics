#include "Scene.h"

using namespace std;

Scene::
Scene(const string& location){
	//Create Model NOTE: MAKE INTO VECTOR LATER
    //models = std::vector<make_unique<WorldModel>>;

	Add_Model(location);

	//Make for loop print data
	for(int i = 0; i < models.size(); i++){
		models[i]->Print_Data();
	}		
    
}

void
Scene::
Draw(){
    camera.Draw();
    light.Draw();

    for(int i = 0; i < models.size(); i++){
    		models[i]->Draw();
    }
}

bool
Scene::
specialKeyPressed(GLint _key, GLint _x, GLint _y) {
    return camera.specialKeyPressed(_key, _x, _y);
}

void
Scene::
Add_Model(const string& location){
	models.emplace_back(make_unique<WorldModel>(location));
}