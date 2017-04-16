#include "Camera.h"

Camera::Camera() {
  // projection = glm::perspective(1.1f, 1366.0f/768.0f, 1.0f, 120.0f);
  projection = glm::perspective(1.1f, 1.0f, 1.0f, 120.0f);
  position = glm::vec3(0,0,0);
  front = glm::vec3(0,0,-1);
  up = glm::vec3(0,1,0);
}

Camera::~Camera() { }

void Camera::Translate(glm::vec3 movement){
  position += movement;
}

void Camera::LookVertical(float delta){
  pitch = glm::clamp(pitch + delta, -89.0f, 89.0f);
  ComputeDirFromPY();
}

void Camera::LookHorizontal(float delta){
  yaw = yaw + delta;
  ComputeDirFromPY();
}

void Camera::ComputeDirFromPY(){
  front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw)) + 0.0001f;
  front.y = sin(glm::radians(pitch));
  front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw)) - 0.0001f;
  front = glm::normalize(front);
}


void Camera::LookAt(glm::vec3 target){
  front = glm::normalize(target - position);
}

glm::mat4 Camera::GetView(){
  return glm::lookAt(position, position + front, up);
}

void Camera::Print(){
  printf("(%.1f, %.1f, %.1f)\n", front.x, front.y, front.z);
  printf("(%.1f, %.1f, %.1f)\n", position.x, position.y, position.z);
}
