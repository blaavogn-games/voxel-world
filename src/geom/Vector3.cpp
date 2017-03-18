#include "Vector3.h"

Vector3::Vector3(float x, float y, float z){
	this->x = x;
	this->y = y;
	this->z = z;
}

// float Vector2::Magnitude() const{
// 	return sqrt(x * x + y * y);
// }

// Vector2 Vector2::Normalized(){
// 	float magnitude = Magnitude();
// 	return Vector2(x / magnitude, y / magnitude);
// }

// void Vector2::Scale(float s){
// 	x *= s;
// 	y *= s;
// }

Vector3 Vector3::Copy() const{
	return Vector3(x, y, z);
}

// bool Vector2::Contained(const Vector2 &v1, const Vector2 &v2) const{
// 	float minX = v1.x, minY = v1.y, maxX = v2.x, maxY = v2.y;
// 	if(v2.x < v1.x){
// 		minX = v2.x;
// 		maxX = v1.x;
// 	}
// 	if(v2.y < v1.y){
// 		minY = v2.y;
// 		maxY = v1.y;
// 	}
// 	return x >= minX && x <= maxX && y >= minY && y <= maxY;
// }

// GLfloat* Vector2::operator>>(GLfloat *arr){
// 	arr[0] = x;
// 	arr[1] = y;
// 	return arr + 2;
// }

Vector3 Vector3::operator+(Vector3 other) const{
	return Vector3(x + other.x, y + other.y, z + other.z);
}

// Vector2 Vector2::operator-(Vector2 other) const{
// 	return Vector2(x - other.x, y - other.y);
// }

// float Vector2::operator*(Vector2 other) const{
// 	return x * other.x + y * other.y;
// }
