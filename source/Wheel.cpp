#include "Wheel.h"
#include "DxLib.h"
#include "keyboard.h"
#include "Resource.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include "main.h"

Wheel::Wheel(double x, double y, double angle, int frame, double rotateSpeed) : GameObject(x, y, angle)
{
	graphHandle = graph_wheel[0].Handle;
	subGraphHandle = graph_wheel[1].Handle;

	keyLeft = 0;
	keyRight = 0;
	rotateAccel = 0;
	rotateSpeed_Min = 0.0015;
	rotateSpeed_Max = 0.03;
	deleteCountAll = 0;
	currentCountAll = 0;
	alpha = 1;
	this->frame = frame;
	this->rotateSpeed = rotateSpeed;
	score = 0;
	isGameOver = false;
}


Wheel::~Wheel()
{
}

void Wheel::Process()
{
	GameObject::Process();


	if (!isGameOver) {

		/*if (alpha < 1) {
			alpha += 0.01;
		}*/

		//キーまとめ
		if ((Key[KEY_INPUT_LEFT] || Key[KEY_INPUT_A])) {
			keyLeft++;
		}
		else {
			keyLeft = 0;
		}
		if ((Key[KEY_INPUT_RIGHT] || Key[KEY_INPUT_D])) {
			keyRight++;
		}
		else {
			keyRight = 0;
		}

		//操作受付
		if (keyLeft > 0 && (keyRight == 0 || (keyRight > 0 && keyLeft < keyRight))) {
			rotateAccel = -M_PI * 0.001;
		}
		else if (keyRight > 0 && (keyLeft == 0 || (keyLeft > 0 && keyRight < keyLeft))) {
			rotateAccel = M_PI * 0.001;
		}
		else {
			rotateAccel = 0;
			if (abs(rotateSpeed) < M_PI * rotateSpeed_Min) {
				rotateSpeed = M_PI * ((rotateSpeed > 0) ? rotateSpeed_Min : -rotateSpeed_Min);
			}
			else {
				rotateSpeed += M_PI * (rotateSpeed > 0) ? -0.001 : 0.001;
			}
		}
	}
	else {
		//ゲームオーバー時
		rotateAccel = 0;
		if (abs(rotateSpeed) < M_PI * rotateSpeed_Min) {
			rotateSpeed = M_PI * ((rotateSpeed > 0) ? rotateSpeed_Min : -rotateSpeed_Min);
		}
		else {
			rotateSpeed += M_PI * (rotateSpeed > 0) ? -0.001 : 0.001;
		}

		alpha -= 0.01;

		//messageとwheelしかいなくなったら
		if (alpha <= 0 && obj.size() == 2) {
			endFlag = true;
			//ゲームオーバークラスを生成
		}

	}

	//回転速度計算
	rotateSpeed += rotateAccel;

	if (rotateSpeed > M_PI * rotateSpeed_Max) {
		rotateSpeed = M_PI * rotateSpeed_Max;
	}
	else if (rotateSpeed < -M_PI * rotateSpeed_Max) {
		rotateSpeed = -M_PI * rotateSpeed_Max;
	}

	//回転計算
	angle += rotateSpeed;

}

void Wheel::Draw()
{
	GameObject::Draw();
	//printfDx("yellow = %d\nred = %d\ngreen = %d\nblue = %d\n\nall = %d", deleteCount[0], deleteCount[1], deleteCount[2], deleteCount[3], deleteCountAll);
	//printfDx("yellow = %d\nred = %d\ngreen = %d\nblue = %d\n\nall = %d", currentCount[0], currentCount[1], currentCount[2], currentCount[3], currentCountAll);
	printfDx("score = %d", score);
}

double Wheel::getAngle(int color)
{
	switch (color) {
	case 0:
		return angleNormalize(angle + M_PI_2);
		break;
	case 1:
		return angleNormalize(angle + M_PI);
		break;
	case 2:
		return angleNormalize(angle - M_PI_2);
		break;
	case 3:
		return angle;
		break;
	default:
		return angle;
		break;
	}
}

void Wheel::deleteBall(int color)
{
	//スコアカウント
	int scoreCalc = 0;
	for (int i = 0; i < 7; i++) {
		if (currentCount[i] > 0) {
			if (scoreCalc == 0) {
				scoreCalc = 1;
			}
			else {
				scoreCalc *= 2;
			}
		}
	}
	score += scoreCalc;
	lastScorePlus = scoreCalc;

	deleteCountAll++;
	deleteCount[color]++;
	currentCountAll--;
	currentCount[color]--;

	//放出速度アップ
	//if (deleteCountAll % 3 == 0) {
		emitter->addEmit();
	//}
}

void Wheel::addBall(int color)
{
	currentCountAll++;
	currentCount[color]++;
	if (currentCount[color] >= 5) {
		//ゲームオーバー処理
		sound_gameover.Play();
		sound_bgm.Stop();
		isGameOver = true;
	}
}

double Wheel::getX()
{
	return x;
}

double Wheel::getY()
{
	return y;
}