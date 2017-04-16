#ifndef CAMERA_H
#define CAMERA_H

#include "../geom/Transform.h"
#include <stdio.h>

class Camera
{
  private:
    float pitch, yaw;
    void ComputeDirFromPY();
  public:
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 position; //Should be able to extract this from view?
    glm::mat4 projection;
    Camera();
    ~Camera();
    glm::mat4 GetView();
    void Translate(glm::vec3 movement);
    void LookVertical(float delta);
    void LookHorizontal(float delta);
    void LookAt(glm::vec3 target);
    void Print();
};

#endif
