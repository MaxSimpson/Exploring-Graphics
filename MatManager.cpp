#include "MatManager.h"

// Constructor
MatManager::
MatManager(){

}

void
MatManager::
addMaterial(Material newMaterial){
  materials.emplace_back(newMaterial);
}