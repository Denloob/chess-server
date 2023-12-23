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

    Point operator-() const;
    Point operator-(const Point &other) const;
    Point &operator-=(const Point &other);

    bool operator==(const Point &other) const;
};
