#ifndef COLLIDER_H
#define COLLIDER_H

#include "../geom/Vector2.h"

class Collider
{
	public:
		Collider(){};
		virtual ~Collider(){};
		virtual void SetPosition(Vector2 pos) = 0;
};
  
#endif