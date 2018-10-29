#pragma once
#include "GameObject.h"
#include "HSVColor.h"

class Cursor;

class Title : public GameObject
{
private:
	int title_logo;
	int title_logoshadow;
	int title_wheel;
	int title_wheelalpha;

	double wheelExtend;

	unsigned int keyLeft, keyRight, keyUp, keyDown;
	double rotateSpeed, rotateAccel;
	double rotateSpeed_Min, rotateSpeed_Max;
	int wheelBright;

	double sinSource;

	bool decisionFlag;

	HSVColor* hsv;

	Cursor* cursor;

public:
	Title();
	~Title();
	void Process();
	void Draw();
};

class Cursor : public GameObject
{
private:
	bool isMoving;
	int to;

public:
	Cursor();
	~Cursor();
	void Process(double, bool);
	void Draw();
	double getAngle();
	void move(int);
	bool getIsMoving();
	int getTo();
};