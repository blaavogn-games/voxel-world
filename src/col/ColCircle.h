#ifndef COL_CIRCLE_H
#define COL_CIRCLE_H

#include <stdio.h>

#include "Collider.h"

class ColCircle : public Collider
{
	private:
    float _radius;
  public:
    const float &Radius;
    ColCircle(const Vector2& position, const float radius);
    ~ColCircle();
    virtual void SetPosition(Vector2 pos);
};

#endif
