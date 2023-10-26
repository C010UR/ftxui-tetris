#pragma once

namespace Tetris::Game
{
class Point
{
  public:

    double x, y;
    
    Point(double x = 0, double y = 0) : x(x), y(y)
    {
    }

    Point operator+(const Point &other) const
    {
        return Point(x + other.x, y + other.y);
    }

    Point operator-(const Point &other) const
    {
        return Point(x - other.x, y - other.y);
    }

    bool operator==(const Point &other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Point &other) const
    {
        return !(*this == other);
    }

    Point &operator+=(const Point &other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    Point &operator-=(const Point &other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }
};
} // namespace Tetris::Game