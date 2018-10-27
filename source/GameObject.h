#pragma once

//仮想クラス
class GameObject
{
protected:
	//こいつのインスタンスが生成されてからの時間を測るよ
	unsigned int frame;

	double x, y;
	double angle;
	double veloX, veloY;
	double accelX, accelY;
	int graphHandle;
	int subGraphHandle;
	void angleNormalize();
	double angleNormalize(double);
	double alpha; //0～1で頼む

	//const double windowCenterX = 300, windowCenterY = 300;
	const double inWheelRadius = 250;

public:
	GameObject(double x, double y, double angle = 0);
	virtual ~GameObject();

	virtual void Process();
	virtual void Draw();

	bool endFlag;
};

