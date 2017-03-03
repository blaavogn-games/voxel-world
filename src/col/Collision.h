#ifndef COLLISION_H
#define COLLISION_H

#include "../geom/Vector2.h"

struct Collision
{
  bool collides;
  Vector2 point;
  static const Collision NoCol;
  Collision(bool collides, Vector2 point) : collides{collides}, point{point}{};
};

#endif
