#include "Scene.h"

#include <fstream>
#include <sstream>
using namespace std;

Scene::
Scene(const string& location){
	ifstream ifs(location);
	while(ifs) {
		string line;
		getline(ifs, line);

		istringstream iss(line);
		string tag;
		iss >> tag;
		if(tag == "start_object") {
			cout << "Reading object" << endl;
			models.emplace_back(make_unique<WorldModel>(ifs));
		}
		else if (tag == "") {
			// ignore
		}
		else {
			cerr << "Unknown tag from creating Scene: '" << tag << "'" << endl;
			exit(1);
		}
	}

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