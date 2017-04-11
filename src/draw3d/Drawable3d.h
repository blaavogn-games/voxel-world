#ifndef DRAWABLE3D_H
#define DRAWABLE3D_H


#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "../geom/Vector3.h"
#include "../geom/Transform.h"

class Drawable3d
{
  public:
	  Transform transform;
		Drawable3d() {};
		virtual ~Drawable3d(){};
    virtual void Draw(Camera camera, float time) = 0;
};

#endif
