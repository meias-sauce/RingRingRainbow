#pragma once
#include "GameObject.h"
#include "Message.h"
#include <list>
#include <string>

class MessageManager : public GameObject
{
private:
	std::list<Message*> message;

	std::string defaultTag;
	int defaultCoolTime;
	//int default;

public:
	MessageManager();
	~MessageManager();
	void Process();
	void Draw();
	
	Message* add(double, double, const char*, const char*);
	Message* add(double, double, const char*);
	void setTag(const char * tag);
	void setCoolTime(int coolTime);
	void tagDelete();
	void messageDelete(Message *);
	void tagSetAlpha(double);
	void setAlpha(double alpha);
};