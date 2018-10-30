#include "Emitter.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include "DxLib.h"
#include "Resource.h"
#include "main.h"
#include "Ball_Color.h"


Emitter::Emitter(double x, double y, double angle) : GameObject(x, y)
{
	graphHandle = graph_emitter[0].Handle;
	subGraphHandle = graph_emitter[1].Handle;
	drawAngle = angle;
	coolTime = 30;
	addEmitFlag = false;
	alpha = 1;
}

void Emitter::Process()
{
	GameObject::Process();
	/*if (alpha < 1) {
		alpha += 0.01;
	}*/

	if (!wheel->isGameOver) {
		//エミッタ本体の移動
		if (pow(x - wheel->getX(), 2) + pow(y - wheel->getY(), 2) > pow(inWheelRadius * 0.6, 2)) {
			auto tmp = std::acos((x - wheel->getX()) / sqrt(pow(wheel->getX() - x, 2) + pow(wheel->getY() - y, 2)));
			if (y < wheel->getY()) {
				tmp = 2 * M_PI - tmp;
			}
			tmp += M_PI;
			tmp += (GetRand(100) - 50) * 0.01;

			angle = tmp;
			veloX = std::cos(angle) * 0.5;
			veloY = std::sin(angle) * 0.5;
		}
		else if (frame % 40 == 0) {
			angle = angleNormalize(GetRand(627) * 0.01);

			veloX = std::cos(angle) * 0.5;
			veloY = std::sin(angle) * 0.5;
		}

		//射出
		if (frame % coolTime == 0) {
			int tmp = GetRand(3);

			switch (tmp) {
			case 0:
				obj.push_back(new Ball_Yellow(x, y));
				break;
			case 1:
				obj.push_back(new Ball_Red(x, y));
				break;
			case 2:
				obj.push_back(new Ball_Green(x, y));
				break;
			case 3:
				obj.push_back(new Ball_Blue(x, y));
				break;
			}
		}
	}
	else {
		//ゲームオーバー時
		veloX = 0;
		veloY = 0;
		alpha -= 0.01;
		if (alpha <= 0) {
			endFlag = true;
		}
	}

	drawAngle += (M_PI * 2) / coolTime;
}

void Emitter::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * alpha/*(std::sin(frame * 0.1) + 1) * 0.5 * 255 * alpha*/);
	DrawRotaGraph(x, y, 1.0, 0, subGraphHandle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255 * alpha);
	DrawRotaGraph(x, y, 1.0, drawAngle, graphHandle, TRUE);
	printfDx("\ncoolTime == %d", coolTime);
}

void Emitter::addEmit()
{
	if (coolTime <= 40) {
		return;
	}
	else {
		coolTime--;
	}
	/*else {
		if (addEmitFlag) {
			coolTime--;
			addEmitFlag = false;
		}
		else {
			addEmitFlag = true;
		}
	}*/
}
