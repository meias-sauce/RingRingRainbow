#include "HSVColor.h"
#include "DxLib.h"

HSVColor::HSVColor(int h, int s, int v)
{
	this->h = h;
	this->s = s;
	this->v = v;
}


HSVColor::~HSVColor()
{
}

void HSVColor::huePlus(int plusNum) {
	h += plusNum;
	if (h >= 360) {
		h -= 360;
	}
}

void HSVColor::SetDrawBrightHSV()
{
	int r, g, b;
	double max = v * 2.55;
	double min = max - ((s * 0.01) * max);

	if (h >= 0 && h < 60) {
		r = (int)max;
		g = (int)(((double)h / 60.0) * (max - min) + min);
		b = (int)min;

	}
	else if (h >= 60 && h < 120) {
		r = (int)((((double)(120 - h)) / 60.0) * (max - min) + min);
		g = (int)max;
		b = (int)min;
	}
	else if (h >= 120 && h < 180) {
		r = (int)min;
		g = (int)max;
		b = (int)(((double)(h - 120) / 60.0) * (max - min) + min);
	}
	else if (h >= 180 && h < 240) {
		r = (int)min;
		g = (int)(((double)(240 - h) / 60.0) * (max - min) + min);
		b = (int)max;
	}
	else if (h >= 240 && h < 300) {
		r = (int)(((double)(h - 240) / 60.0) * (max - min) + min);
		g = (int)min;
		b = (int)max;
	}
	else if (h >= 300 && h < 360) {
		r = (int)max;
		g = (int)min;
		b = (int)(((double)(360 - h) / 60.0) * (max - min) + min);
	}
	else {
		printf("‚â‚×‚¥‚æc");
	}

	SetDrawBright(r, g, b);
}

void HSVColor::DrawHSV(int x, int y, double ExtRate, double Angle, int GrHandle)
{
	SetDrawBrightHSV();
	DrawRotaGraph(x, y, ExtRate, Angle, GrHandle, TRUE);
	SetDrawBright(255, 255, 255);
}

void HSVColor::DrawHSV(int x, int y, int GrHandle)
{
	SetDrawBrightHSV();
	DrawGraph(x, y, GrHandle, TRUE);
	SetDrawBright(255, 255, 255);
}

void HSVColor::DrawHSV(int x1, int y1, int x2, int y2)
{
	SetDrawBrightHSV();
	DrawBox(x1, y1, x2, y2, GetColor(255, 255, 255), true);
	SetDrawBright(255, 255, 255);
}
