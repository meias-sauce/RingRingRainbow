#pragma once

#define LOAD_DIV_MAX 8
#define EXTEND_RATE 1.0

void AllLoad();

class C_Graph;
class C_Sound;
class C_Font;

//素材は全部ここで宣言した後、Resource.cpp内でロードする

extern C_Graph graph_wheel[2];
extern C_Graph graph_ball[2];
extern C_Graph graph_emitter[2];
extern C_Graph graph_logo[2];
extern C_Graph graph_message[2];

extern C_Sound sound_ball[2];
extern C_Sound sound_bgm;
extern C_Sound sound_start;
extern C_Sound sound_message;
extern C_Sound sound_cursor;

extern C_Font font_cine;

//以下クラス定義

class C_Graph {
public:
	int Handle;
	int HandleArray[LOAD_DIV_MAX];
	int sizeX, sizeY;
	void Load(char *filename, int _mode = 0, int AllNum = 0, int XNum = 0, int YNum = 0, int Div_sizeX = 0, int Div_sizeY = 0);
};

class C_Sound {
public:
	int Handle;
	int soundtype;
	int volume_default = 100;
	static int volume_music;
	static int volume_se;
	void Load(const char* filename, int SEorMusic = 0, int volume_def = 100);
	void Play();
};

class C_Font {
public:
	int Handle;
	void Load(const char* fontname, const char* filename, int fontsize = -1, int thick = -1, int fonttype = (0x02));
};