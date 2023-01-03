#pragma once
#include <windows.h>
#include <gl/GL.h>
#include <glut.h>
#include <cmath>

const float EPSILON = 0.2f;

class Point
{
private:
	double x, y;

public:
	Point()
	{
		x = 0;
		y = 0;
		
	}

	Point(double x, double y)
	{
		this->x = x;
		this->y = y;
	
	}


	const float& getX() const { return x; }
	const float& getY() const { return y; }
	void setX(double x) { this->x = x; }
	void setY(double y) { this->y = y; }

	Point operator- (Point const arg)
	{
		return Point(x - arg.x, y - arg.y);
	}

	bool operator== (const Point& arg)
	{
		return ((abs(this->x - arg.x) < EPSILON) && ((abs(this->y - arg.y) < EPSILON)));
	}



	void drawPoint(float size = 7.0f, GLfloat Red = 1.0f , GLfloat Green = 1.0f, GLfloat Blue = 1.0f)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_POINT_SMOOTH);

		glColor3f(Red, Green, Blue);

		glPointSize(size);

		glBegin(GL_POINTS);
		glVertex2f(x, y);
		glEnd();
	}
};

