#include <Vector2D.h>

using namespace GAlpha;

Vector2D::Vector2D() : x(0.0f), y(0.0f)
{
}

Vector2D::Vector2D(float x, float y) : x(x), y(y)
{
}

Vector2D &Vector2D::Add(const Vector2D &other)
{
    this->x += other.x;
    this->y += other.y;
    return *this;
}

Vector2D &Vector2D::Subtract(const Vector2D &other)
{
    this->x -= other.x;
    this->y -= other.y;
    return *this;
}

Vector2D &Vector2D::Multiply(const Vector2D &other)
{
    this->x *= other.x;
    this->y *= other.y;
    return *this;
}

Vector2D &Vector2D::Divide(const Vector2D &other)
{
    this->x /= other.x;
    this->y /= other.y;
    return *this;
}

Vector2D &operator+(Vector2D &left, Vector2D &right)
{
    return left.Add(right);
}

Vector2D &operator-(Vector2D &left, Vector2D &right)
{
    return left.Subtract(right);
}

Vector2D &operator*(Vector2D &left, Vector2D &right)
{
    return left.Multiply(right);
}

Vector2D &operator/(Vector2D &left, Vector2D &right)
{
    return left.Divide(right);
}

Vector2D &Vector2D::operator+=(const Vector2D &other)
{
    return this->Add(other);
}

Vector2D &Vector2D::operator-=(const Vector2D &other)
{
    return this->Subtract(other);
}

Vector2D &Vector2D::operator*=(const Vector2D &other)
{
    return this->Multiply(other);
}

Vector2D &Vector2D::operator/=(const Vector2D &other)
{
    return this->Divide(other);
}

Vector2D &Vector2D::operator*(const float elem)
{
    this->x *= elem;
    this->y *= elem;
    return *this;
}

Vector2D &Vector2D::Zero()
{
    this->x = 0.0f;
    this->y = 0.0f;
    return *this;
}