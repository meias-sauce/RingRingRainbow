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
}


Title::~Title()
{
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

		//ゲーム開始処理へ
		if (Key[KEY_INPUT_Z]) {
			decisionFlag = true;
			sound_start.Play();
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
		if (abs(y - 300) < 1) {
			y = 300;
			accelY = 0; veloY = 0;
		}
		else {
			veloX = (300 - x) * std::sin(sinSource);
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
		if (x == 300 && y == 300 && alpha == 0 && wheelExtend == 1 && wheelBright == 255) {
			endFlag = true;
			wheel = new Wheel(x, y, angle, frame, rotateSpeed);
			emitter = new Emitter(x, y);
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
}

