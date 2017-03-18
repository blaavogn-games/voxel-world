#ifndef DRAWABLE3D_H
#define DRAWABLE3D_H

#include "../geom/Vector3.h"

class Drawable3d
{
  protected:
    Vector3 position;
	public:
		Drawable3d(float x, float y, float z) : position(x,y,z){};
		virtual ~Drawable3d(){};
		virtual void Draw(float time) = 0;
    virtual void SetPosition(Vector3 pos) = 0;
    virtual void Move(Vector3 pos) = 0;
		Vector3 GetPosition(){return position.Copy();};
};

#endif
