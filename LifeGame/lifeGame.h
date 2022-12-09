#ifndef __LIFEGAME_H
#define __LIFEGAME_H

#include "sdkconfig.h"
#include <easyx.h>

/*========================================
	����״̬
========================================*/

typedef uint32_t LifePixel_State_t;

/*========================================
	����״̬
========================================*/

enum LifePixel_State{
	LIFEGAME_SURVIVAL = BLACK,
	LIFEGAME_DEATH = WHITE
};

/*========================================
	���������ı���
========================================*/

/* �������� */
extern LifePixel_State_t LifeGame_Graph[GRAPH_WIDTH][GRAPH_HEIGH];

/*========================================
	������Ϸ����
========================================*/

/* ��ʼ�� */
void life_Random_Init(void);
void life_DoubleVerticalBar_Init(void);
void life_DoubleLineCross_Init(void);

/* չʾ */
void show_LifeState(void);

/* ���� */
void update_NextGeneration(void);

#endif /* __LIFEGAME_H */
