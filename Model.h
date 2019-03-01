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

struct ObjVertex {
  size_t m_p, m_t, m_n;
};

struct ObjFace {
  ObjVertex m_v[3];
};

struct Vertex {
  Vector3 m_point;
  Vector3 m_normal;
  Vector2 m_texture;
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
    using TriVert = std::tuple<size_t, size_t, size_t>;
    std::unordered_map<TriVert, size_t, boost::hash<TriVert>>
      m_vertexMap;                  // Vertex to Index mapping
    std::vector<GLuint> m_indices;  // EBO data

    GLuint m_vertexBuffer; // VBO object
    GLuint m_elementBuffer; // EBO object
};

#endif
