#include "Ball_Effect.h"
#include "DxLib.h"
#include "main.h"

Ball_Effect::Ball_Effect(double x, double y, int handle, int scorePlus) : GameObject(x, y)
{
	currentSize = 1.0;
	graphHandle = handle;
	this->scorePlus = scorePlus;
	mm->setTag("ballEffect");

	char tmp[8];
	sprintfDx(tmp, "+%d", scorePlus);
	myMessage = mm->add(x - 16, y - 20, tmp);
	myMessage->setVelo((300 - this->x) * 0.005, (300 - this->y) * 0.005);
}


Ball_Effect::~Ball_Effect()
{
	mm->messageDelete(myMessage);
}

void Ball_Effect::Process() {
	GameObject::Process();
	currentSize += 0.04;
	alpha -= 0.02;
	if (alpha <= 0) {
		endFlag = true;
	}
	myMessage->setAlpha(alpha);
}

void Ball_Effect::Draw() {
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255 * alpha);
	DrawRotaGraph((int)x, (int)y, currentSize, angle, graphHandle, TRUE);
}