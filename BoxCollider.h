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
  /// @brief Updates transforms
  void Update(glm::vec3 _translation, glm::vec3 _rotation, float rotation_axis,
              glm::vec3 _scale);

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Draws wireframe box collider
  void Draw(GLuint _program, const glm::mat4& _projection, const glm::mat4& _view);

  /// Buffer offset
  constexpr GLvoid* bufferOffset(size_t _off) {return (char*)NULL + _off;}

  ////////////////////////////////////////////////////////////////////////////
  /// @brief Setup for cube
  void Initialize();

  //////////////////////////////////////////////////////////////////////////////
  /// @brief Sets outer bounds for collision
  void SetBounds();

  bool CollidesWith(const BoxCollider& _other);

  private:

  std::vector<glm::vec3> m_vertices; //< VBO data
  std::vector<GLuint> m_indices;  //< EBO data

  glm::vec3 Color = glm::vec3(0, 0, 0); //< Color for shader

  glm::vec3 MinPoint = glm::vec3(-1, -1, -1); //< Min bounds
  glm::vec3 MaxPoint = glm::vec3(1, 1, 1); //< Max bounds

  // Parent data
  glm::vec3 Translation;
  glm::vec3 Rotation;
  float Angle;
  glm::vec3 Scale;

  GLuint m_vertexArrayObject; //< VAO
  GLuint m_vertexBuffer;  //< VBO object
  GLuint m_elementBuffer; //< EBO object

};

#endif
