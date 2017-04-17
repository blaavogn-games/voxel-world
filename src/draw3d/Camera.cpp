#include "Camera.h"

Camera::Camera() {
  // projection = glm::perspective(1.1f, 1366.0f/768.0f, 1.0f, 120.0f);
  projection = glm::perspective(1.1f, 1.0f, 1.0f, 200.0f);
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
  glm::mat4 view = glm::lookAt(position, position + front, up);
  glm::mat4 cull = projection * view;
  row1 = glm::vec4(cull[0][0],cull[1][0],cull[2][0],cull[3][0]);
  row2 = glm::vec4(cull[0][1],cull[1][1],cull[2][1],cull[3][1]);
  row3 = glm::vec4(cull[0][2],cull[1][2],cull[2][2],cull[3][2]);
  row4 = glm::vec4(cull[0][3],cull[1][3],cull[2][3],cull[3][3]);
  return view;
}

bool Camera::WithinFrustum(glm::vec3 p1, glm::vec3 p2){
  return WithinFrustum(p1) || WithinFrustum(p2);
}

bool Camera::WithinFrustum(glm::vec3 point){
  glm::vec4 vertex = glm::vec4(point, 1.0f);

  return (glm::dot(vertex, (row4 + row1)) > 0) &&
         (glm::dot(vertex, (row4 - row1)) > 0) &&
         (glm::dot(vertex, (row4 + row2)) > 0) &&
         (glm::dot(vertex, (row4 - row2)) > 0) &&
         (glm::dot(vertex, (row4 + row3)) > 0) &&
         (glm::dot(vertex, (row4 - row3)) > 0);
}

void Camera::Print(){
  printf("(%.1f, %.1f, %.1f)\n", front.x, front.y, front.z);
  printf("(%.1f, %.1f, %.1f)\n", position.x, position.y, position.z);
}
