#pragma once
#include "GameObject.h"
#include "Message.h"

class Ball_Effect :
	public GameObject
{
private:
	double currentSize;
	//double currentAlpha;
	int scorePlus;
	Message* myMessage;

public:
	Ball_Effect(double, double, int, int);
	~Ball_Effect();
	void Process();
	void Draw();
};

