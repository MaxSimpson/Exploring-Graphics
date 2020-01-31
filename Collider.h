#ifndef _COLLIDER_H_
#define _COLLIDER_H_

// GL/GLM
#include "GLInclude.h"

class Collider {
  public:
    virtual void Update(glm::vec3 _translation);
    virtual glm::vec3 checkCollision(Collider _newCollider);

  protected:
    glm::vec3 translation;
    int type;
};

#endif