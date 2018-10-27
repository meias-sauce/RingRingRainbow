#pragma once
#include "GameObject.h"

class Emitter :
	public GameObject
{
private:
	double drawAngle;
	int coolTime;
	unsigned int lastDelete;
	bool addEmitFlag;

public:
	Emitter(double, double);
	void Process();
	void Draw();

	void addEmit();
};

