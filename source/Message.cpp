#include "Message.h"
#include "Resource.h"
#include "DxLib.h"
#include <Windows.h>

void Message::step()
{
	if (!text.empty()) {
		if (IsDBCSLeadByte(text[0]) == 0) {
			currentText += text[0];
			text = text.substr(1, text.size() - 1);
		}
		else {
			currentText = currentText + text[0] + text[1];
			text = text.substr(2, text.size() - 1);
		}
	}
	else {
		isFinishString = true;
	}
}

Message::Message(double x, double y, const char* text, const char* tag, int coolTime) : GameObject(x, y)
{
	this->text = text;
	this->coolTime = coolTime;
	this->tag = tag;
	currentText.clear();
	isFinishString = false;
	fontHandle = font_cine.Handle;
}


Message::~Message()
{
}

void Message::Process() {
	GameObject::Process();
	if (coolTime == 0) {
		currentText += text;
		text.clear();
		isFinishString = true;
	}
	else if (frame % coolTime == 0) {
		if (!isFinishString) {
			step();
		}
		else {
			//endFlag = true;
		}
	}
}

void Message::Draw() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * alpha);
	DrawFormatStringToHandle(x, y, GetColor(255, 255, 255), fontHandle, currentText.c_str());
	//printfDx(currentText.c_str());
}

const char * Message::getTag()
{
	return tag.c_str();
}

void Message::setAlpha(double alpha)
{
	this->alpha = alpha;
}

void Message::multiAlpha(double alpha) {
	this->alpha *= alpha;
}

void Message::setVelo(double veloX, double veloY) {
	this->veloX = veloX;
	this->veloY = veloY;
}

void Message::setFont(int fontHandle) {
	this->fontHandle = fontHandle;
}

//•¶š—ñ‚ğÅŒã‚Ü‚Å•\¦‚µ‚Ä‚¢‚ê‚Îtrue
bool Message::getIsEmpty() {
	if (text == "") {
		return true;
	}
	else {
		return false;
	}
}