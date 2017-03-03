#include "ColCircle.h"

ColCircle::ColCircle(const Vector2& position, const float inRadius) :
  Collider(position.x, position.y),
	_radius{inRadius},
  Radius(_radius){
}

ColCircle::~ColCircle(){}

void ColCircle::SetPosition(Vector2 newPosition){
  position = newPosition;
}

