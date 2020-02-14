#ifndef _BOXCOLLIDER_H_
#define _BOXCOLLIDER_H_

#include "Collider.h"

// STL
#include <vector>
using namespace std;

// GL
#include "GLInclude.h"
#define GL_EXT_PROTOTYPES
#include <GL/glut.h>

// GLM
#include <glm/glm.hpp>

////////////////////////////////////////////////////////////////////////////////
/// @brief Box collider for collision
////////////////////////////////////////////////////////////////////////////////
class BoxCollider{
  public:
  //////////////////////////////////////////////////////////////////////////////
  /// @brief Constructor
  BoxCollider();
  
  //////////////////////////////////////////////////////////////////////////////
  /// @brief Draws wireframe box collider
  void Draw();

  /// Buffer offset
  constexpr GLvoid* bufferOffset(size_t _off) {return (char*)NULL + _off;}

  ////////////////////////////////////////////////////////////////////////////
  /// @brief Setup for cube
  void Initialize();

  private:

  std::vector<glm::vec3> m_vertices; //< VBO data
  std::vector<GLuint> m_indices;  //< EBO data
  
  glm::vec3 Color = glm::vec3(0, 0, 0); //< Color for shader

  GLuint m_vertexArrayObject; //< VAO
  GLuint m_vertexBuffer;  //< VBO object
  GLuint m_elementBuffer; //< EBO object

};

#endif