#ifndef _MODEL_H_
#define _MODEL_H_

// STL
#include <vector>

// My program
#include "Vector.h"

struct Vertex {
  size_t m_p, m_t, m_n;
};
// m->m_faces(m_v(m_n))
struct Face {
  Vertex m_v[3];
};

class Model {
  public:
    Model(std::string filename);

    std::vector<Vector3> m_points;
    std::vector<Vector3> m_normals;
    std::vector<Vector2> m_textures;
    std::vector<Face> m_faces;



};

#endif
