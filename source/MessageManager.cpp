#include "MessageManager.h"

MessageManager* MessageManager::instance = nullptr;


MessageManager::MessageManager() : GameObject(0, 0)
{
	defaultTag = "__default";
	defaultCoolTime = 0;
}

MessageManager * MessageManager::getInstance()
{
	if (instance == nullptr) {
		instance = new MessageManager();
	}
	return instance;
}

void MessageManager::deleteInstance()
{
	if (instance != nullptr) {
		delete instance;
		instance = nullptr;
	}
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

Message* MessageManager::add(double x, double y, const char * text, const char * tag)
{
	Message* newMessage = new Message(x, y, text, tag, defaultCoolTime);
	message.push_back(newMessage);
	return newMessage;
}


Message* MessageManager::add(double x, double y, const char * text) {
	return add(x, y, text, defaultTag.c_str());
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
			//特定のタグを削除
			delete(*i);
			i = message.erase(i);
		}
		else {
			i++;
		}
	}
}

void MessageManager::messageDelete(Message* target) {
	for (auto i = message.begin(); i != message.end();) {
		if ((*i) == target) {
			//特定のメッセージを削除するやべーやつ
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

void MessageManager::setAlpha(double alpha) {
	this->alpha = alpha;
	for (auto i = message.begin(); i != message.end(); i++) {
		(*i)->multiAlpha(alpha);
	}
}
