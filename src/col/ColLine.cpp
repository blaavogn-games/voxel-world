#include "ColLine.h"

ColLine::ColLine(Vector2 start, Vector2 end) :
	Collider((start.x + end.x) / 2, (start.y + end.y) / 2),
	start(start.x, start.y),
	end(end.x, end.y){
}

ColLine::~ColLine(){}

void ColLine::SetPosition(Vector2 newPosition){
	Vector2 delta = newPosition - position;
	position = newPosition;
	start = start + delta;
	end = end + delta;
}
