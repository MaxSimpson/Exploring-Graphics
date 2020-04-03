#include "Prefab.h"

#include <iostream>

using namespace std;

Prefab::
Prefab(){}

void
Prefab::
Initialize(const string _location){
  location = _location;

  // Read in files in directory
  std::vector<string> files; // Add names to list as reading them in

  // Read in data from files
  for(int i = 0; i < files.size(); i++){
    if(files[i][files[i].size()] == 'j'){ // Read obj
      
    }else if (files[i][files[i].size()] == 'l'){ // Read materials

    }else{
      cerr << "Unknown file in " << location << endl;
    }
  }

}

