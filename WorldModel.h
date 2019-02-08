#ifndef _WorldModel_H_
#define _WorldModel_H_

//Includes
#include "Vector.h"
#include "Model.h"

#include <memory>

class WorldModel{
	public:
		WorldModel(std::ifstream& ifs);
		void Draw();	
		void Print_Data();
		float getAngle() const;
	private:
		Vector3 translation;
		Vector3 scale;
		float angle;
		Vector3 rotation_axis;
		Vector3 color;
		std::unique_ptr<Model> model; 
};

#endif