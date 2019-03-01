#include "Model.h"

// STL
#include <cstdio>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

// GL
#define GL_EXT_PROTOTYPES
#include <GL/glut.h>

Model::
Model(const std::string& filename) {
  Parse(filename);
  ConstructVBOData();
}

void
Model::
Print_Data() const {

  cout << "Model contains: " << endl;
  cout << "\t Points: " << m_points.size() << endl;
  cout << "\t Normals: " << m_normals.size() << endl;
  cout << "\t Textures: " << m_textures.size() << endl;

  //Annoying with larger models
  /*cout << "Model contains:" << endl;
    cout << "\t" << m_points.size() << " points:" << endl;
    for(auto& p : m_points)
    cout << "\t\tPoint: " << p << endl;
    cout << "\t" << m_normals.size() << " normals:" << endl;
    for(auto& n : m_normals)
    cout << "\t\tNormal: " << n << endl;
    cout << "\t" << m_textures.size() << " textures:" << endl;
    for(auto& t : m_textures)
    cout << "\t\tTexture: " << t << endl;
    cout << "\t" << m_faces.size() << " faces" << endl; */

}

void
Model::
Draw() const {
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  glBegin(GL_TRIANGLES);

    for(auto& face : m_faces) {
      for(auto& vertex : face.m_v) {
        const Vector3& n = m_normals[vertex.m_n];
        glNormal3f(n.getX(), n.getY(), n.getZ());
        const Vector3& v = m_points[vertex.m_p];
        glVertex3f(v.getX(), v.getY(), v.getZ());
      }
    }

  glEnd();
}

constexpr GLvoid* bufferOffset(size_t _off) {return (char*)NULL + _off;}

void
Model::
Initialize() {
  glGenBuffers(1, &m_vertexBuffer);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, sizeof(Vertex),bufferOffset(0));

  glEnableClientState(GL_NORMAL_ARRAY);
  glNormalPointer(GL_FLOAT, sizeof(Vertex), bufferOffset(12));

  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), bufferOffset(24));
}

void
Model::
Parse(const std::string& filename) {
  //Next Line
  std::string line;
  //Setup Input stream
  std::ifstream ifs{filename};
  while(getline(ifs, line)) {
    std::string tag;
    std::istringstream iss{line};
    iss >> tag;

    if(tag == "v") {
      Vector3 v;
      iss >> v;
      m_points.emplace_back(v);
    }

    else if(tag == "vt") {
      Vector2 v;
      iss >> v;
      m_textures.emplace_back(v);
    }

    else if(tag == "vn") {
      Vector3 v;
      iss >> v;
      m_normals.emplace_back(v);
    }

    else if(tag == "f") {
      ObjFace f;
      for(size_t i = 0; i < 3; ++i) {
        ObjVertex v;
        string vert;
        iss >> vert;
        if(std::sscanf(vert.c_str(), "%zu/%zu/%zu", &v.m_p, &v.m_t, &v.m_n) == 3) {
          --v.m_p; --v.m_t; --v.m_n;
        }
        else if(std::sscanf(vert.c_str(), "%zu//%zu", &v.m_p, &v.m_n) == 2) {
          --v.m_p; --v.m_n;
        }
        else {
          cerr << "Error: Unknown face format with OBJ." << endl;
          exit(1);
        }
        f.m_v[i] = v;
      }
      m_faces.emplace_back(f);
    }
    else {
    }
  }
}


void
Model::
ConstructVBOData() {
  // for each ObjFace do
  //   for each ObjVertex v of ObjFace do
  //     if v does not exist in vertexMap then   {Use count method}
  //       add v to VBO data and the vertexMap   {Use emplace_back and emplace}
  //     add v to EBO data                       {Use emplace_back}
}
