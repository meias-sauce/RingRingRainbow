#include "MessageManager.h"

MessageManager::MessageManager() : GameObject(0, 0)
{
	defaultTag = "__default";
	defaultCoolTime = 0;
}

MessageManager::~MessageManager()
{
	for (auto i = message.begin(); i != message.end(); i++) {
		delete(*i);
	}
	message.clear();
}

void MessageManager::Process()
{
	for (auto i = message.begin(); i != message.end(); i++) {
		(*i)->Process();
	}
}

void MessageManager::Draw()
{
	for (auto i = message.begin(); i != message.end(); i++) {
		(*i)->Draw();
	}
}

void MessageManager::add(double x, double y, const char * text, const char * tag)
{
	message.push_back(new Message(x, y, text, tag, defaultCoolTime));
}


void MessageManager::add(double x, double y, const char * text) {
	add(x, y, text, defaultTag.c_str());
}

void MessageManager::setTag(const char* tag) {
	defaultTag = tag;
}

void MessageManager::setCoolTime(int coolTime) {
	defaultCoolTime = coolTime;
}

void MessageManager::tagDelete() {
	for (auto i = message.begin(); i != message.end();) {
		if ((*i)->getTag() == defaultTag) {
			//“Á’è‚Ìƒ^ƒO‚ðíœ
			delete(*i);
			i = message.erase(i);
		}
		else {
			i++;
		}
	}
}

void MessageManager::tagSetAlpha(double alpha)
{
	for (auto i = message.begin(); i != message.end(); i++) {
		if ((*i)->getTag() == defaultTag) {
			(*i)->setAlpha(alpha * this->alpha);
		}
	}
}
