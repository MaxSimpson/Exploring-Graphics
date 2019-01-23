#ifndef _WorldModel_H_
#define _WorldModel_H_

//Includes
#include "Vector.h"
#include "Model.h"

#include <memory>

class WorldModel{
	public:
		WorldModel(const std::string& location);
		void Draw();	
		void Print_Data();
	private:
		Vector3 Translation();
		Vector3 Scale();
		Vector3 Rotation();
		std::unique_ptr<Model> model; 
};

#endif