//Includes
#include "WorldModel.h"

//Contstructer
WorldModel::
WorldModel(const std::string& location){
	model = std::make_unique<Model>(location);
}

void
WorldModel::
Draw(){
	model->Draw();
}

void
WorldModel::
Print_Data(){
	model->Print_Data();
}