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
	int lastEmit;

public:
	Emitter(double, double, double);
	void Process();
	void Draw();

	void addEmit();
};

