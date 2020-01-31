#include "SphereCollider.h"

SphereCollider::
SphereCollider(float _radius){
  // Set translation
  translation = glm::vec3(0, 0, 0);
  // Set radius
  radius = _radius;
  // Set type
  type = 0;
}

void
SphereCollider::
Update(glm::vec3 _translation){
  translation = _translation;
}

glm::vec3
SphereCollider::
CheckCollision(Collider _newCollider){
  return glm::vec3(0, 0, 0);
}

int
SphereCollider::
getType(){return 0;}