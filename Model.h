#ifndef _MODEL_H_
#define _MODEL_H_

// STL
#include <unordered_map>
#include <vector>
//using namespace std;

// My program
#include "Vector.h"

// GL
#include "GLInclude.h"

// Boost
#include <boost/functional/hash.hpp>

// First is index of point, second is index of normal, third is index of texture
using ObjVertex  = std::tuple<size_t, size_t, size_t>;

struct ObjFace {
  ObjVertex m_v[3];
};

struct Vertex {
  Vector3 m_point;
  Vector3 m_normal;
  Vector2 m_texture;

  Vertex(const Vector3& p, const Vector3& n, const Vector2& t) : m_point{p}, m_normal{n}, m_texture{t} {}
};

class Model {
  public:

    Model(const std::string& filename);

    void Print_Data() const;
    void Draw() const;
    void Initialize();

  private:

    void Parse(const std::string& filename);
    void ConstructVBOData();

    std::vector<Vector3> m_points;   // Obj point data
    std::vector<Vector3> m_normals;  // Obj normal data
    std::vector<Vector2> m_textures; // Obj texture coordinate data
    std::vector<ObjFace> m_faces;    // Obj face data

    std::vector<Vertex> m_vertices; // VBO data
    std::unordered_map<ObjVertex, size_t, boost::hash<ObjVertex>>
      m_vertexMap;                  // Vertex to Index mapping
    std::vector<GLuint> m_indices;  // EBO data

    GLuint m_vertexBuffer;  // VBO object
    GLuint m_elementBuffer; // EBO object
};

#endif
