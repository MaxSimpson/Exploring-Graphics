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
	int important_data = 0;
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
			important_data = important_data + 1;
		}
		else if(tag == "world_location") {
			cout << "Reading World Location" << endl;
			iss >> translation;
		}
		else if(tag == "color_rgb") {
			cout << "Reading Color RBG" << endl;
			iss >> color;
			color /= 255;
		}else if (tag == "world_scale"){
			cout << "Reading Scale" << endl;
			iss >> scale;
			important_data += 1;
		}else if (tag == "world_rotation"){
			cout << "Reading rotation" << endl;
			iss >> angle;
			cout << "Angle: " << angle << endl;
			iss >> rotation_axis;
			rotation_axis = rotation_axis.normalize();
			cout << "Rotation Axis: " << rotation_axis << endl;
			important_data += 1;
		}else if (tag[0] == '#'){

		}else if(tag == "end_object") {
			if(important_data < 3){
				cout << important_data << endl;
				cout << "Model is missing data ex: file, scale, rotation" << endl;
				exit(1);
			}
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
Initialize() {
	model->Initialize();
}

void
WorldModel::
Draw(){

	//Start
	glPushMatrix();
	//Color
	glColor3f(color.getX(), color.getY(), color.getZ());

	//Translate
	glTranslatef(translation.getX(), translation.getY(), translation.getZ());

    //Rotate
	//glRotatef(getAngle(), rotation_axis.getX(), rotation_axis.getY(), rotation_axis.getZ());

	//Scale
	glScalef(scale.getX(), scale.getY(), scale.getZ());
	
	model->Draw();
	//End
	glPopMatrix();
}

float 
WorldModel::
getAngle()const { return angle;}

void
WorldModel::
Print_Data(){
	model->Print_Data();
}