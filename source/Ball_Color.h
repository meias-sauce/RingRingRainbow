#pragma once
#include "Ball.h"
class Ball_Green :
	public Ball
{
public:
	Ball_Green(double, double, double angle = 0);
};

class Ball_Red :
	public Ball
{
public:
	Ball_Red(double, double, double angle = 0);
};

class Ball_Blue :
	public Ball
{
public:
	Ball_Blue(double, double, double angle = 0);
};

class Ball_Yellow :
	public Ball
{
public:
	Ball_Yellow(double, double, double angle = 0);
};