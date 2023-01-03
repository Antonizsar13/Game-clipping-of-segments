#include <windows.h>
#include <gl/GL.h>
#include <glut.h>
#include <iostream>
#include "Point.h"
#include <vector>
#include <time.h>
#include <string>
#include <math.h>
#include "GenerationPolygon.h"
#include "DrawPoints.h"
#include "MathVectors.h"
#include "Intersection.h"
#include <algorithm>

#include <fstream>



const int width = 550, height = 550;
const float x_min = -1.0f, x_max = 10.0f, y_min = -1.0f, y_max = 10.0f;
const float EPS = 0.5f;

double timer = 5;//3
double timerGame = 100;//15
int score = 0;

bool FirstRan{ true };
bool work{ false };
bool firstDot{ true };

std::vector <Point> Points;
Point dot, dot1, dot2;
std::string stringScore = "Score: 0";
std::string stringTime = "Time: " + std::to_string((int)timerGame);
int higerScore;

DrawPoints drawPoints;
MathVectors mathVectors;

clock_t startGame;
clock_t startTime;



Point leftCorner{ x_min + EPS, y_min + EPS };
Point rightCorner{ x_max - EPS, y_max - EPS };


void fileHigerScore()
{
	std::ifstream file;
	file.open("HigerScore.txt");
	file >> higerScore;
	file.close();
}

void file()
{
	std::string fileName = "1.txt";

	std::ifstream file;
	file.open(fileName);
	float Xpoint, Ypoint;

	while (!file.eof())
	{
		file >> Xpoint;
		file >> Ypoint;
		Point dot{ Xpoint + 1, Ypoint + 1 };
		dot.drawPoint();
		Points.push_back(dot);
	}
	file.close();
}



void Text_Out(std::string str, GLfloat x, GLfloat y, GLfloat Red = 1.0f, GLfloat Green = 1.0f, GLfloat Blue = 1.0f);
bool ScreenStart(bool checkPozishion);
void ChooseTimersScreen();
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	Point dot2{ x_min + EPS, y_max - EPS};

	Point dot4{ x_max - EPS, y_min + EPS};

	Point dotLB{ ((x_min + x_max) / 2) - 2.5, y_min + 0.0 };
	Point dotRT{ ((x_min + x_max) / 2) + 2.5, y_min + 0.5 };

	drawPoints.DrawSquare(dotLB, dotRT, 0, 0, 0);

	std::string stringHigerScore = "Higer score: " + std::to_string(higerScore);
	Text_Out(stringHigerScore, (x_min + x_max) / 2 - 2.0, y_min + 0.2);
	drawPoints.DrawSquare(leftCorner, dot2, rightCorner, dot4, 0.1, 0.1, 0.1); 
	
	if (FirstRan)
	{
		ScreenStart(false);
	}
	glFlush();
}

void init(void)
{
	glClearColor(0.0f, 0.0f, 0.8f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(x_min, x_max, y_min, y_max);
	glClear(GL_COLOR_BUFFER_BIT);
}


void convect(Point& object)
{
	object.setX(object.getX() * (x_max - x_min) / width + x_min);
	object.setY(-(object.getY()) * (y_max - y_min) / height + y_max);
}

void Text_Out(std::string str, GLfloat x, GLfloat y, GLfloat Red, GLfloat Green, GLfloat Blue)
{
	glColor3f(Red, Green, Blue);

	for (int i{ 0 }; i < str.length(); i++)
	{
		glRasterPos2f(x + i * 0.2, y);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str[i]);
	}
}

