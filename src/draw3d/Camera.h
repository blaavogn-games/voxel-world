#ifndef CAMERA_H
#define CAMERA_H

#include "../geom/Transform.h"
#include <stdio.h>

class Camera
{
  private:
    Transform view;
  public:
    glm::vec3 position; //Should be able to extract this from view
    glm::mat4 projection;
    Camera();
    ~Camera();
    Transform GetView(){return view;};
    void Translate(glm::vec3 movement);
    void LookAt(glm::vec3 targer, glm::vec3 up);
};

#endif
