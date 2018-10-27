#include "GameObject.h"
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include "DxLib.h"

void GameObject::angleNormalize()
{
	angle = angleNormalize(angle);
}

double GameObject::angleNormalize(double angle)
{
	bool flag;
	do {
		flag = false;
		if (angle >= 2 * M_PI) {
			angle -= 2 * M_PI;
			flag = true;
		}
		else if (angle < 0) {
			angle += 2 * M_PI;
			flag = true;
		}
	} while (flag);
	return angle;
}

GameObject::GameObject(double x, double y, double angle)
{
	this->x = x;
	this->y = y;
	veloX = 0;
	veloY = 0;
	accelX = 0;
	accelY = 0;
	this->angle = angle;
	frame = 0;
	endFlag = false;
	alpha = 1;
}

GameObject::~GameObject()
{
}

void GameObject::Process()
{
	veloX += accelX;
	veloY += accelY;
	x += veloX;
	y += veloY;

	if (angle >= 2 * M_PI) {
		angle = angle - (2 * M_PI);
	}
	else if (angle < 0) {
		angle = angle + (2 * M_PI);
	}
		
	frame++;
}

void GameObject::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (std::sin(frame * 0.1) + 1) * 0.5 * 255 * alpha);
	DrawRotaGraph(x, y, 1.0, angle, subGraphHandle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255 * alpha);
	DrawRotaGraph(x, y, 1.0, angle, graphHandle, TRUE);
}