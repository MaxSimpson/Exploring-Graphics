//Includes
#include "WorldModel.h"

#include <fstream>
#include <sstream>
using namespace std;

// GL
#include <GL/glut.h>

//Contstructer
WorldModel::
WorldModel(std::ifstream& ifs){
	cout << "Constructor" << endl;
	while(ifs) {
		string line;
		getline(ifs, line);

		istringstream iss(line);
		string tag;
		iss >> tag;
		if(tag ==  "file_location") {
			cout << "Reading File Location" << endl;
			string location;
			iss >> location;
			model = std::make_unique<Model>(location);
		}
		else if(tag == "world_location") {
			cout << "Reading World Location" << endl;
			iss >> translation;
		}
		else if(tag == "color_rgb") {
			cout << "Reading Color RBG" << endl;
			iss >> color;
			color /= 255;
		}
		else if(tag == "end_object") {
			break;
		}
		else {
			cerr << "Unknown tag from creating WorldModel: '" << tag << "'" << endl;
			exit(1);
		}
	}
}

void
WorldModel::
Draw(){

	glPushMatrix();

	glColor3f(color.getX(), color.getY(), color.getZ());
	glTranslatef(translation.getX(), translation.getY(), translation.getZ());
	model->Draw();

	glPopMatrix();
}

void
WorldModel::
Print_Data(){
	model->Print_Data();
}