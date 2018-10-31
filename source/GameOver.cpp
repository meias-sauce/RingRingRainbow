#define _USE_MATH_DEFINES
#include <cmath>
#include "GameOver.h"
#include "main.h"
#include "Resource.h"
#include "DxLib.h"
#include "keyboard.h"

GameOver::GameOver(int score) :GameObject(0, 0)
{
	mm->setCoolTime(0);
	mm->setTag("gameover");
	(mm->add(155, 150, "Game Over"))->setFont(font_cineBig.Handle);
	mm->tagSetAlpha(0);

	this->score = score;

	alpha = 0;
	phase = 0;
	sinSource = - M_PI_2;
	keyEnter = 0;
}


GameOver::~GameOver()
{
	mm->setTag("gameover");
	mm->tagDelete();
	mm->setAlpha(1);

	title = new Title();
	obj.push_back(title);
}

void GameOver::Process() {
	switch (phase) {
	case 0:
		if (alpha < 1) {
			alpha += 0.03;
			mm->tagSetAlpha(alpha);
		}
		else {
			mm->setCoolTime(3);
			mm->setTag("gameover");
			lastMessage = mm->add(100, 340, "Score");
			phase = 1;
		}
		break;
	case 1:
		if (lastMessage->getIsEmpty()) {
			mm->setCoolTime(3);
			mm->setTag("gameover");
			char scoreStr[8];
			sprintfDx(scoreStr, "%d", score);

			int scoreX;
			for (int i = 0; i < 8; i++) {
				if (scoreStr[i] == '\0') {
					scoreX = 295 - i * 15;
					break;
				}
			}

			(lastMessage = (mm->add(scoreX, 310, scoreStr)))->setFont(font_cineBig.Handle);
			phase = 2;
		}
		break;

	case 2:
		if (lastMessage->getIsEmpty()) {
			mm->setCoolTime(3);
			mm->setTag("gameover");
			char scoreStr[8];
			lastMessage = mm->add(400, 340, "pts");
			phase = 3;
		}
		break;
	case 3:
		if (lastMessage->getIsEmpty()) {
			mm->setCoolTime(0);
			mm->setTag("gameover");
			(lastMessage = mm->add(320, 550, "press to title"))->setAlpha(0);
			phase = 4;
		}
		break;
	case 4:
		//ƒL[‚Ü‚Æ‚ß
		if ((Key[KEY_INPUT_Z] || Key[KEY_INPUT_RETURN])) {
			keyEnter++;
		}
		else {
			keyEnter = 0;
		}

		lastMessage->setAlpha((sin(sinSource) + 1) * 0.5);
		sinSource += 0.05;

		//‘€ìŽó•t
		if (keyEnter == 1) {
			phase = 5;
			sound_start.Play();
		}
		break;
	case 5:
		alpha -= 0.1;
		mm->tagSetAlpha(alpha);
		lastMessage->setAlpha((sin(sinSource) + 1) * 0.5 * alpha);
		sinSource += 0.05;
		if (alpha <= 0) {
			endFlag = true;
		}
		break;
	}
}
