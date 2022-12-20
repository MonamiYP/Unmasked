#include "Vector2D.hpp"

Vector2D::Vector2D() { 
    x = 0.0f; 
    y = 0.0f; 
}
Vector2D::Vector2D(float x, float y) {
    this->x = x;
    this->y = y;
}

Vector2D& Vector2D::zero() {
    this->x = 0;
    this->y = 0;
    return *this;
}

Vector2D Vector2D::operator-() const { return Vector2D(-this->x, -this->y); }

Vector2D& Vector2D::operator+=(const Vector2D& vector) {
    this->x += vector.x;
    this->y += vector.y;
    return *this;
}

Vector2D& Vector2D::operator*=(const float t) {
    this->x *= t;
    this->y *= t;
    return *this;
}

Vector2D& Vector2D::operator/=(const float t) { return *this *= 1/t; }

float Vector2D::abs() const { return sqrt(abs2()); }
float Vector2D::abs2() const { return this->x*this->x + this->y*this->y; }

Vector2D Vector2D::operator+(const Vector2D& vector) {
    return Vector2D(this->x + vector.x, this->y + vector.y);
}

Vector2D Vector2D::operator-(const Vector2D& vector) {
    return Vector2D(this->x - vector.x, this->y - vector.y);
}

Vector2D Vector2D::operator*(const float t) {
    return Vector2D(this->x * t, this->y * t);
}

Vector2D Vector2D::operator/(const float t) {
    return Vector2D(this->x / t, this->y / t);
}

float dot(const Vector2D& vector1, const Vector2D& vector2) {
    return vector1.x * vector2.x + vector1.y * vector2.y;
}

Vector2D Vector2D::norm() {
    return *this / this->abs();
}

std::ostream &operator<<(std::ostream &stream, const Vector2D vector)
{
    stream << "(" << vector.x << "," << vector.y << ")";
    return stream;
}