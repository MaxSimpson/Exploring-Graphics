#include "BoxCollider.h"

// Includes
using namespace std;

// GL
#define GL_EXT_PROTOTYPES
#include <GL/glut.h>

//GLM
#include "GLInclude.h"

BoxCollider::
BoxCollider(){

}

void
BoxCollider::
Draw(GLuint _program, const glm::mat4& _projection, const glm::mat4& _view){
	glm::mat4 mv = _view;
	glm::mat4 itmv = glm::transpose(glm::inverse(mv));
	glm::mat4 mvp = _projection * mv;

	GLuint mvIndex = glGetUniformLocation(_program, "mv");
    glUniformMatrix4fv(mvIndex, 1, GL_FALSE, &mv[0][0]);

	GLuint itmvIndex = glGetUniformLocation(_program, "itmv");
    glUniformMatrix4fv(itmvIndex, 1, GL_FALSE, &itmv[0][0]);

	GLuint mvpIndex = glGetUniformLocation(_program, "mvp");
    glUniformMatrix4fv(mvpIndex, 1, GL_FALSE, &mvp[0][0]);

  glBindVertexArray(m_vertexArrayObject);
  glDrawElements(GL_LINES, GLsizei(m_indices.size()),
                 GL_UNSIGNED_INT, bufferOffset(0));
  glBindVertexArray(0);
}

void
BoxCollider::
Initialize(){
  // Generate data
  // Points
  m_vertices.emplace_back(glm::vec3( 1,  1,  1)); // 0
  m_vertices.emplace_back(glm::vec3( 1,  1, -1)); // 1
  m_vertices.emplace_back(glm::vec3(-1,  1,  1)); // 2
  m_vertices.emplace_back(glm::vec3(-1,  1, -1)); // 3
  m_vertices.emplace_back(glm::vec3( 1, -1,  1)); // 4
  m_vertices.emplace_back(glm::vec3( 1, -1, -1)); // 5
  m_vertices.emplace_back(glm::vec3(-1, -1,  1)); // 6
  m_vertices.emplace_back(glm::vec3(-1, -1, -1)); // 7
  // Top 1
  m_indices.emplace_back(0);
  m_indices.emplace_back(1);
  m_indices.emplace_back(0);
  m_indices.emplace_back(2);
  // Top 2
  m_indices.emplace_back(3);
  m_indices.emplace_back(1);
  m_indices.emplace_back(3);
  m_indices.emplace_back(2);
  // Bottom 1
  m_indices.emplace_back(4);
  m_indices.emplace_back(5);
  m_indices.emplace_back(4);
  m_indices.emplace_back(6);
  // Bottom 2
  m_indices.emplace_back(7);
  m_indices.emplace_back(5);
  m_indices.emplace_back(7);
  m_indices.emplace_back(6);
  // Top bottom connectors
  m_indices.emplace_back(0);
  m_indices.emplace_back(4);
  m_indices.emplace_back(1);
  m_indices.emplace_back(5);
  m_indices.emplace_back(2);
  m_indices.emplace_back(6);
  m_indices.emplace_back(3);
  m_indices.emplace_back(7);

  // Points
  //  1  1  1
  //  1  1 -1
  // -1  1  1
  // -1  1 -1

  //  1 -1 -1
  // -1 -1  1
  // -1 -1  1
  //  1 -1 -1

  // Vertex buffer object on vertices
  glGenBuffers(1, &m_vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*m_vertices.size(),
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

  // Just points (no normals or texture cords)
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                        sizeof(glm::vec3), bufferOffset(0));
  glBindVertexArray(0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}
