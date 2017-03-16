#ifndef _DEFINE_H
#define _DEFINE_H

//不同难度下的雷区信息
#define PRIMARY_MINENUM 10
#define PRIMARY_X 10
#define PRIMARY_Y 10
#define MEDIUM_MINENUM 40
#define MEDIUM_X 16
#define MEDIUM_Y 16
#define ADVANCE_MINENUM 99
#define ADVANCE_X 30
#define ADVANCE_Y 16

//颜色信息
#define WHITE RGB(255,255,255)
#define GRAY RGB(192,192,192)
#define DARK_GRAY RGB(128,128,128)

//雷方块信息
#define MINE_SIZE 16

enum GAME_MODE{PRIMARY,MEDIUM,ADVANCE};
enum BUTTON_STATE{CLICKED,WIN,DEAD,CLICKMINE,NORMAL};
enum MINE_STATE{MINE_NORMAL,MINE_MARKED,MINE_QUESTIONED,MINE_EXPLODE,MINE_WRONGMINE,MINE_ISMINE,MINE_CLICKED,MINE_DETECTED};
enum COLOR_MODE{COLOR_COLOR,COLOR_GRAY};

class CMine:public CObject
{
public:
	MINE_STATE state;
	int x;         //雷方块的x坐标
	int y;         //y坐标
	int NearMine;  //如果该方块不是雷，则该变量记录其周围的雷数
	bool IsMine;
	CMine(){}
};



#endif