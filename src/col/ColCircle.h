#ifndef COL_CIRCLE_H
#define COL_CIRCLE_H

#include <stdio.h>

#include "Collider.h"
#include "../Shader.h"

class ColCircle : public Collider
{
	private:
		Vector2 position;
		float radius;
	public:
		ColCircle(Vector2 position, float radius);
		~ColCircle();
		virtual void SetPosition(Vector2 pos);
};
  
#endif