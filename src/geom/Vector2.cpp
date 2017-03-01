#include "Vector2.h"

Vector2::Vector2(float x, float y){
	this->x = x;
	this->y = y;
}

float Vector2::Magnitude(){
	return sqrt(x * x + y * y);
}

Vector2 Vector2::Normalized(){
	float magnitude = Magnitude();
	return Vector2(x / magnitude, y / magnitude);
}

Vector2 Vector2::Copy(){
	return Vector2(x, y);
}

GLfloat* Vector2::operator>>(GLfloat* arr){
	arr[0] = x;
	arr[1] = y;
	return arr + 2;
}

Vector2 Vector2::operator+(Vector2 other){
	return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(Vector2 other){
	return Vector2(x - other.x, y - other.y);
}
