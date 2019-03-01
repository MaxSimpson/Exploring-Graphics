#ifndef _MODEL_H_
#define _MODEL_H_

// STL
#include <vector>
//using namespace std;

// My program
#include "Vector.h"

struct Vertex {
  size_t m_p, m_t, m_n;
};

struct Face {
  Vertex m_v[3];
};

class Model {
  public:
    
    
    #ifndef GL_WITHOUT_SHADERS
      void draw();
    #elif defined (GL_WITH_SHADERS)
      void draw(GLuint _program);
    #endif
    
    Model(const std::string& filename);

    std::vector<Vector3> m_points;
    std::vector<Vector3> m_normals;
    std::vector<Vector2> m_textures;
    std::vector<Face> m_faces;

    

    void Print_Data() const;
    void Draw() const;
    void Initialize();
};

#endif
