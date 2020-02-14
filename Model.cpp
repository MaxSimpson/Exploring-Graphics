#include "Model.h"

// STL
#include <cstdio>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

// GL
#define GL_EXT_PROTOTYPES
#include <GL/glut.h>

//GLM
#include "GLInclude.h"

#include "MatManager.h"

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
    cout << "\t" << m_faces.size() << " faces" << endl;
  */
}

constexpr GLvoid* bufferOffset(size_t _off) {return (char*)NULL + _off;}

void
Model::
Draw(GLuint _program) const {
  mat_ptr->Draw(_program);

  glBindVertexArray(m_vertexArrayObject);
  glDrawElements(GL_TRIANGLES, GLsizei(m_indices.size()),
                 GL_UNSIGNED_INT, bufferOffset(0));
  glBindVertexArray(0);
}


void
Model::
Initialize() {
  // Vertex buffer object on vertices
  glGenBuffers(1, &m_vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*m_vertices.size(),
               m_vertices.data(), GL_STATIC_DRAW);

  // Vertex array object - will store state of vertex buffer + attributes. For
  // sending to shader. We split the data to separate attributes for shaders.
  glGenVertexArrays(1, &m_vertexArrayObject);
  glBindVertexArray(m_vertexArrayObject);

  // Create EBO on the GPU and send CPU data to the GPU for triangle indices
  glGenBuffers(1, &m_elementBuffer);               // Create EBO name on the GPU
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer); // Make our new EBO the active ELEMENT_ARRAY_BUFFER
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*m_indices.size(),
    m_indices.data(), GL_STATIC_DRAW);             // Send index data to EBO on the GPU

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                        sizeof(Vertex), bufferOffset(0));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                        sizeof(Vertex), bufferOffset(sizeof(glm::vec3)));
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
                       sizeof(Vertex), bufferOffset(2*sizeof(glm::vec3)));

  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
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
      //cout << "Reading Point" << endl;
      glm::vec3 v;
      iss >> v.x;
      iss >> v.y;
      iss >> v.z;
      m_points.emplace_back(v);
    } else if(tag == "vt") {
      //cout << "Reading Texture" << endl;
      glm::vec2 v;
      iss >> v.x;
      iss >> v.y;
      m_textures.emplace_back(v);
    } else if(tag == "vn") {
      //cout << "Reading Normal" << endl;
      glm::vec3 v;
      iss >> v.x;
      iss >> v.y;
      iss >> v.z;
      m_normals.emplace_back(v);
    } else if(tag == "f") {
      //cout << "Reading Face" << endl;
      ObjFace f;
      for(size_t i = 0; i < 3; ++i) {
        ObjVertex v;
        string vert;
        iss >> vert;
        if(std::sscanf(vert.c_str(), "%zu/%zu/%zu", &get<0>(v), &get<2>(v), &get<1>(v)) == 3) {
          --get<0>(v); --get<2>(v); --get<1>(v);
        }
        else if(std::sscanf(vert.c_str(), "%zu//%zu", &get<0>(v), &get<1>(v)) == 2) {
          --get<0>(v); --get<1>(v);
        } else {
          cerr << "Error: Unknown face format with OBJ." << endl;
          exit(1);
        }
        f.m_v[i] = v;
      }
      m_faces.emplace_back(f);
    } else if(tag == "mtllib") {
      string filename;
      iss >> filename;
      string dir = "ModelFiles";
      string mtlfilename = dir + "/" + filename;
      getMatManager().makeMaterials(mtlfilename);
    } else if(tag == "usemtl") {
      string mat_name;
      iss >> mat_name;
      mat_ptr = getMatManager().getMaterial(mat_name);
    } else {
    }
  }
  if(m_textures.empty())
    m_textures.emplace_back(0, 0);
}


void
Model::
ConstructVBOData() {
  // for each ObjFace do
  for(auto& oface : m_faces) {
    //   for each ObjVertex v of ObjFace do
    for(auto& overtex : oface.m_v) {
      //     if v does not exist in vertexMap then   {Use count method}
      if(m_vertexMap.count(overtex) == 0){
        //       add v to VBO data and the vertexMap   {Use emplace_back and emplace}
        m_vertices.emplace_back(m_points[get<0>(overtex)], m_normals[get<1>(overtex)], m_textures[get<2>(overtex)]);
        //cout << "Vertex: " << m_vertices.back().m_point << endl;
        m_vertexMap.emplace(overtex, m_vertices.size() - 1);
      }
      //     add v to EBO data                       {Use emplace_back}

      m_indices.emplace_back(m_vertexMap[overtex]);
      //cout << "Index: " << m_indices.back() << endl;
    }
  }

  cout << "Vertex size: " << m_vertices.size() << endl;
  cout << "Element size: " << m_indices.size() << endl;
}
