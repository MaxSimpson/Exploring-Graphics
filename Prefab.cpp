#include "Prefab.h"

#include <algorithm>
#include <locale>

#include <iostream>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

using namespace std;

Prefab::
Prefab(){}

void
Prefab::
Initialize(const string _location){
  location = _location;

  // Read in files in directory
  std::vector<string> files; // Add names to list as reading them in
  for(const auto & entry : fs::directory_iterator(location))
    files.emplace_back(entry.path());

  

  // Read in data from files
  for(int i = 0; i < files.size(); i++){
    cout << "Files of I " << files[i] << endl;
    const string& f = files[i];
    size_t di = f.rfind(".");
    string ext = f.substr(di);
    transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    cout << "EXT: " << ext << endl;
    if(ext == ".obj"){ // Read obj
      // models.emplace_back(new Model(files[i]));
    }else if (ext == ".mtl"){ // Read materials
      // materials.emplace_back(new Material(files[i]));
    }else{
      cerr << "Unknown file in " << files[i] << endl;
    }
  }

}

Model
Prefab::
getModel(){
  // for 
}
