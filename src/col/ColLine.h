#ifndef COL_LINE_H
#define COL_LINE_H

#include <stdio.h>

#include "Collider.h"
#include "../Shader.h"

class ColLine : public Collider
{
	private:
		Vector2 position;
		Vector2 start, end;
	public:
		ColLine(Vector2 start, Vector2 end);
		~ColLine();
		virtual void SetPosition(Vector2 pos);
};
  
#endif