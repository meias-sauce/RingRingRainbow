#pragma once
class HSVColor
{
private:
	int h, s, v;
	//int r, g, b;

public:
	HSVColor(int h = 0, int s = 100, int v = 100);
	~HSVColor();
	void huePlus(int plusNum = 1);
	void SetDrawBrightHSV();
	void DrawHSV(int, int, double, double, int);
	void DrawHSV(int, int, int);
	void DrawHSV(int, int, int, int);
};

