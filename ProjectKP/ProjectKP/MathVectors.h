#pragma once
#include "Point.h"

class MathVectors : Point
{
public:
	double pseudoScalar(Point& Line1, Point& Line2)
	{
		double x1 = Line1.getX();
		double y1 = Line1.getY();
		double x2 = Line2.getX();
		double y2 = Line2.getY();
		return { (x1 * y2) - (y1 * x2) };
	}

	double scalar(Point& Line1, Point& Line2)
	{
		double x1 = Line1.getX();
		double y1 = Line1.getY();
		double x2 = Line2.getX();
		double y2 = Line2.getY();
		return { (x1 * x2) + (y1 * y2) };
	}
};

