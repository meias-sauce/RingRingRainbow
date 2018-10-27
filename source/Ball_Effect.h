#pragma once
#include "GameObject.h"
class Ball_Effect :
	public GameObject
{
private:
	double currentSize;
	double currentAlpha;

public:
	Ball_Effect(double, double, int);
	~Ball_Effect();
	void Process();
	void Draw();
};

