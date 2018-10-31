#pragma once
#include "GameObject.h"
#include <string>

class Message :
	public GameObject
{
private:
	std::string text;
	std::string currentText;
	int coolTime;
	std::string tag;

	void step();

	bool isFinishString;

	int fontHandle;

public:
	Message(double, double, const char*, const char*, int);
	~Message();
	void Process();
	void Draw();

	const char* getTag();
	void setAlpha(double);
	void multiAlpha(double alpha);
	void setVelo(double veloX, double veloY);
	void setFont(int fontHandle);
	bool getIsEmpty();
};
