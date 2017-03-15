#ifndef DRAWABLE3D_H
#define DRAWABLE3D_H

#include "../geom/Vector3.h"

class Drawable3D
{
  protected:
    Vector3 position;
	public:
		Drawable(float x, float y, float z) : position(x,y,z){};
		virtual ~Drawable(){};
		virtual void Draw(float time) = 0;
    virtual void SetPosition(Vector3 pos) = 0;
		Vector3 GetPosition(){return position.Copy();};
};

#endif
