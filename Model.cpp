#include "Model.h"

// STL
#include <cstdio>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

Model::
Model(std::string filename) {
  //Next Line
  std::string line;
  //Setup Input stream
  std::ifstream ifs{filename};
  while(getline(ifs, line)) {
    std::string tag;
    std::istringstream iss{line};
    iss >> tag;

    if(tag == "v") {
      std::cout<<"Point";
      Vector3 v;
      iss >> v;
      m_points.emplace_back(v);
    }

    else if(tag == "vt") {
      std::cout<<"Texture";
      Vector2 v;
      iss >> v;
      m_textures.emplace_back(v);
    }

    else if(tag == "vn") {
      std::cout<<"Normal";
      Vector3 v;
      iss >> v;
      m_normals.emplace_back(v);
    }

    else if(tag == "f") {
      std::cout<<"Face";
      Face f;
      for(size_t i = 0; i < 3; ++i) {
        Vertex v;
        string vert;
        iss >> vert;
        std::sscanf(vert.c_str(), "%zu/%zu/%zu", &v.m_p, &v.m_t, &v.m_n);
        f.m_v[i] = v;
      }
      m_faces.emplace_back(f);
    }
    else {
    }
  }
}
