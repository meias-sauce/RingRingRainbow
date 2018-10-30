#pragma once
#include "GameObject.h"
class Wheel :
	public GameObject
{
private:
	//ÉLÅ[Ç™âüÇ≥ÇÍÇΩí∑Ç≥Ç‹Ç∆Çﬂóp
	unsigned int keyLeft, keyRight;
	double rotateSpeed;
	double rotateAccel;
	double rotateSpeed_Min, rotateSpeed_Max;
	unsigned int deleteCountAll;
	unsigned int currentCountAll;
	unsigned int deleteCount[7] = { 0 };
	unsigned int currentCount[7] = { 0 };
	unsigned int score;

public:
	Wheel(double, double, double, int, double);
	~Wheel();
	void Process();
	void Draw();

	double getAngle(int color = -1);
	void deleteBall(int);
	void addBall(int);
	double getX();
	double getY();

	int lastScorePlus;
	bool isGameOver;
};

