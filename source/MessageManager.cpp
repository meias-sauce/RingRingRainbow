#include "MessageManager.h"

MessageManager::MessageManager() : GameObject(0, 0)
{
	defaultCoolTime = 3;
}

MessageManager::~MessageManager()
{
}

void MessageManager::Process()
{
}

void MessageManager::Draw()
{
}

void MessageManager::add(double x, double y, const char * text, const char * tag)
{
	for (auto i = message.begin(); i != message.end(); i++) {
		if ((*i)->getTag() == tag) {
			//ƒ^ƒO‚ª“¯‚¶‚â‚Â‚¢‚½‚çÁ‚·
		}
	}

	message.push_back(new Message(x, y, text, tag, defaultCoolTime));
}

void MessageManager::add(double x, double y, const char *)
{
}
