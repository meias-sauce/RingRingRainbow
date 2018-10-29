#include "Title.h"
#include "Resource.h"
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include "keyboard.h"
#include "main.h"

Title::Title() : GameObject(175, 210)
{
	hsv = new HSVColor();
	keyLeft = 0;
	keyRight = 0;
	keyUp = 0;
	keyDown = 0;
	rotateSpeed = 0;
	rotateAccel = 0;
	rotateSpeed_Min = 0.0015;
	rotateSpeed_Max = 0.03;
	title_wheelalpha = graph_wheel[1].Handle;
	title_wheel = graph_wheel[0].Handle;
	title_logo = graph_logo[0].Handle;
	title_logoshadow = graph_logo[1].Handle;
	decisionFlag = false;
	wheelExtend = 0.5;
	sinSource = 0;
	wheelBright = 150;
	cursor = new Cursor();

	message->setCoolTime(3);
	message->setTag("title");
	message->add(380, 380, "Start");
	message->add(380, 440, "Tutorial");
	message->add(380, 500, "Quit");
}


Title::~Title()
{
	delete(cursor);
}

void Title::Process()
{
	GameObject::Process();

	if (decisionFlag == false) {
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
		if ((Key[KEY_INPUT_UP] || Key[KEY_INPUT_W])) {
			keyUp++;
		}
		else {
			keyUp = 0;
		}
		if ((Key[KEY_INPUT_DOWN] || Key[KEY_INPUT_S])) {
			keyDown++;
		}
		else {
			keyDown = 0;
		}

		//ゲーム開始処理へ
		if (Key[KEY_INPUT_Z] == 1 && cursor->getIsMoving() == false) {
			switch (cursor->getTo()) {
			case 0:
				decisionFlag = true;
				sound_start.Play();
				break;
			case 1:
				sound_start.Play();
				break;
			case 2:
				DxLib_End();
				break;
			}
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
			if (abs(rotateSpeed) < M_PI * 0.0015) {
				rotateSpeed = M_PI * ((rotateSpeed > 0) ? rotateSpeed_Min : -rotateSpeed_Min);
			}
			else {
				rotateSpeed += M_PI * (rotateSpeed > 0) ? -0.001 : 0.001;
			}
		}

		if (keyUp == 1 && keyDown != 1) {
			cursor->move(-1);
		}
		else if (keyDown == 1 && keyUp != 1) {
			cursor->move(1);
		}


	}
	else {
		//ゲーム開始処理

		sinSource += 0.001;

		//回転減速
		rotateAccel = 0;
		if (abs(rotateSpeed) < M_PI * 0.0015) {
			rotateSpeed = M_PI * ((rotateSpeed > 0) ? rotateSpeed_Min : -rotateSpeed_Min);
		}
		else {
			rotateSpeed += M_PI * (rotateSpeed > 0) ? -0.001 : 0.001;
		}

		//ホイール拡大

		if (abs(1 - wheelExtend) < 0.01) {
			wheelExtend = 1;
		}
		else {
			wheelExtend += 0.1 * std::sin(sinSource);
		}


		//ホイール位置合わせ
		if (abs(x - 300) < 1) {
			x = 300;
			accelX = 0; veloX = 0;
		}
		else {
			veloX = (300 - x) * std::sin(sinSource);
		}
		if (abs(y - 300) < 1) {
			y = 300;
			accelY = 0; veloY = 0;
		}
		else {
			veloY = (300 - y) * std::sin(sinSource);
		}

		//ホイール以外のアルファマイナス
		if (alpha > 0) {
			alpha -= 0.03;
			if (alpha < 0) {
				alpha = 0;
			}
		}

		//ホイールの輝度プラス
		if (wheelBright < 255) {
			wheelBright++;
		}
		else {
			wheelBright = 255;
		}


		//全部終わったらゲーム開始
		if (x == 300 && y == 300 && alpha == 0 && wheelExtend == 1 && wheelBright == 255 && cursor->endFlag) {
			endFlag = true;
			wheel = new Wheel(x, y, angle, frame, rotateSpeed);
			emitter = new Emitter(x, y, cursor->getAngle());
			obj.push_back(wheel);
			obj.push_back(emitter);
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

	//カーソルProcess回す
	cursor->Process(sinSource, decisionFlag);

	//メニュー文字のアルファ値をタイトルロゴと同期
	message->tagSetAlpha(alpha);

	//hsvカラー変更
	hsv->huePlus();
}

void Title::Draw()
{
	SetDrawBright(wheelBright, wheelBright, wheelBright);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (std::sin(frame * 0.1) + 1) * 0.5 * 255);
	DrawRotaGraph(x, y, wheelExtend, angle, title_wheelalpha, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	DrawRotaGraph(x, y, wheelExtend, angle, title_wheel, TRUE);
	SetDrawBright(255, 255, 255);

	SetDrawBlendMode(DX_BLENDMODE_ADD, 255 * alpha);
	hsv->DrawHSV(0, 0, title_logoshadow);
	DrawGraph(0, 0, title_logo, TRUE);
	/*
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	DrawRotaGraph(cursorX, cursorY, 1.0, 0, cursorGraphAlpha, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	DrawRotaGraph(cursorX, cursorY, 1.0, cursorAngle, cursorGraph, TRUE);
	*/
	cursor->Draw();
}

Cursor::Cursor() : GameObject(0, 0)
{
	graphHandle = graph_emitter[0].Handle;
	subGraphHandle = graph_emitter[1].Handle;
	x = 340;
	y = 395;
	isMoving = false;
	to = 0;
}

Cursor::~Cursor()
{
}

void Cursor::Process(double sinSource, bool decisionFlag)
{
	GameObject::Process();


	//ゲーム開始処理
	if (decisionFlag) {
		//カーソル（エミッタ）位置合わせ
		if (abs(x - 300) < 1) {
			x = 300;
		}
		else {
			veloX = (300 - x) * std::sin(sinSource);
		}
		if (abs(y - 300) < 1) {
			y = 300;
		}
		else {
			veloY = (300 - y) * std::sin(sinSource);
		}
		//終了処理
		if (x == 300 && y == 300) {
			endFlag = true;
		}
	}
	else {
		if (isMoving) {
			veloY = (((to * 60) + 395) - y) * 0.2;
			if (abs(veloY) < 0.6) {
				isMoving = false;
				y = (to * 60) + 395;
				veloY = 0;
			}
		}
	}

	//カーソル回転
	angle += (M_PI * 2) / 90;
}

void Cursor::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	DrawRotaGraph(x, y, 1.0, 0, subGraphHandle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	DrawRotaGraph(x, y, 1.0, angle, graphHandle, TRUE);
}

double Cursor::getAngle()
{
	return angle;
}

void Cursor::move(int add) {
	isMoving = true;
	to += add;
	if (to > 2) {
		to -= 3;
	}
	else if (to < 0) {
		to += 3;
	}
}

bool Cursor::getIsMoving()
{
	return isMoving;
}

int Cursor::getTo()
{
	return to;
}
