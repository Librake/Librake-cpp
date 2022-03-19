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
	double distToLine(Point lineP1, Point lineP2)
	{
		return abs((lineP2.y - lineP1.y) * x - (lineP2.x - lineP1.x) * y + lineP2.x * lineP1.y - lineP2.y * lineP1.x) /
			sqrt(pow(lineP2.y - lineP1.y, 2) + pow(lineP2.x - lineP1.x, 2));
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
	Line(const Line& line) { *this = line; }

	Line& operator= (const Line& line)
	{
		points = line.points;
		return *this;
	}

	virtual double getPerimetr()
	{
		double perimetr = 0;
		for (int i = 0; i < points.size() - 1; i++)
		{
			perimetr += points[i].dist(points[i + 1]);
		}
		return perimetr;
	}

	void print()
	{
		for (Point point : points)
		{
			cout << point << ' ';
		}
	}
};

class Contour : public Line
{
public:
	Contour(const vector<Point>& initPoints) : Line(initPoints) { }
	Contour(const Contour& contour) : Line (contour.points) { }

	Contour& operator= (const Contour& contour)
	{
		points = contour.points;
		return *this;
	}

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

class Triangle : public Contour
{
public:
	Triangle(Point p1, Point p2, Point p3) : Contour(vector<Point>({ p1, p2, p3 })) { }
	Triangle(const Triangle& triangle) : Contour(triangle.points) { }

	Triangle& operator= (const Triangle& triangle)
	{
		points = triangle.points;
		return *this;
	}
	static double triangleArea(Point p1, Point p2, Point p3)
	{
		double height = p1.distToLine(p2, p3);
		double base = p2.dist(p3);
		return height * base / 2;
	}
	double getArea()
	{
		return triangleArea(points[0], points[1], points[2]);
	}
};

class Polygon : public Contour
{	
	
public:
	Polygon(const vector<Point>& initPoints) : Contour(initPoints) { }
	Polygon(const Polygon& polygon) : Contour(polygon.points) { }

	Polygon& operator= (const Polygon& polygon)
	{
		points = polygon.points;
		return *this;
	}

	virtual double getArea()
	{
		double area = 0;
		for (int i = 2; i < points.size(); i++)
		{
			area += Triangle::triangleArea(points[0], points[i - 1], points[i]);
		}
		return area;
	}
};

class Trapeze : public Polygon
{
	bool isParallel(Point a1, Point a2, Point b1, Point b2)
	{
		double dx1 = a2.getX() - a1.getX();
		double dx2 = b2.getX() - b1.getX();
		double dy1 = a2.getY() - a1.getY();
		double dy2 = b2.getY() - b1.getY();

		double angleCos = (dx1 * dx2 + dy1 * dy2) / (sqrt(dx1 * dx1 + dy1 * dy1) * sqrt(dx2 * dx2 + dy2 * dy2));
		return angleCos < 0.01;
	}

	bool isCorrect()
	{
		return isParallel(points[0], points[1], points[2], points[3]);
	}
public:
	Trapeze(Point p1, Point p2, Point p3, Point p4) : Polygon(vector<Point>({ p1, p2, p3, p4 }))
	{ 
		if (!isCorrect())delete this;
	}
	Trapeze(const Trapeze& trapeze) : Polygon(trapeze.points) { }

	Trapeze& operator= (const Trapeze& trapeze)
	{
		points = trapeze.points;
		return *this;
	}

};

class RegPolygon : public Polygon
{
public:
	RegPolygon(const vector<Point>& initPoints) : Polygon(initPoints) 
	{
		double faceLength = points[0].dist(points[1]);
		for (int i = 2; i < points.size(); i++)
		{
			if (points[i].dist(points[i - 1]) != faceLength) delete this;
		}
	}
	RegPolygon(const RegPolygon& regPolygon) : Polygon(regPolygon.points) { }

	RegPolygon& operator= (const RegPolygon& regPolygon)
	{
		points = regPolygon.points;
		return *this;
	}
};



int main()
{
	Point a(2, 7);
	Point b(10, 1);
	Point c(3, 5);

	Line* figures[3];
	figures[0] = new Line(vector<Point>({ a, b, c }));
	figures[1] = new Contour(vector<Point>({ a, b, c }));
	figures[2] = new Triangle(a, b, Point(10, 7));
	
	for (Line* figure : figures)
	{
		cout << figure->getPerimetr() << endl;
	}
}