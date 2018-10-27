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

public:
	Message(double, double, const char*, const char*, int = 6);
	~Message();
	void Process();
	void Draw();

	const char* getTag();
};

