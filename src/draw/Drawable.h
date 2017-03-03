#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "../geom/Vector2.h"

class Drawable
{
  protected:
    Vector2 position;
	public:
		Drawable(float x, float y) : position(x,y){};
		virtual ~Drawable(){};
		virtual void Draw(float time) = 0;
    virtual void SetPosition(Vector2 pos) = 0;
		Vector2 GetPosition(){return position.Copy();};
};

#endif
