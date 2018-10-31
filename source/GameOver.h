#pragma once
#include "GameObject.h"
#include "Message.h"

class GameOver :
	public GameObject
{
private:
	int phase;
	int score;
	Message* lastMessage;
	double sinSource;

	int keyEnter;

public:
	GameOver(int);
	~GameOver();
	void Process();
};

