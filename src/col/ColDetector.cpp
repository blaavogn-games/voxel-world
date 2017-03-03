#include "ColDetector.h"

Collision ColDetector::Collides(const Collider &c1, const Collider &c2)
{
  try{
    const ColCircle &circle1 = dynamic_cast<const ColCircle&>(c1);
    try{
      const ColCircle &circle2 = dynamic_cast<const ColCircle&>(c2);
    }catch(std::bad_cast e){}
    try{
      const ColLine &line2 = dynamic_cast<const ColLine&>(c2);
      return ColDetector::CircleLine(circle1, line2);
    }catch(std::bad_cast e){}
  }catch(std::bad_cast e){}

  return Collision::NoCol;
};

Collision ColDetector::CircleLine(const ColCircle &circle, const ColLine &line)
{

  Vector2 a = circle.GetPosition();
  Vector2 b = (line.start - line.end).Normalized();
  b.Scale(a * b);

  if(!b.Contained(line.start, line.end)){
    if((a - line.start).Magnitude() < circle.Radius)
      return Collision(true, line.start.Copy());
    if((a - line.end).Magnitude() < circle.Radius)
      return Collision(true, line.end.Copy());
    return Collision::NoCol;
  }
  if((a - b).Magnitude() < circle.Radius)
    return Collision(true, b);
  return Collision::NoCol;
};
