#include "Camera.h"

Camera::Camera() {
  // projection = glm::perspective(1.1f, 1366.0f/768.0f, 1.0f, 120.0f);
  projection = glm::perspective(1.3f, 1.0f, 0.2f, 120.0f);
  position = glm::vec3(0,2,0);
  front = glm::vec3(0,0,-1);
  up = glm::vec3(0,1,0);
  velosity = 0;
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

// Extracting frstum planes
// http://gamedevs.org/uploads/fast-extraction-viewing-frustum-planes-from-world-view-projection-matrix.pdf
glm::mat4 Camera::GetView(){
  glm::vec3 target = position + front;
  //Posibly check whether target and position are aligned on two axis
  glm::mat4 view = glm::lookAt(position, target, up);
  glm::mat4 cull = projection * view;
  planes[0].x = cull[0][3] + cull[0][0]; //left
  planes[0].y = cull[1][3] + cull[1][0];
  planes[0].z = cull[2][3] + cull[2][0];
  planes[0].w = cull[3][3] + cull[3][0];
  planes[1].x = cull[0][3] - cull[0][0]; //right
  planes[1].y = cull[1][3] - cull[1][0];
  planes[1].z = cull[2][3] - cull[2][0];
  planes[1].w = cull[3][3] - cull[3][0];
  planes[2].x = cull[0][3] + cull[0][1]; //bottom
  planes[2].y = cull[1][3] + cull[1][1];
  planes[2].z = cull[2][3] + cull[2][1];
  planes[2].w = cull[3][3] + cull[3][1];
  planes[3].x = cull[0][3] - cull[0][1]; //top
  planes[3].y = cull[1][3] - cull[1][1];
  planes[3].z = cull[2][3] - cull[2][1];
  planes[3].w = cull[3][3] - cull[3][1];
  planes[4].x = cull[0][3] + cull[0][2]; //near
  planes[4].y = cull[1][3] + cull[1][2];
  planes[4].z = cull[2][3] + cull[2][2];
  planes[4].w = cull[3][3] + cull[3][2];
  planes[5].x = cull[0][3] - cull[0][2]; //far
  planes[5].y = cull[1][3] - cull[1][2];
  planes[5].z = cull[2][3] - cull[2][2];
  planes[5].w = cull[3][3] - cull[3][2];
  return view;
}

// Partly usin https://doc.lagout.org/Others/Game%20Development/Programming/Graphics%20Gems%204.pdf
// page 84
bool Camera::WithinFrustum(glm::vec3 p1, glm::vec3 p2){
  glm::vec3 max;
  for (int i = 0; i < 6; i++)
  {
    glm::vec4 plane = planes[i];
    max.x = (plane.x >= 0) ? p2.x : p1.x;
    max.y = (plane.y >= 0) ? p2.y : p1.y;
    max.z = (plane.z >= 0) ? p2.z : p1.z;
    if(plane.x * max.x + plane.y * max.y + plane.z * max.z + plane.w < 0)
      return false;
  }
  return true;
}

