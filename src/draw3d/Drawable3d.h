#ifndef DRAWABLE3D_H
#define DRAWABLE3D_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "../geom/Vector3.h"
#include "../geom/Transform.h"
#include "../shader/ShaderManager.h"

class Drawable3d
{
  protected:
    Shader *shader;
    static bool staticInitialized;
  public:
	  Transform transform;
		Drawable3d() {};
    virtual ~Drawable3d(){};
    void SetShader(const char *vertexPath, const char *fragmentPath){
      shader = ShaderManager::GetShader(vertexPath, fragmentPath);
    };
    virtual void Draw(float time) = 0;
};

#endif
