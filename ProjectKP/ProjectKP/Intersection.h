#pragma once
#include "Point.h"
#include <vector>
#include "MathVectors.h"

class Intersection
{
private:
	MathVectors mathVectors;

	Point& maxPointY(Point& dot1, Point& dot2)
	{
		float y1 = dot1.getY();
		float y2 = dot2.getY();
		if (y1 > y2)
			return dot1;
		else
			return dot2;
	}

public:
	bool dotInPolygon( Point gamePoint, std::vector <Point> &Polygon, float x_max, float x_min)
	{
		int intersection{ 0 };
			Point time{ gamePoint.getX() - x_max + x_min, gamePoint.getY() };
			for (int j{ 0 }; j < Polygon.size()-1; j++)
			{
				double yj2 = Polygon[j + 1].getY();
				double yj1 = Polygon[j].getY();
				if (yj2 != yj1)
				{
					Point max = maxPointY(Polygon[j + 1], Polygon[j]);
					double maxY = max.getY();
					double gameY = gamePoint.getY();
					if (maxY == gameY)
					{
						Point P1P2{ gamePoint - time };
						Point P1m{ max - time };
						Point mP1{ time - max };
						Point mP2{ gamePoint - max };
						if ((mathVectors.pseudoScalar(P1P2, P1m) == 0) && (mathVectors.scalar(mP1, mP2) <= 0))
							intersection++;
					}
					else
					{
						Point vector1{ time - gamePoint };
						Point vector2{ Polygon[j + 1] - gamePoint };
						Point vector3{ Polygon[j] - gamePoint };

						Point vector4{ Polygon[j + 1] - Polygon[j] };
						Point vector5{ gamePoint - Polygon[j] };
						Point vector6{ time - Polygon[j] };

						if (((mathVectors.pseudoScalar(vector1, vector2) * mathVectors.pseudoScalar(vector1, vector3)) < 0) && ((mathVectors.pseudoScalar(vector4, vector5) * mathVectors.pseudoScalar(vector4, vector6)) < 0))
						{
							intersection++;
						}
					}
				}
			}

			if ((intersection % 2) == 0)
				return false;
			else
				return true;

		return false;
	}

	Point findIntersectionPoint(std::pair<Point, Point> a, std::pair<Point, Point> b)
	{
		double x1{ a.first.getX() }, y1{ a.first.getY() }, x2{ a.second.getX() }, y2{ a.second.getY() }, x3{ b.first.getX() }, y3{ b.first.getY() }, x4{ b.second.getX() }, y4{ b.second.getY() };

		double a1 = y1 - y2;
		double b1 = x2 - x1;
		double c1 = x1 * y2 - x2 * y1;
		double a2 = y3 - y4;
		double b2 = x4 - x3;
		double c2 = x3 * y4 - x4 * y3;

		double det = a1 * b2 - a2 * b1;
		double x = (b1 * c2 - b2 * c1) / det;
		double y = (a2 * c1 - a1 * c2) / det;



		Point dotInersection{ x, y };
		return dotInersection;
	}


	int lineInersections(Point dot1, Point dot2, std::vector <Point> &Polygon, std::vector <int> &IntersectionsList)
	{
		int intersection{ 0 };
		for (int j{ 0 }; j < Polygon.size() - 1; j++)
		{

				Point vector1{ dot2 - dot1 };
				Point vector2{ Polygon[j + 1] - dot1 };
				Point vector3{ Polygon[j] - dot1 };

				Point vector4{ Polygon[j + 1] - Polygon[j] };
				Point vector5{ dot1 - Polygon[j] };
				Point vector6{ dot2 - Polygon[j] };

				if (((mathVectors.pseudoScalar(vector1, vector2) * mathVectors.pseudoScalar(vector1, vector3)) < 0) && ((mathVectors.pseudoScalar(vector4, vector5) * mathVectors.pseudoScalar(vector4, vector6)) < 0))
				{
					IntersectionsList.push_back(j);
					intersection++;
				}
		}

		return intersection;
	}

	/*Point findIntersectionPoint (std::pair<Point, Point> a, std::pair<Point, Point> b)
	{
		double num = (b.first.getX() * b.second.getY() - b.second.getX() * b.first.getY()) * (a.first - a.second).getX() - (a.first.getX() * a.second.getY() - a.second.getX() * a.first.getY()) * (b.first - b.second).getX();
		double den = (a.first - a.second).getY() * (b.first - b.second).getX() - (b.first - b.second).getX() * (a.first - a.second).getX();
		double x = num / den;
		double y = (x * (a.first - a.second).getY() + (a.first.getX() * a.second.getY() - a.second.getX() * a.first.getY())) / (a.first - a.second).getX();

		Point dotInersection{ x, y };
		return dotInersection;
	}*/

	

};

