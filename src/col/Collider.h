#ifndef COLLIDER_H
#define COLLIDER_H

#include "../geom/Vector2.h"

class Collider
{
  protected:
    Vector2 position;
  public:
    Collider(float x, float y) : position(x,y){};
		virtual ~Collider(){};
    Vector2 GetPosition() const {return position.Copy();};
};

#endif
