#ifndef _MATMANAGER_H_
#define _MATMANAGER_H_

// STL
#include <vector>

// My files
#include "Material.h"

////////////////////////////////////////////////////////////////////////////////
/// @brief Class for managing materials
////////////////////////////////////////////////////////////////////////////////
class MatManager{
  public:
    ////////////////////////////////////////////////////////////////////////////
    /// @brief Constructor for setup of material manager
    MatManager();

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Returns material to draw
    Material* getMaterial();

		// Make multiple materials
		void makeMaterials(std::string mat_location,
                       std::string tag,
                       std::string mat_name, int _counter);

  private:
    std::vector<std::unique_ptr<Material>> materials; //< Materials

};

#endif