void ChooseTimersScreen()
{
	Text_Out("Time round:", (x_max + x_min) / 2 - 1, ((y_max + y_min) / 2 - 1));
	
	Point dotLB{ (x_max + x_min) / 2 - 1.7,(y_max + y_min) / 2 - 1.6 }, dotRT{ (x_max + x_min) / 2 - 1.1,(y_max + y_min) / 2 - 1.15 };
	if (timer == 1)
		drawPoints.DrawSquare(dotLB, dotRT, 0.2, 0.6, 0.3);
	else
		drawPoints.DrawSquare(dotLB, dotRT, 0.2, 0.2, 0.3);
	Text_Out("1", (x_max + x_min) / 2 - 1.5, ((y_max + y_min) / 2 - 1.5));

	dotLB.setX((x_max + x_min) / 2 - 0.7); dotRT.setX((x_max + x_min) / 2 - 0.1 );
	if (timer == 3)
		drawPoints.DrawSquare(dotLB, dotRT, 0.2, 0.6, 0.3);
	else
		drawPoints.DrawSquare(dotLB, dotRT, 0.2, 0.2, 0.3);
	Text_Out("3", (x_max + x_min) / 2 - 0.5, ((y_max + y_min) / 2 - 1.5));

	dotLB.setX((x_max + x_min) / 2 + 0.3); dotRT.setX((x_max + x_min) / 2 + 0.9);
	if (timer == 5)
		drawPoints.DrawSquare(dotLB, dotRT, 0.2, 0.6, 0.3);
	else
		drawPoints.DrawSquare(dotLB, dotRT, 0.2, 0.2, 0.3);
	Text_Out("5", (x_max + x_min) / 2 + 0.5 , ((y_max + y_min) / 2 - 1.5));

	dotLB.setX((x_max + x_min) / 2 + 1.3); dotRT.setX((x_max + x_min) / 2 + 2.0);
	if (timer == 10)
		drawPoints.DrawSquare(dotLB, dotRT, 0.2, 0.6, 0.3);
	else
		drawPoints.DrawSquare(dotLB, dotRT, 0.2, 0.2, 0.3);
	Text_Out("10", (x_max + x_min) / 2 + 1.5, ((y_max + y_min) / 2 - 1.5));
	
	Text_Out("Time game:", (x_max + x_min) / 2 - 1, ((y_max + y_min) / 2 - 2.5));

	dotLB.setY((y_max + y_min) / 2 - 3.2); dotRT.setY(((y_max + y_min) / 2 - 2.75));
	dotLB.setX((x_max + x_min) / 2 - 1.2); dotRT.setX((x_max + x_min) / 2 - 0.5);
	if (timerGame == 25)
		drawPoints.DrawSquare(dotLB, dotRT, 0.4, 0.3, 0.6);
	else
		drawPoints.DrawSquare(dotLB, dotRT, 0.4, 0.2, 0.3);
	Text_Out("25", (x_max + x_min) / 2 - 1, ((y_max + y_min) / 2 - 3));

	dotLB.setX((x_max + x_min) / 2 - 0.2); dotRT.setX((x_max + x_min) / 2 + 0.5);
	if (timerGame == 50)
		drawPoints.DrawSquare(dotLB, dotRT, 0.4, 0.3, 0.6);
	else
		drawPoints.DrawSquare(dotLB, dotRT, 0.4, 0.2, 0.3);
	Text_Out("50", (x_max + x_min) / 2, ((y_max + y_min) / 2 - 3));

	dotLB.setX((x_max + x_min) / 2 + 0.8); dotRT.setX((x_max + x_min) / 2 + 1.8);
	if (timerGame == 100)
		drawPoints.DrawSquare(dotLB, dotRT, 0.4, 0.3, 0.6);
	else
		drawPoints.DrawSquare(dotLB, dotRT, 0.4, 0.2, 0.3);
	Text_Out("100", (x_max + x_min) / 2 + 1, ((y_max + y_min) / 2 - 3));
}

void DrawPolygon()
{
	GenerationPolygon Polygon(x_min + EPS, x_max - EPS, y_min + EPS, y_max - EPS, 30);
	Points = Polygon.ToPointVector();

	//file();
	glColor3f(((rand() % 5) + 5) / 10.0, (rand() % 10) / 10.0, (rand() % 10) / 10.0);
	glBegin(GL_LINE_LOOP);
	for (int i{ 0 }; i < Points.size(); i++)
	{
		glVertex2f(Points[i].getX(), Points[i].getY());
	}
	glEnd();
}


void NewPolygon()
{
	Points.clear();
	display();
	DrawPolygon();
	firstDot = true;
	Text_Out(stringScore, x_max - 2.5, y_max - 0.4);
	stringTime = "Time: " + std::to_string((int)(timerGame - (clock() - startGame) / CLOCKS_PER_SEC));
	Text_Out(stringTime, x_min + 1.0, y_max - 0.4);
	if (score > higerScore)
		higerScore = score;
	startTime = clock();
	glFlush();
}

void Time()
{
	double elpsedTime;
	elpsedTime = double((clock() - startTime) / CLOCKS_PER_SEC);
	if ((elpsedTime > timer) && work)
	{
		NewPolygon();
	}
	elpsedTime = double((clock() - startGame) / CLOCKS_PER_SEC);

	if ((elpsedTime > timerGame) && work)
	{
		work = false;
	}
}

