#include "DxLib.h"
#include "Resource.h"
#include "main.h"
#include "keyboard.h"
#include "GameObject.h"
#include "Ball_Color.h"
#include "../resource/resource.h"

Wheel* wheel;
Emitter* emitter;
Title* title;
MessageManager* mm;
std::list<GameObject*> obj;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetOutApplicationLogValidFlag(FALSE);
	ChangeWindowMode(TRUE);
	SetGraphMode(600, 600, 32);
	SetWindowSize(600, 600);
	SetAlwaysRunFlag(true);

	SetDXArchiveKeyString("nijinoko");
	SetDXArchiveExtension("sgp");

	//アイコンファイルの読み込み
	SetWindowIconID(IDI_ICON2);
	//ウィンドウタイトルの設定
	SetMainWindowText("RingRingRainbow -ver 0.8");


	if (DxLib_Init() == -1) {
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	//素材全部ロード
	AllLoad();

	//ウィンドウサイズ取得
	int width, height;
	GetWindowSize(&width, &height);

	unsigned int frame = 0;


	//GameObjectまとめリストを作成
	obj = std::list<GameObject*>();

	//とりあえずWheelとEmitterをぶちこむ
	/*wheel = new Wheel(width / 2, height / 2);
	obj.push_back(wheel);
	emitter = new Emitter(wheel->getX(), wheel->getY());
	obj.push_back(emitter);*/

	mm = new MessageManager();
	

	title = new Title();
	obj.push_back(title);

	obj.push_back(mm);

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && gpUpdateKey() == 0) {
		clsDx();

		for (auto i = obj.begin(); i != obj.end();) {
			//Processを回す
			(*i)->Process();
			//Drawを回す
			(*i)->Draw();

			//endFlagが立ってたらメモリ解放してリストからも追い出す
			if ((*i)->endFlag) {
				delete (*i);
				i = obj.erase(i);
			}
			else {
				//立ってなかったら次に行こう
				++i;
			}
		}

		frame++;
	}
	DxLib_End();
	return 0;
}