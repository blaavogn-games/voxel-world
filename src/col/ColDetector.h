#ifndef COLDECTECTOR_H
#define COLDECTECTOR_H

#include <typeinfo>
#include <stdio.h>
#include "Collider.h"
#include "ColCircle.h"
#include "ColLine.h"
#include "Collision.h"
#include "../geom/Vector2.h"

class ColDetector
{
  public:
    static Collision Collides(const Collider &c1, const Collider &c2);
  private:
    ColDetector(){};
    static Collision CircleLine(const ColCircle &circle, const ColLine &line);
};

#endif
