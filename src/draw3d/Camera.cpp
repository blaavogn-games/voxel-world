#include "Camera.h"

Camera::Camera() {
  projection = glm::perspective(45.0f, 1.0f, 1.0f, 120.0f);
}

Camera::~Camera() {
}

void Camera::Translate(glm::vec3 movement){
  position += movement;
  view.Translate(movement);
}

void Camera::LookAt(glm::vec3 target, glm::vec3 up){
  view = glm::lookAt(position, target, up);
}
