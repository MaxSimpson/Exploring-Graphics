#ifndef _PREFAB_H_
#define _PREFAB_H_

// Includes
#include <vector>

////////////////////////////////////////////////////////////////////////////////
/// @class Class for planet prefabs to be generated from
class Prefab {
  public:
    ////////////////////////////////////////////////////////////////////////////
    /// @brief Class for creating list of models, shader programs, and weights
    Prefab();
  private:
    std::vector<Model> models; //< Models for possible planets
    //< List for shader programs

}

#endif