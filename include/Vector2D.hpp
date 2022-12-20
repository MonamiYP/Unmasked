#pragma once
#include <iostream>
#include <cmath>

class Vector2D {
    public:
        float x, y;

        Vector2D();
        Vector2D(float x, float y);

        Vector2D& zero();
        Vector2D operator-() const;
        float abs() const;
        float abs2() const;
        Vector2D norm();

        Vector2D& operator+=(const Vector2D& vector);
        Vector2D& operator*=(const float t);
        Vector2D& operator/=(const float t);

        Vector2D operator+(const Vector2D& vector);
        Vector2D operator-(const Vector2D& vector);
        Vector2D operator*(const float t);
        Vector2D operator/(const float t);
        
        friend float dot(const Vector2D& vector1, const Vector2D& vector2);
        friend std::ostream& operator<<(std::ostream& stream, const Vector2D vector);
};