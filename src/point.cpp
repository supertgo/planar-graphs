#include "../include/point.h"

Point::Point(float x_, float y_) : x(x_), y(y_) {}

Point Point::operator-(const Point &p) const { return Point(x - p.x, y - p.y); }

float Point::cross(const Point &p) const { return x * p.y - y * p.x; }

float Point::cross(const Point &p, const Point &q) const {
  return (p - *this).cross(q - *this);
}

int Point::half() const { return int(y < 0 || (y == 0 && x < 0)); }
