// TITLE: Line Intersegment
// COMPLEXITY: O(1)
// DESCRIPTION: Check if two half segments intersect with which other

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

};

int triangle(const Point & a, const Point & b, const Point & c)
{
  return (b - a) * (c - a);
}

bool intersect(const Point & p1, const Point & p2, const Point & p3, const Point & p4) {
  bool ans = true;
  int s1 = triangle(p1, p2, p3);
  int s2 = triangle(p1, p2, p4);

  if (s1 == 0 && s2 == 0) {
    int a_min_x = min(p1.x, p2.x);
    int a_max_x = max(p1.x, p2.x);
    int a_min_y = min(p1.y, p2.y);
    int a_max_y = max(p1.y, p2.y);
  
    int b_min_x = min(p3.x, p4.x);
    int b_max_x = max(p3.x, p4.x);
    int b_min_y = min(p3.y, p4.y);
    int b_max_y = max(p3.y, p4.y);
    if (a_min_x > b_max_x || a_min_y > b_max_y) {
      ans = false;
    }
    if (b_min_x > a_max_x || b_min_y > a_max_y) {
      ans = false;
    }
    return ans;
  }
  int s3 = triangle(p3, p4, p1);
  int s4 = triangle(p3, p4, p2);

  if ((s1 < 0) && (s2 < 0)) ans = false;
  if ((s1 > 0) && (s2 > 0)) ans = false;
  if ((s3 < 0) && (s4 < 0)) ans = false;
  if ((s3 > 0) && (s4 > 0)) ans = false;
  return ans;
}
