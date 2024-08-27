#pragma once

namespace GAlpha
{
    class Vector2D
    {
    public:
        float x;
        float y;

        Vector2D();
        Vector2D(float x, float y);

        Vector2D& Add(const Vector2D& other);
        Vector2D& Subtract(const Vector2D& other);
        Vector2D& Multiply(const Vector2D& other);
        Vector2D& Divide(const Vector2D& other);

        friend Vector2D& operator+(Vector2D& left, Vector2D& right);
        friend Vector2D& operator-(Vector2D& left, Vector2D& right);
        friend Vector2D& operator*(Vector2D& left, Vector2D& right);
        friend Vector2D& operator/(Vector2D& left, Vector2D& right);

        Vector2D& operator+=(const Vector2D& other);
        Vector2D& operator-=(const Vector2D& other);
        Vector2D& operator*=(const Vector2D& other);
        Vector2D& operator/=(const Vector2D& other);

        Vector2D& operator*(const float elem);
        Vector2D& Zero();
    };
}