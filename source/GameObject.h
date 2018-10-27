#pragma once

//���z�N���X
class GameObject
{
protected:
	//�����̃C���X�^���X����������Ă���̎��Ԃ𑪂��
	unsigned int frame;

	double x, y;
	double angle;
	double veloX, veloY;
	double accelX, accelY;
	int graphHandle;
	int subGraphHandle;
	void angleNormalize();
	double angleNormalize(double);
	double alpha; //0�`1�ŗ���

	//const double windowCenterX = 300, windowCenterY = 300;
	const double inWheelRadius = 250;

public:
	GameObject(double x, double y, double angle = 0);
	virtual ~GameObject();

	virtual void Process();
	virtual void Draw();

	bool endFlag;
};

