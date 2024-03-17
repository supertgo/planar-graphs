class Point {
public:
  Point(float x_, float y_);

  Point operator-(const Point &p) const;

  float cross(const Point &p) const;

  float cross(const Point &p, const Point &q) const;

  int half() const;

private:
  float x, y;
};