bool dotInZoneSquare(Point& dot1Zone, Point& dot2Zone)
{
	float x1{ dot1Zone.getX() };
	float y1{ dot1Zone.getY() };
	float x2{ dot2Zone.getX() };
	float y2{ dot2Zone.getY() };
	float x{ dot.getX() };
	float y{ dot.getY() };

	if (((x1 <= x) && (x <= x2)) && ((y1 <= y) && (y <= y2)))
		return true;
	else
		return false;
}

bool ScreenStart(bool checkPozishion = true) {
	Point dot1, dot2, dot3, dot4;
	dot1.setX((x_max + x_min) / 2 - 1.0);
	dot1.setY((y_max + y_min) / 2 - 0.5);

	dot2.setX((x_max + x_min) / 2 - 1.0);
	dot2.setY((y_max + y_min) / 2 + 0.5);

	dot3.setX((x_max + x_min) / 2 + 1.0);
	dot3.setY((y_max + y_min) / 2 + 0.5);

	dot4.setX((x_max + x_min) / 2 + 1.0);
	dot4.setY((y_max + y_min) / 2 - 0.5);

	drawPoints.DrawSquare(dot1, dot2, dot3, dot4, 0.3, 0.4, 0.5);
	Text_Out("Start", (x_max + x_min) / 2 - 0.5, (y_max + y_min) / 2);
	ChooseTimersScreen();
	if (checkPozishion)
	{
		return(dotInZoneSquare(dot1, dot3));
	}
	glFlush();
}

void ScoreChange(int newScore)// прибавляет счет
{
	score += newScore;
	stringScore = "Score: " + std::to_string(score);
}


double SegmentLength(Point dot1, Point dot2)//длина отрезка
{
	double x1{dot1.getX()}, x2{ dot2.getX() }, y1{ dot1.getY() }, y2{ dot2.getY() };

	return (sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2)));
}

bool comp(std::pair <Point, double> a, std::pair <Point, double> b)
{
	return a.second < b.second;
}

void CheckFileHigerScore(int score)
{
	std::ofstream file;
	file.open("HigerScore.txt");

	if (score > higerScore)
	{
		higerScore = score;
		file << std::to_string(higerScore);
	}
	file.close();
}

