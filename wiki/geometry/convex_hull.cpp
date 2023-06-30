// TITLE: Convex Hull
// COMPLEXITY: N
// DESCRIPTION: Gives you the convex hull of a set of points


struct Point
{
  int x, y;

  void read()
  {
    cin >> x >> y;
  }

  Point operator- (const Point & b) const
  {
    Point p;
    p.x = x - b.x;
    p.y = y - b.y;
    return p;
  }

  void operator-= (const Point & b)
  {
    x -= b.x;
    y -= b.y;
  }

  int operator* (const Point & b) const
  {
    return x * b.y - b.x * y;
  }

  bool operator< (const Point & b) const
  {
    return make_pair(x, y) < make_pair(b.x, b.y);
  }

};

int triangle(const Point & a, const Point & b, const Point & c)
{
  return (b - a) * (c - a);
}

vector<Point> convex_hull(vector<Point> points)
{
  vector<Point> hull;
  sort(all(points));

  for (int z = 0; z < 2; z++) {
    int s = hull.size();
    for (int i = 0; i < points.size(); i++) {
        while(hull.size() >= s + 2) {
            auto a = hull.end()[-2];
            auto b = hull.end()[-1];
            if (triangle(a, b, points[i]) <= 0) {
                break;
            }
            hull.pop_back();
        }
        hull.push_back(points[i]);
    }
    hull.pop_back();
    reverse(all(points));
  }
  return hull;
}
