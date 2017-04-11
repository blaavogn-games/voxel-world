#ifndef TRANSFORM
#define TRANSFORM

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

typedef glm::mat4 mat4;

class Transform
{
  private:
    mat4 mat;
  public:
    Transform();
    ~Transform();
    void Scale(glm::vec3 scale){mat = glm::scale(mat, scale);};
    void Translate(glm::vec3 movement){mat = glm::translate(mat, movement);};
    void Rotate(float rot, glm::vec3 axis){mat = glm::rotate(mat, rot, axis);};
    void operator=(mat4 m){mat = m;};
    mat4 GetMat(){return mat;};
};

#endif
