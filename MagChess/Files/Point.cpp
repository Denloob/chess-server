#include "Point.h"

Point Point::operator+(Point other) const
{
    other += *this;

    return other;
}

Point &Point::operator+=(const Point &other)
{
    this->x += other.x;
    this->y += other.y;
    return *this;
}

Point Point::operator-() const
{
    return {-x, -y};
}

Point Point::operator-(const Point &other) const
{
    Point copy = *this;
    copy -= other;

    return copy;
}

Point &Point::operator-=(const Point &other)
{
    return *this += (-other);
}

bool Point::operator==(const Point &other) const
{
    return this->x == other.x && this->y == other.y;
}
