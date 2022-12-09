#ifndef __LIFEGAME_H
#define __LIFEGAME_H

#include "sdkconfig.h"
#include <easyx.h>

/*========================================
	生命状态
========================================*/

typedef uint32_t LifePixel_State_t;

/*========================================
	生命状态
========================================*/

enum LifePixel_State{
	LIFEGAME_SURVIVAL = BLACK,
	LIFEGAME_DEATH = WHITE
};

/*========================================
	对外声明的变量
========================================*/

/* 生命画布 */
extern LifePixel_State_t LifeGame_Graph[GRAPH_WIDTH][GRAPH_HEIGH];

/*========================================
	生命游戏函数
========================================*/

/* 初始化 */
void life_Random_Init(void);
void life_DoubleVerticalBar_Init(void);
void life_DoubleLineCross_Init(void);

/* 展示 */
void show_LifeState(void);

/* 更新 */
void update_NextGeneration(void);

#endif /* __LIFEGAME_H */
