#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class Point
{
	double x, y;

public:
	Point()
	{
		setX(0);
		setY(0);
	}
	Point(double x, double y)
	{
		setX(x);
		setY(y);
	}
	Point(const Point& point)
	{
		*this = point;
	}

	Point& operator= (const Point& point)
	{
		x = point.x;
		y = point.y;
		return *this;
	}

	bool operator== (const Point& point)
	{
		return x == point.x && y == point.y;
	}
	bool operator!= (const Point& point)
	{
		return !(*this == point);
	}

	Point& operator+ (const Point& point){
		return *(new Point(x + point.x, y + point.y));
	}
	Point& operator- (const Point& point){
		return *(new Point(x - point.x, y - point.y));
	}
	Point& operator- (){
		return *(new Point(-x, -y));
	}
	Point& operator+= (const Point& point) {
		x += point.x;
		y += point.y;
		return *this;
	}
	Point& operator-= (const Point& point) {
		x -= point.x;
		y -= point.y;
		return *this;
	}

	Point& operator* (const double& value) {
		return *(new Point(x * value, y * value));
	}
	Point& operator/ (const double& value) {
		return *(new Point(x / value, y / value));
	}
	Point& operator*= (const double& value) {
		x *= value;
		y *= value;
		return *this;
	}
	Point& operator/= (const double& value) {
		x /= value;
		y /= value;
		return *this;
	}

	void setX(double x) { this->x = x; }
	void setY(double y) { this->y = y; }

	double getX() { return x; }
	double getY() { return y; }

	double dist(Point targert)
	{
		double dx = targert.x - x;
		double dy = targert.y - y;

		return sqrt(dx * dx + dy * dy);
	}
};

ostream& operator<< (ostream& stream, Point& point) {
	stream << "(" << point.getX() << ", " << point.getY() << ")"; return stream;
}
istream& operator>> (istream& stream, Point& point) 
{ 
	double x, y;
	stream >> x >> y; 
	point = Point(x, y);
	return stream; 
}

class Line
{
protected:
	vector<Point> points;

public:
	Line(const vector<Point>& initPoints)
	{
		points = initPoints;
	}
	Line(const Line& line)
	{
		*this = line;
	}

	Line& operator= (const Line& line)
	{
		points = line.points;
		return *this;
	}

	double getPerimetr()
	{
		double perimetr = 0;
		for (int i = 0; i < points.size() - 1; i++)
		{
			perimetr += points[i].dist(points[i + 1]);
		}
		return perimetr;
	}

	virtual void print()
	{
		for (Point point : points)
		{
			cout << point << ' ';
		}
	}
};

class Contour : virtual public Line
{
public:
	Contour(const vector<Point>& initPoints) : Line(initPoints) { }

	double getPerimetr()
	{
		double perimetr = 0;
		for (int i = 0; i < points.size() - 1; i++)
		{
			perimetr += points[i].dist(points[i + 1]);
		}
		perimetr += points[0].dist(points[points.size() - 1]);
		return perimetr;
	}
};

class Polygon : virtual public Contour
{
public:
	//Polygon(const vector<Point>& initPoints) : Contour(initPoints) { }
};


int main()
{
	Point a(2, 7);
	Point b(10, 1);
	Point c;
	c = b;
	c /= 2;

	//cin >> a;
	cout << a << ' ' << b << ' ' << c << '\n';

	Line l(vector<Point>({ a, c, b }));
	Contour ct(vector<Point>({a, c, b}));
	Polygon cc(vector<Point>({ a, c, b }));
	l.print();
	cout << l.getPerimetr() << endl;
	ct.print();
	cc.print();
	cout << ct.getPerimetr() << endl;


}