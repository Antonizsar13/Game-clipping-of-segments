#pragma once
#include <windows.h>
#include <vector>
#include <time.h>
#include <cmath>
#include "Point.h"
#include "MathVectors.h"

class GenerationPolygon : Point
{
public:

	GenerationPolygon(float x_min_poligon, float x_max_poligon, float y_min_poligon, float y_max_poligon, int stepAngel)
	{
		this->x_max = x_max_poligon;
		this->x_min = x_min_poligon;
		this->y_max = y_max_poligon;
		this->y_min = y_min_poligon;
		
		this->step = stepAngel;
		generation();
	}

private:
	float x_min, x_max, y_min, y_max;

	int step;

	std::vector <Point> dotsPolygon;
	bool work{ true };
	Point firstDot;
	Point timeDot;
	double angel;
	double an = 0;

	MathVectors mathVectors;

	void RandomFirstPoint(Point& point)
	{
		point.setX(rand() % (int)(x_max - x_min - 2) + x_min + 1 );
		point.setY(rand() % (int)(y_max - y_min - 2) + y_min + 1 );
	}

	void RandomPoint2(Point& Point) {
		float longe, x = x_min - 1, y = y_min - 1, x0, y0;
		x0 = firstDot.getX();
		y0 = firstDot.getY();

		
		//an = rand() % 20 + angel + 1;
		while (((x < x_min || x > x_max) || (y < y_min || y >   y_max)))
		{
			an = ((rand() % (step * 100)) + (step * 0.2)) / 100 + angel;
			longe = ((rand() % 400) + 100) / 100;
			x = x0 + longe * cos(an * 0.017453);
			y = y0 + longe * sin(an * 0.017453);
		}
		Point.setX(x);
		Point.setY(y);
	}

	void generation()
	{
		RandomFirstPoint(firstDot);

		Point pointSearth{ firstDot.getX() + 1, firstDot.getY() };
		Point vector1;
		Point vector2{ pointSearth - firstDot };
		bool work{ true };

		while (angel + step < 360)
		{
			RandomPoint2(timeDot);
			vector2 = timeDot - firstDot;

			dotsPolygon.push_back(timeDot);
			timeDot.drawPoint();
			angel += an;
			glFlush();
		}
		dotsPolygon.push_back(dotsPolygon[0]);
	}

public:

	std::vector <Point>& ToPointVector()
	{
		return dotsPolygon;
	}
};