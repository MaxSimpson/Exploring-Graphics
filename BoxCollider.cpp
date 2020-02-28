#include "BoxCollider.h"

// Includes
#include <iostream>
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
Update(glm::vec3 _translation, glm::vec3 _rotation, float rotation_axis,
       glm::vec3 _scale){
  Translation = _translation;
  Rotation = _rotation;
  Angle = rotation_axis;
  Scale = _scale;

  glm::mat4 t = glm::translate(glm::mat4(1.f), Translation);
	glm::mat4 r = glm::rotate(glm::mat4(1.f), Angle, Rotation);
	glm::mat4 s = glm::scale(glm::mat4(1.f), Scale);
	glm::mat4 m = t*r*s;

  glm::vec3 minP{(m*glm::vec4(MaxPoint, 1))};
  glm::vec3 maxP{(m*glm::vec4(MaxPoint, 1))};
  MinPoint = minP;
}

void
BoxCollider::
Draw(GLuint _program, const glm::mat4& _projection, const glm::mat4& _view){
  glm::mat4 t = glm::translate(glm::mat4(1.f), Translation);
	glm::mat4 r = glm::rotate(glm::mat4(1.f), Angle, Rotation);
	glm::mat4 s = glm::scale(glm::mat4(1.f), Scale);
	glm::mat4 m = t*r*s;

	glm::mat4 mv = _view * m;
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
SetBounds(){
  for(int i = 0; i < m_vertices.size(); i++){
    if(m_vertices[i].x > MaxPoint.x){
      MaxPoint.x = m_vertices[i].x;
    }else if(m_vertices[i].x < MinPoint.x){
      MinPoint.x = m_vertices[i].x;
    }else if(m_vertices[i].y > MaxPoint.y){
      MaxPoint.y = m_vertices[i].y;
    }else if(m_vertices[i].y < MinPoint.y){
      MinPoint.y = m_vertices[i].y;
    }
  }
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

bool
BoxCollider::
CollidesWith(const BoxCollider& _other) {
  // Compute the locations of each box extent
  // Determine overlap
  return !(MaxPoint.x < _other.MinPoint.x || MaxPoint.y < _other.MinPoint.y ||
    MinPoint.x > _other.MaxPoint.x || MinPoint.y > _other.MaxPoint.y);
}
