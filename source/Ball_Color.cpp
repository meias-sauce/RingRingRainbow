#define _USE_MATH_DEFINES
#include <cmath>
#include "Ball_Color.h"
#include "Resource.h"
#include "main.h"


Ball_Yellow::Ball_Yellow(double x, double y, double angle) : Ball(x, y, angle)
{
	color = 0;
	graphHandle = graph_ball[0].HandleArray[color];
	subGraphHandle = graph_ball[1].HandleArray[color];
	wheel->addBall(color);
}


Ball_Red::Ball_Red(double x, double y, double angle) : Ball(x, y, angle)
{
	color = 1;
	graphHandle = graph_ball[0].HandleArray[color];
	subGraphHandle = graph_ball[1].HandleArray[color];
	wheel->addBall(color);
}


Ball_Green::Ball_Green(double x, double y, double angle) : Ball(x, y, angle)
{
	color = 2;
	graphHandle = graph_ball[0].HandleArray[color];
	subGraphHandle = graph_ball[1].HandleArray[color];
	wheel->addBall(color);
}

Ball_Blue::Ball_Blue(double x, double y, double angle) : Ball(x, y, angle)
{
	color = 3;
	graphHandle = graph_ball[0].HandleArray[color];
	subGraphHandle = graph_ball[1].HandleArray[color];
	wheel->addBall(color);
}