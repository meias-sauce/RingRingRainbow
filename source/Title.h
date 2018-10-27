#pragma once
#include "GameObject.h"
#include "HSVColor.h"

class Title : public GameObject
{
private:
	int title_logo;
	int title_logoshadow;
	int title_wheel;
	int title_wheelalpha;

	double wheelExtend;

	unsigned int keyLeft, keyRight;
	double rotateSpeed, rotateAccel;
	double rotateSpeed_Min, rotateSpeed_Max;
	int wheelBright;

	double sinSource;

	bool decisionFlag;

	HSVColor* hsv;

public:
	Title();
	~Title();
	void Process();
	void Draw();
};