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

//コンストラクタ
Ball::Ball(double x, double y, double angle) : GameObject(x, y, angle)
{
	//角度はとりあえず適当
	this->angle = (double)GetRand(627) / 100.0;

	//スピードは2〜4
	setSpeed(GetRand(2) + 2);
}

//デストラクタ
Ball::~Ball()
{
	if (!wheel->isGameOver) {
		//ホイールに記録されているボール数を減らす
		wheel->deleteBall(color);
		//ホイールが何点増やしたか確認する
		auto crtScorePlus = wheel->lastScorePlus;
		//消滅エフェクトを出す
		obj.push_back(new Ball_Effect(x, y, graphHandle, crtScorePlus));
		//音を鳴らす
		sound_ball[0].Play();
	}
}

void Ball::Process() {
	GameObject::Process();

	//ホイールに当たった時
	if (pow(wheel->getX() - x, 2) + pow(wheel->getY() - y, 2) > pow(inWheelRadius - ballRadius, 2)) {
		//ボール反射
		double tmp = std::acos((x - wheel->getX()) / sqrt(pow(wheel->getX() - x, 2) + pow(wheel->getY() - y, 2)));
		if (y < wheel->getY()) {
			tmp = 2 * M_PI - tmp;
		}
		tmp += M_PI;

		setAngle(tmp);

		//消える部分か判定
		auto check = abs(angle - wheel->getAngle(color));
		if (check < M_PI_4 || check > 2 * M_PI - M_PI_4) {
			endFlag = true;
		}
		else {
			sound_ball[1].Play();
		}
	}

	//ゲームオーバー時
	if (wheel->isGameOver) {
		veloX = 0;
		veloY = 0;
		alpha -= 0.01;
		if (alpha <= 0) {
			endFlag = true;
		}
	}
}
