// TITLE: Lattice Points
// COMPLEXITY: N
// DESCRIPTION: Points with integer coordinate

// Picks theorem
// A = area
// i = points_inside
// b = points in boundary including vertices
// A = i + b/2 - 1

void solve()
{
  int n; cin >> n;
  vector<Point> points(n);
  for (int i = 0; i < n; i++) {
    points[i].read();
  }

  // Calculatting points on boundary
  int B = 0;
  for (int i =0; i < n; i++) {
    int j = (i + 1) % n;
    Point p = points[j] - points[i];
    B += __gcd(abs(p.x), abs(p.y)); // Unsafe for 0
  }
  // Calculating Area
  int a2 = 0;
  for (int i= 0; i < n; i++) {
    int j = (i + 1) % n;
    a2 += points[i] * points[j];
  }
  a2 = abs(a2);
  // Picks theorem
  int I = (a2 - B + 2)/2;
  cout << I << " " << B << endl;
}
