#pragma once
#include "GameObject.h"
class Ball :
	public GameObject
{
protected:
	const double ballRadius = 15;
	double speed;
	int color;

	void setSpeed(double);
	void setAngle(double);

public:
	Ball(double, double, double angle = 0);
	~Ball();
	virtual void Process();
};

