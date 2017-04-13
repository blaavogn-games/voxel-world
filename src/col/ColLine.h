#ifndef COL_LINE_H
#define COL_LINE_H

#include <stdio.h>
#include "Collider.h"

class ColLine : public Collider
{
  public:
    ColLine(Vector2 start, Vector2 end);
    ~ColLine();
		Vector2 start, end;
    virtual void SetPosition(Vector2 pos);
};

#endif
