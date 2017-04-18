#ifndef CAMERA_H
#define CAMERA_H

#include <stdio.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../io/Input.h"
#include "../geom/Transform.h"

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
    glm::vec4 planes[6];
    Camera();
    ~Camera();
    glm::mat4 GetView();
    void Translate(glm::vec3 movement);
    void LookVertical(float delta);
    void LookHorizontal(float delta);
    void LookAt(glm::vec3 target);
    bool WithinFrustum(glm::vec3 p1, glm::vec3 p2);
    void Update();
};

#endif
