#include "Ball.h"
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include "main.h"
#include "Ball_Effect.h"
#include "Resource.h"

void Ball::setSpeed(double speed)
{
	this->speed = speed;
	veloX = speed * std::cos(this->angle);
	veloY = speed * std::sin(this->angle);
}

void Ball::setAngle(double angle)
{
	this->angle = angle;
	angleNormalize();

	veloX = speed * std::cos(this->angle);
	veloY = speed * std::sin(this->angle);
}

//�R���X�g���N�^
Ball::Ball(double x, double y, double angle) : GameObject(x, y, angle)
{
	//�p�x�͂Ƃ肠�����K��
	this->angle = (double)GetRand(627) / 100.0;

	//�X�s�[�h��2�`4
	setSpeed(GetRand(2) + 2);
}

//�f�X�g���N�^
Ball::~Ball()
{
	//�z�C�[���ɋL�^����Ă���{�[���������炷
	wheel->deleteBall(color);
	//���ŃG�t�F�N�g���o��
	obj.push_back(new Ball_Effect(x, y, graphHandle));
	//����炷
	sound_ball[0].Play();
}

void Ball::Process() {
	GameObject::Process();
	if (pow(wheel->getX() - x, 2) + pow(wheel->getY() - y, 2) > pow(inWheelRadius - ballRadius, 2)) {
		double tmp = std::acos((x - wheel->getX()) / sqrt(pow(wheel->getX() - x, 2) + pow(wheel->getY() - y, 2)));
		if (y < wheel->getY()) {
			tmp = 2 * M_PI - tmp;
		}
		tmp += M_PI;

		setAngle(tmp);

		auto check = abs(angle - wheel->getAngle(color));
		if (check < M_PI_4 || check > 2 * M_PI - M_PI_4) {
			endFlag = true;
		}
		else {
			sound_ball[1].Play();
		}
	}
}