void GameLogic()// логика всей игры
{
	Intersection intersection;
	std::vector <int> ListFirstPointIntersections;
	std::vector <Point> PointsIntersections;
	int intersectionCount = intersection.lineInersections(dot1, dot2, Points, ListFirstPointIntersections); //количество точек персечений построенной прямой с полигоном
	if (intersectionCount != 0)// проверка если не 0
	{
		if (intersectionCount == 1)//проверка для одного пересчений (можно ее и убрать и будет работать проверка нечетных но с ней оптимальнее)(это тоже можно вставить в презентацию)
		{
			
			drawPoints.DrawLines(Points[ListFirstPointIntersections[0]], Points[ListFirstPointIntersections[0] + 1], 3.0, 0.1, 1.0, 0.2);// "красит линию с пересечением в зеленым
			std::pair <Point, Point> line {dot1, dot2};
			std::pair <Point, Point> linePolygon{ Points[ListFirstPointIntersections[0]], Points[ListFirstPointIntersections[0] + 1]};

			Point dotIntersection = intersection.findIntersectionPoint(line, linePolygon);// находит единственную точку пресечения

			if (intersection.dotInPolygon(dot1, Points, x_max, x_min))// если первая точка была внутри полигона
			{// то стоим от нее прямую то пересечения и в счет прибавляем просто счет
				drawPoints.DrawLines(dot1, dotIntersection);
				ScoreChange((int)(10 * SegmentLength(dot1, dotIntersection)));
			}
			else// если не первая втутри то значит вторая
			{// то же самое только от второй точки
				drawPoints.DrawLines(dot2, dotIntersection);
				ScoreChange((int)(10 * SegmentLength(dot2, dotIntersection)));
			}
			dotIntersection.drawPoint(5.0, 0.7, 0.2, 0.9);
		}//
		else
		
		
		if ((intersectionCount % 2) != 0)// проверка для нечетных
		{
			if (intersection.dotInPolygon(dot2, Points, x_max, x_min))// если вторая точка внутри то точки меняем их местами
			{
				Point time = dot2;
				dot2 = dot1;
				dot1 = time;
			}

			

			std::pair <Point, Point> line{ dot1, dot2 }; //пара точка точка то есть типо отрезок

			std::vector <std::pair <Point, double>> dotInteresectionSort;// пара точка, длина что бы хранить точку и ее отдаленость от точки дот1 


			for (int i{ 0 }; i < ListFirstPointIntersections.size(); i++)// идет по первым точкам всех прямых с которыми пересеклись(искали мы их в посчете пересечений)
			{
				drawPoints.DrawLines(Points[ListFirstPointIntersections[i]], Points[ListFirstPointIntersections[i] + 1], 3.0, 0.1, 1.0, 0.2);
				//рисуется зеленым прямая пересеченная

				std::pair <Point, Point> linePolygon{ Points[ListFirstPointIntersections[i]], Points[ListFirstPointIntersections[i] + 1] };
				//пара точка точка хранит прямую с которой персекается при данном  i

				Point dotIntersection = intersection.findIntersectionPoint(line, linePolygon);//находит точки пересечения с прямой та что сейчас в цикле
				
				double lenght = SegmentLength(dot1, dotIntersection);// длину от точки внутри до прямой
			// только комиты убери когда скринить будешь
				std::pair <Point, double> IntersectionTime{ dotIntersection, lenght };

				dotInteresectionSort.push_back(IntersectionTime);//заполняется вектор со значениями точка и длина от нее до точки 1

				dotIntersection.drawPoint(5.0, 0.7, 0.2, 0.9);//рисуется точка пресечения
			}

			sort(dotInteresectionSort.begin(), dotInteresectionSort.end(), comp);// сортируется по оттдалености от точки 1

			bool firstIntersection = true;

			for (int i{ 0 }; i < dotInteresectionSort.size(); i++)// рисуется с почердностью (пересечение рисуется, не рисуется, рисуется , не рисуется и тд )
			{
				Point dotInteresection = dotInteresectionSort[i].first;

				if (firstIntersection)
				{
					drawPoints.DrawLines(dot1, dotInteresection);
					ScoreChange((int)(10 * intersectionCount * SegmentLength(dot1, dotInteresection)));// и прибавляется к счету умноженное на количество пересечений
					firstIntersection = false;
				}
				else
				{
					firstIntersection = true;
				}
				dot1 = dotInteresection;
			}
			dotInteresectionSort.clear();
		}// 
		else//случай когда количество пересечений четное тоже надо в презентацию(проверка похожа на с четными)
		{// ввобщем то тут все тоже самое что и в предыдущем только некоторые моменты котоыре отличаоются сейчас покажу
			bool firstIntersection = false;
			bool dotsInPoligon = false;
			if (intersection.dotInPolygon(dot1, Points, x_max, x_min))//вот тут если какаято точка внутри ну значит и вторая внутри тогда меняем переменные булевые что бы знать что мы начинаем строить сразу типо внутри
			{
				firstIntersection = true;
				dotsInPoligon = true;
			}

			std::pair <Point, Point> line{ dot1, dot2 };

			std::vector <std::pair <Point, double>> dotInteresectionSort;


			for (int i{ 0 }; i < ListFirstPointIntersections.size(); i++)
			{
				drawPoints.DrawLines(Points[ListFirstPointIntersections[i]], Points[ListFirstPointIntersections[i] + 1], 3.0, 0.1, 1.0, 0.2);

				std::pair <Point, Point> linePolygon{ Points[ListFirstPointIntersections[i]], Points[ListFirstPointIntersections[i] + 1] };

				Point dotIntersection = intersection.findIntersectionPoint(line, linePolygon);

				double lenght = SegmentLength(dot1, dotIntersection);

				std::pair <Point, double> IntersectionTime{ dotIntersection, lenght };

				dotInteresectionSort.push_back(IntersectionTime);

				dotIntersection.drawPoint(5.0, 0.7, 0.2, 0.9);
			}

			sort(dotInteresectionSort.begin(), dotInteresectionSort.end(), comp);


			for (int i{ 0 }; i < dotInteresectionSort.size(); i++)
			{
				Point dotInteresection = dotInteresectionSort[i].first;

				if (firstIntersection)//ну тут собсвенно и тоже самое что и в нечетных пересеченияъ
				{
						drawPoints.DrawLines(dot1, dotInteresection);
						ScoreChange((int)(10 * intersectionCount * dotInteresectionSort[i].second));
					firstIntersection = false;
				}
				else
				{
					firstIntersection = true;
				}
				dot1 = dotInteresection;
			}
			
			if (dotsInPoligon)// если точки были внутри то тогда нужно еще последнее пресечение с второй точкой соединить
			{
				drawPoints.DrawLines(dot1, dot2);
			}
			dotInteresectionSort.clear();
		}	
	}
	else
	{// случай когда нет пересеченрй
		if(intersection.dotInPolygon(dot1, Points, x_max, x_min))// если хоть одна внутри то логично и вторая внутри и засчитываем что она внутри
		{
			drawPoints.DrawLines(dot1, dot2);
			ScoreChange((int)(10 * SegmentLength(dot1, dot2)));
		}
	}

	ListFirstPointIntersections.clear();
}


