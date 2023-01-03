#pragma once
#include "Point.h"

class DrawPoints : Point
{
public:

	void DrawSquare(Point& dot1, Point& dot2, Point& dot3, Point& dot4, GLfloat Red = 1.0f, GLfloat Green = 1.0f, GLfloat Blue = 1.0f)
	{
		glColor3f(Red, Green, Blue);

		glBegin(GL_QUADS);
		glVertex2f(dot1.getX(), dot1.getY());
		glVertex2f(dot2.getX(), dot2.getY());
		glVertex2f(dot3.getX(), dot3.getY());
		glVertex2f(dot4.getX(), dot4.getY());
		glEnd();
	}

	void DrawSquare(Point& dotLB, Point& dotRT, GLfloat Red = 1.0f, GLfloat Green = 1.0f, GLfloat Blue = 1.0f)
	{
		glColor3f(Red, Green, Blue);

		glBegin(GL_QUADS);
		glVertex2f(dotLB.getX(), dotLB.getY());
		glVertex2f(dotLB.getX(), dotRT.getY());
		glVertex2f(dotRT.getX(), dotRT.getY());
		glVertex2f(dotRT.getX(), dotLB.getY());
		glEnd();
	}

	void DrawLines(Point& dot1, Point& dot2, GLfloat size = 2.0f, GLfloat Red = 1.0f, GLfloat Green = 1.0f, GLfloat Blue = 1.0f, bool dottedLine = false)
	{
		glLineWidth(size);
		glColor3f(Red, Green, Blue);

		if (dottedLine)
		{
			glEnable(GL_LINE_STIPPLE);
			glLineStipple(1, 0x1C47);
		}

		glBegin(GL_LINES);
		glVertex2f(dot1.getX(), dot1.getY());
		glVertex2f(dot2.getX(), dot2.getY());
		glEnd();

		if (dottedLine)
		{
			glDisable(GL_LINE_STIPPLE);
		}

	}

};

