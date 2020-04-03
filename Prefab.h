#ifndef _PREFAB_H_
#define _PREFAB_H_

// Includes
#include <vector>
#include "Model.h"
#include "Material.h"

////////////////////////////////////////////////////////////////////////////////
/// @class Class for planet prefabs to be generated from
class Prefab {
  public:
    ////////////////////////////////////////////////////////////////////////////
    /// @brief Constructor
    Prefab();

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Setup and read in data
    void Initialize(const string location);
  private:
    std::vector<Model> models; //< Models for possible planets
    std::vector<Material> materials; //< List for materials
    //< File for weights of different models and materials
    string location; //< Folder with prefab data

};

#endif