void mouse(int botton, int state, int x, int y)
{
	if ((botton == GLUT_LEFT_BUTTON) && (state == GLUT_UP))
	{
		dot.setX(x);
		dot.setY(y);
		convect(dot);
		if (dotInZoneSquare(leftCorner, rightCorner))
		{
			if (work)
			{
				if (firstDot)
				{
					//dot.setX(4);
					//dot.setY(0);
					dot1 = dot;
					dot1.drawPoint(9.0, 1.0, 0.9, 0.0);
					
					firstDot = false;
				}
				else
				{
					//dot.setX(1);
					//dot.setY(3);
					dot2 = dot;
					if (!(dot1 == dot2))
					{
						dot2.drawPoint(9.0, 1.0, 0.9, 0.0);
						drawPoints.DrawLines(dot1, dot2, 2, 1, 1, 1, true);
						firstDot = true;
						GameLogic();

					}
				}

			}
			else
			{
				if (!FirstRan)
				{
					Text_Out("Game over", (x_max + x_min) / 2 - 1.0, (y_max + y_min) / 2);
					CheckFileHigerScore(score);
					stringScore = "Score: " + std::to_string(score);
					Text_Out(stringScore, (x_max + x_min) / 2 - 1.0, (y_max + y_min) / 2 - 0.3);
					glFlush();
					Sleep(2200);
					display();
					score = 0;
					stringScore = "Score: 0";
					stringTime = "Time: " + std::to_string((int)timerGame);
				}
				else
					FirstRan = false;

				
				if (ScreenStart())
				{
					display();
					work = true;
					startGame = clock();
					NewPolygon();
				}
				else
					FirstRan = true;

				Point dotLB{ (x_max + x_min) / 2 - 1.7,(y_max + y_min) / 2 - 1.6 }, dotRT{ (x_max + x_min) / 2 - 1.1,(y_max + y_min) / 2 - 1.15 };
				if (dotInZoneSquare(dotLB, dotRT))
				{
					timer = 1;
					display();
				}
				dotLB.setX((x_max + x_min) / 2 - 0.7); dotRT.setX((x_max + x_min) / 2 - 0.1);
				if (dotInZoneSquare(dotLB, dotRT))
				{
					timer = 3;
					display();
				}
				dotLB.setX((x_max + x_min) / 2 + 0.3); dotRT.setX((x_max + x_min) / 2 + 0.9);
				if (dotInZoneSquare(dotLB, dotRT))
				{
					timer = 5;
					display();
				}
				dotLB.setX((x_max + x_min) / 2 + 1.3); dotRT.setX((x_max + x_min) / 2 + 2.0);
				if (dotInZoneSquare(dotLB, dotRT))
				{
					timer = 10;
					display();
				}

				dotLB.setY((y_max + y_min) / 2 - 3.2); dotRT.setY(((y_max + y_min) / 2 - 2.75));
				dotLB.setX((x_max + x_min) / 2 - 1.2); dotRT.setX((x_max + x_min) / 2 - 0.5);
				if (dotInZoneSquare(dotLB, dotRT))
				{
					timerGame = 25;
					display();
				}
				dotLB.setX((x_max + x_min) / 2 - 0.2); dotRT.setX((x_max + x_min) / 2 + 0.5);
				if (dotInZoneSquare(dotLB, dotRT))
				{
					timerGame = 50;
					display();
				}
				dotLB.setX((x_max + x_min) / 2 + 0.8); dotRT.setX((x_max + x_min) / 2 + 1.8);
				if (dotInZoneSquare(dotLB, dotRT))
				{
					timerGame = 100;
					display();
				}
			}
		}
		else
		{
			if (!work)
			{
				Point dotLB{ ((x_min + x_max) / 2) - 2.5, y_min + 0.0 };
				Point dotRT{ ((x_min + x_max) / 2) + 2.5, y_min + 0.5 };

				if (dotInZoneSquare(dotLB, dotRT))
				{
					std::ofstream file;
					file.open("HigerScore.txt");
					higerScore = 0;
					file << std::to_string(higerScore);
					file.close();
					display();
				}
			}
		}
	}
	glFlush();
}



int main(int argc, char** argv)
{
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Game Polygon Point");
	fileHigerScore();
	init();
	glutDisplayFunc(display);
	glutIdleFunc(Time);
	glutMouseFunc(mouse);
	glutMainLoop();

	return 0;
}