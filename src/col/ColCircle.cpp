#include "ColCircle.h"

ColCircle::ColCircle(Vector2 position, float radius) : 
	position(position.x, position.y){
	this->radius = radius;
}

ColCircle::~ColCircle(){}

void ColCircle::SetPosition(Vector2 newPosition){
	position = newPosition;
}
