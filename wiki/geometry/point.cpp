// TITLE: Point structure
// COMPLEXITY: Does not apply
// DESCRIPTION: Basic 2d point functionality

// Point/vector structure definition and sorting

#define T int
float EPS = 1e-6;
bool eq(T a, T b){ return abs(a-b)<=EPS; }

struct point{
	T x, y;
	point(T x=0, T y=0): x(x), y(y){}
	
	point operator+(const point &o) const{ return {x + o.x, y + o.y}; }
	point operator-(const point &o) const{ return {x - o.x, y - o.y}; }
	point operator*(T k) const{ return {x*k, y*k}; }
	point operator/(T k) const{ return {x/k, y/k}; }
	T operator*(const point &o) const{ return x*o.x + y*o.y; }
	T operator^(const point &o) const{ return x*o.y - y*o.x; }
	bool operator<(const point &o) const{ return (eq(x, o.x) ? y < o.y : x < o.x); }
	bool operator==(const point &o) const{ return eq(x, o.x) and eq(y, o.t); }
	
	friend ostream& operator<<(ostream& os, point p){
		return os << "(" << p.x << "," << p.y << ")";
	}
};

int ret[2][2] = {{3, 2}, {4, 1}};
inline int quad(point p){
	return ret[p.x >= 0][p.y >= 0];
}

bool comp(point a, point b){
	int qa = quad(a), qb = quad(b);
	return (qa == qb ? (a ^ b) > 0 : qa < qb);
}
