#include "Ball_Effect.h"
#include "DxLib.h"


Ball_Effect::Ball_Effect(double x, double y, int handle) :GameObject(x, y)
{
	currentSize = 1.0;
	currentAlpha = 255;
	graphHandle = handle;
}


Ball_Effect::~Ball_Effect()
{
}

void Ball_Effect::Process() {
	GameObject::Process();
	currentSize += 0.04;
	currentAlpha -= 12;
	if (currentAlpha <= 0) {
		endFlag = true;
	}
}

void Ball_Effect::Draw() {
	SetDrawBlendMode(DX_BLENDMODE_ADD, (int)currentAlpha);
	DrawRotaGraph((int)x, (int)y, currentSize, angle, graphHandle, TRUE);
}