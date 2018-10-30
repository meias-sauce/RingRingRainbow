#include "Resource.h"
#include "DxLib.h"


C_Graph graph_wheel[2];
C_Graph graph_ball[2];
C_Graph graph_emitter[2];
C_Graph graph_logo[2];
C_Graph graph_message[2];

C_Sound sound_ball[2];
C_Sound sound_bgm;
C_Sound sound_start;
C_Sound sound_message;
C_Sound sound_cursor;
C_Sound sound_gameover;

C_Font font_cine;

void AllLoad() {
	//画像
	graph_wheel[0].Load("graph/wheel_alpha.png");
	graph_wheel[1].Load("graph/wheel.png");

	graph_ball[0].Load("graph/ball_alpha.png", 1, 7, 7, 1, 40, 40);
	graph_ball[1].Load("graph/ball.png", 1, 7, 7, 1, 40, 40);

	graph_emitter[0].Load("graph/emitter.png");
	graph_emitter[1].Load("graph/emitter_alpha.png");

	graph_logo[0].Load("graph/title_logo.png");
	graph_logo[1].Load("graph/title_logoshadow.png");

	graph_message[0].Load("graph/message.png");
	graph_message[1].Load("graph/message_shadow.png");

	//音声
	sound_ball[0].Load("sound/delete.ogg");
	sound_ball[1].Load("sound/bound.ogg", 0, 80);
	sound_bgm.Load("sound/bgm.ogg", 1, 50);
	sound_start.Load("sound/start.ogg", 0, 40);
	sound_message.Load("sound/message.ogg");
	sound_cursor.Load("sound/cursor.ogg");
	sound_gameover.Load("sound/gameover.ogg", 0, 60);


	//フォント
	font_cine.Load("しねきゃぷしょん", "font/cinecaption226.ttf", 30);
}



//画像クラス
//第2引数が0でLoad,1でLoadDiv
void C_Graph::Load(char *filename, int _mode, int AllNum, int XNum, int YNum, int Div_sizeX, int Div_sizeY) {
	switch (_mode) {
	case 0:Handle = LoadGraph(filename); 	GetGraphSize(Handle, &sizeX, &sizeY); break;
	case 1:LoadDivGraph(filename, AllNum, XNum, YNum, Div_sizeX, Div_sizeY, HandleArray);	GetGraphSize(HandleArray[0], &sizeX, &sizeY); break;
	}
}

//音声クラス
//第2引数が0でSE,1でMusic　第3引数はパーセンテージで基本ボリューム設定
void C_Sound::Load(const char * filename, int SEorMusic, int volume_def) {
	soundtype = SEorMusic;
	Handle = LoadSoundMem(filename);
	volume_default = volume_def;
	ChangeVolumeSoundMem(255 * volume_default / 100, Handle);
}

void C_Sound::Play() {
	if (soundtype == 0) {
		ChangeVolumeSoundMem(255 * volume_default * volume_se / 10000, Handle);
		PlaySoundMem(Handle, DX_PLAYTYPE_BACK);
	}
	else {
		ChangeVolumeSoundMem(255 * volume_default * volume_music / 10000, Handle);
		PlaySoundMem(Handle, DX_PLAYTYPE_LOOP);
	}
}

void C_Sound::Stop() {
	StopSoundMem(Handle);
}

int C_Sound::volume_music = 100;
int C_Sound::volume_se = 100;

void C_Font::Load(const char * fontname, const char * filename, int fontsize, int thick, int fonttype) {
	int filesize = FileRead_size(filename);
	int filehandle = FileRead_open(filename);
	void *buffer = malloc(filesize);
	FileRead_read(buffer, filesize, filehandle);
	DWORD font_num = 0;
	if (AddFontMemResourceEx(buffer, filesize, NULL, &font_num) != 0) {}
	else {
		MessageBox(NULL, "フォント読込失敗", "", MB_OK);
		return;
	}
	Handle = CreateFontToHandle(fontname, fontsize, thick, fonttype);
}