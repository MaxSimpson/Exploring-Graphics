#ifndef _MODEL_H_
#define _MODEL_H_

// STL
#include <unordered_map>
#include <vector>
using namespace std;

// GL
#include "GLInclude.h"

// GLM
#include <glm/glm.hpp>

// Boost
#include <boost/functional/hash.hpp>

// Engine
class Material;

// First is index of point, second is index of normal, third is index of texture
using ObjVertex  = std::tuple<size_t, size_t, size_t>;

struct ObjFace {
  ObjVertex m_v[3];
};

struct Vertex {
  glm::vec3 m_point;
  glm::vec3 m_normal;
  glm::vec2 m_texture;
  Vertex(const glm::vec3& p, const glm::vec3& n, const glm::vec2& t) : m_point{p}, m_normal{n}, m_texture{t} {}
};

////////////////////////////////////////////////////////////////////////////////
/// @brief Class for model data
////////////////////////////////////////////////////////////////////////////////
class Model {
  public:
    ////////////////////////////////////////////////////////////////////////////
    /// @brief Constructor
    /// @param filename Filename of model data
    Model(const std::string& filename);

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Prints model data
    void Print_Data() const;

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Draws the model
    /// @param _program Shader program for drawing
    void Draw(GLuint _program) const;

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Setups 
    void Initialize();

  private:

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Parses model data
    /// @param filename Location of model data
    void Parse(const std::string& filename);

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Constructs VBO data
    void ConstructVBOData();

    std::vector<glm::vec3> m_points;   //< Obj point data
    std::vector<glm::vec3> m_normals;  //< Obj normal data
    std::vector<glm::vec2> m_textures; //< Obj texture coordinate data
    std::vector<ObjFace> m_faces;    //< Obj face data

    std::vector<Vertex> m_vertices; //< VBO data
    std::unordered_map<ObjVertex, size_t, boost::hash<ObjVertex>>
      m_vertexMap;                  //< Vertex to Index mapping
    std::vector<GLuint> m_indices;  //< EBO data

    GLuint m_vertexArrayObject; //< VAO
    GLuint m_vertexBuffer;  //< VBO object
    GLuint m_elementBuffer; //< EBO object

    Material* mat_ptr; //< Material reference
};

#endif
