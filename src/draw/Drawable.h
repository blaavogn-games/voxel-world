#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "../geom/Vector2.h"

class Drawable
{
	public:
		Drawable(){};
		virtual ~Drawable(){};
		virtual void Draw(float time) = 0;
		virtual void SetPosition(Vector2 pos) = 0;
};
  
#endif