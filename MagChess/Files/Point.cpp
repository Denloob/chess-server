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
