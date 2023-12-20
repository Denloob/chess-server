#pragma once

struct Point
{
  public:
    int x;
    int y;

    /**
     * @brief Adds the corresponding coordinates of two points.
     */
    Point operator+(Point other) const;
    Point &operator+=(const Point &other);
};
