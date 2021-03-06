//Includes
#include "WorldModel.h"

#include <fstream>
#include <sstream>
using namespace std;

#include <iostream>

// GL
#include "GLInclude.h"

// Constructer
WorldModel::
WorldModel(ifstream& ifs){
	// cout << "Constructor" << endl;
  // Read data
	int important_data = 0;
	int material = 0;
	while(ifs) {
		string line;
		getline(ifs, line);

		istringstream iss(line);
		string tag;
		iss >> tag;
		if(tag ==  "file_location") {
			// cout << "Reading File Location" << endl;
			string location;
			iss >> location;
			important_data = important_data + 1;
      model = make_unique<Model>(location);
		}else if(tag == "world_location") {
			// cout << "Reading World Location" << endl;
			iss >> translation.x;
			iss >> translation.y;
			iss >> translation.z;

		}else if(tag == "color_rgb") {
			// cout << "Reading Color RBG" << endl;
			iss >> color.x;
			iss >> color.y;
			iss >> color.z;
			color /= 255;
		}else if (tag == "world_scale"){
			// cout << "Reading Scale" << endl;
			iss >> scale.x;
			iss >> scale.y;
			iss >> scale.z;
			important_data += 1;
		}else if (tag == "world_rotation"){
			// cout << "Reading rotation" << endl;
			iss >> angle;
			// cout << "Angle: " << angle << endl;
			iss >> rotation_axis.x;
			iss >> rotation_axis.y;
			iss >> rotation_axis.z;
			glm::normalize(rotation_axis);
			// cout << "Rotation Axis: " << rotation_axis.x << " " << rotation_axis.y
				 								// << " " << rotation_axis.z << endl;
			important_data += 1;
    }else if (tag == "physics"){
      iss >> physicsOn;
    }else if(tag == "sphereCollider"){
      float _radius;
      iss >> _radius;
      // cout << "Adding sphere collider with radius of " << _radius << endl;
      // collider = SphereCollider(_radius);
    }else if(tag == "boxCollider"){
      // collider = BoxCollider();
		}else if (tag[0] == '#'){
			// Comment
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
  collider.Initialize();
}

void
WorldModel::
Update(float _dt,
       const std::vector<std::unique_ptr<WorldModel>>& _models) {
  // Set collider translation
  collider.Update(translation, rotation_axis, angle, scale);

  // Save old values
  glm::vec3 old_translation = translation;
  glm::vec3 old_velocity = velocity;

  // Do physics
  Physics(_dt);

  // Check collision
  if(CollidesWith(_models)) {
    translation = old_translation;
    velocity = old_velocity;
  }
}

void
WorldModel::
Draw(GLuint _program, const glm::mat4& _projection, const glm::mat4& _view) {

  glm::mat4 t = glm::translate(glm::mat4(1.f), translation);
	glm::mat4 r = glm::rotate(glm::mat4(1.f), angle, rotation_axis);
	glm::mat4 s = glm::scale(glm::mat4(1.f), scale);
	glm::mat4 m = t*r*s;

	glm::mat4 mv = _view * m;
	glm::mat4 itmv = glm::transpose(glm::inverse(mv));
	glm::mat4 mvp = _projection * mv;

	GLuint mvIndex = glGetUniformLocation(_program, "mv");
    glUniformMatrix4fv(mvIndex, 1, GL_FALSE, &mv[0][0]);

	GLuint itmvIndex = glGetUniformLocation(_program, "itmv");
    glUniformMatrix4fv(itmvIndex, 1, GL_FALSE, &itmv[0][0]);

	GLuint mvpIndex = glGetUniformLocation(_program, "mvp");
    glUniformMatrix4fv(mvpIndex, 1, GL_FALSE, &mvp[0][0]);

	GLuint colorIndex = glGetUniformLocation(_program, "color");
    glUniform3fv(colorIndex, 1, &color[0]);

  model->Draw(_program);
  collider.Draw(_program, _projection, _view);
}

float
WorldModel::
getAngle()const {return angle;}

void
WorldModel::
Print_Data(){
}

void
WorldModel::
Physics(float _dt) {
	if(physicsOn){
    // Apply forces
    // F = ma  --> a = F/m
    glm::vec3 force = -glm::vec3(0, gravity, 0)/* * mass */;
    glm::vec3 acceleration = force /* / mass */;

    // Update positions
    velocity += _dt * acceleration;
    translation += _dt * velocity; // Should really use old velocity
  }
}

bool
WorldModel::
CollidesWith(const std::vector<std::unique_ptr<WorldModel>>& _models) {
  for(auto& m : _models) {
    if(this != m.get()) {
      // check box to box collision
      if(collider.CollidesWith(m->collider))
        return true;
    }
  }
  if (translation.y < -5){
    return true;
  }
  return false;
}

bool
WorldModel::
getPhysicsOn(){return physicsOn;}
