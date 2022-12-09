#include "lifeGame.h"
#include "sdkconfig.h"
#include "myMem.h"
#include <assert.h>
#include <easyx.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

LifePixel_State_t LifeGame_Graph[GRAPH_WIDTH][GRAPH_HEIGH];

/**
 * @fn static LifePixel_State_t read_LifeState(uint16_t x, uint16_t y)
 * @brief ��д��λ����״̬
 * @param x �жϵĸ���ĺ�����
 * @param y �жϵĸ����������
 * @return LifePixel_State_t
 */
static LifePixel_State_t read_LifeState(uint16_t x, uint16_t y) {
	return LifeGame_Graph[x * LIFE_SIZE][y * LIFE_SIZE];
}

/**
 * @fn static LifePixel_State_t set_LifeState(uint16_t x, uint16_t y, LifePixel_State_t nextGene_State)
 * @brief ��д��λ����״̬
 * @param x �жϵĸ���ĺ�����
 * @param y �жϵĸ����������
 * @param nextGene_State ��λ������һ����״̬
 * @return LifePixel_State_t
 */
static LifePixel_State_t set_LifeState(uint16_t x, uint16_t y, LifePixel_State_t nextGene_State) {
	uint16_t r, l;
	LifePixel_State_t pareGene_State;  // ��ǰ��һ���õ�λ������״̬

	pareGene_State = LifeGame_Graph[x * LIFE_SIZE][y * LIFE_SIZE];
	for (l = 0; l < LIFE_SIZE; l++) for (r = 0; r < LIFE_SIZE; r++)
		LifeGame_Graph[x * LIFE_SIZE + l][y * LIFE_SIZE + r] = nextGene_State;

	return pareGene_State;
}

/**
 * @fn void life_Random_Init(void)
 * @brief �����ʼ�������ֲ�
 * @return void
 */
void life_Random_Init(void) {
	uint16_t i, j;

	myMemset_Uint32_t((uint32_t*)LifeGame_Graph, LIFEGAME_DEATH, sizeof(LifeGame_Graph) / sizeof(uint32_t));
	srand((unsigned int)time(NULL));
	for (i = 0; i < GRAPH_WIDTH / LIFE_SIZE; i++) {
		for (j = 0; j < GRAPH_HEIGH / LIFE_SIZE; j++) {
			if (!(rand() % GRAPH_HEIGH % (((uint16_t)min(GRAPH_WIDTH, GRAPH_HEIGH)) / LIFE_SIZE) / GRAPH_DENSITY)) {
				set_LifeState(i, j, LIFEGAME_SURVIVAL);
			}
		}
	}
}

/**
 * @fn void life_DoubleVerticalBar_Init(void)
 * @brief ��ʼ�������ֲ�Ϊ��������
 * @return void
 */
void life_DoubleVerticalBar_Init(void) {
	uint16_t i, j;

	myMemset_Uint32_t((uint32_t*)LifeGame_Graph, LIFEGAME_DEATH, sizeof(LifeGame_Graph) / sizeof(uint32_t));
	for (i = 0; i < 2; i++) {
		for (j = 0; j < GRAPH_HEIGH; j++) {
			if(i == 0) LifeGame_Graph[GRAPH_WIDTH / 2 - 4][j] = LIFEGAME_SURVIVAL;
			else LifeGame_Graph[GRAPH_WIDTH / 2 + 4][j] = LIFEGAME_SURVIVAL;
		}
	}
}

/**
 * @fn void life_DoubleLineCross_Init(void)
 * @brief ��ʼ�������ֲ�Ϊ˫��ʮ��
 * @return void
 */
void life_DoubleLineCross_Init(void) {
	uint16_t i, j;

	myMemset_Uint32_t((uint32_t*)LifeGame_Graph, LIFEGAME_DEATH, sizeof(LifeGame_Graph) / sizeof(uint32_t));
	for (i = 0; i < 2; i++) {
		for (j = 0; j < GRAPH_HEIGH; j++) {
			if (i == 0) LifeGame_Graph[GRAPH_WIDTH / 2 - 4][j] = LIFEGAME_SURVIVAL;
			else LifeGame_Graph[GRAPH_WIDTH / 2 + 4][j] = LIFEGAME_SURVIVAL;
		}
	}
	for (i = 0; i < 2; i++) {
		for (j = 0; j < GRAPH_WIDTH; j++) {
			if (i == 0) LifeGame_Graph[j][GRAPH_HEIGH / 2 - 4] = LIFEGAME_SURVIVAL;
			else LifeGame_Graph[j][GRAPH_HEIGH / 2 + 4] = LIFEGAME_SURVIVAL;
		}
	}
}

/**
 * @fn void show_LifeState(void)
 * @brief ��ʾ����״̬
 * @return void
 */
void show_LifeState(void) {
	uint16_t i, j;

	for (i = 0; i < GRAPH_WIDTH; i++) {
		for (j = 0; j < GRAPH_HEIGH; j++) {
			putpixel(i, j, LifeGame_Graph[i][j]);
		}
	}
}

/**
 * @fn LifePixel_State_t judge_NextGeneration_Pixel(uint16_t x, uint16_t y)
 * @brief �ж���һ���еĸ���Ӧ���ڵ�״̬
 * @param x �жϵĸ���ĺ�����
 * @param y �жϵĸ����������
 * @return LifePixel_State_t
 */
static LifePixel_State_t judge_NextGeneration_Pixel(uint16_t x, uint16_t y) {
	LifePixel_State_t NeighborValue = 0;  // �������������ĺ�ֵ

	if (x == 0 || y == 0 || x == GRAPH_WIDTH / LIFE_SIZE - 1 || y == GRAPH_HEIGH / LIFE_SIZE - 1) {  // �����ڻ����߽�
		if (x == 0 && y == 0) {  // ���Ͻ�
			if (read_LifeState(  x  , y + 1)	== LIFEGAME_SURVIVAL) NeighborValue++;
			if (read_LifeState(x + 1,   y  )	== LIFEGAME_SURVIVAL) NeighborValue++;
			if (read_LifeState(x + 1, y + 1)	== LIFEGAME_SURVIVAL) NeighborValue++;
		}
		else if (x == GRAPH_WIDTH / LIFE_SIZE - 1 && y == 0) {  // ���Ͻ�
			if (read_LifeState(  x  , y + 1)	== LIFEGAME_SURVIVAL) NeighborValue++;
			if (read_LifeState(x - 1,   y  )	== LIFEGAME_SURVIVAL) NeighborValue++;
			if (read_LifeState(x - 1, y + 1)	== LIFEGAME_SURVIVAL) NeighborValue++;
		}
		else if (x == 0 && y == GRAPH_HEIGH / LIFE_SIZE - 1) {  // ���½�
			if (read_LifeState(  x  , y - 1)	== LIFEGAME_SURVIVAL) NeighborValue++;
			if (read_LifeState(x + 1,   y  )	== LIFEGAME_SURVIVAL) NeighborValue++;
			if (read_LifeState(x + 1, y - 1)	== LIFEGAME_SURVIVAL) NeighborValue++;
		}
		else if (x == GRAPH_WIDTH / LIFE_SIZE - 1 && y == GRAPH_HEIGH / LIFE_SIZE - 1) {  // ���½�
			if (read_LifeState(  x  , y - 1)	== LIFEGAME_SURVIVAL) NeighborValue++;
			if (read_LifeState(x - 1,   y  )	== LIFEGAME_SURVIVAL) NeighborValue++;
			if (read_LifeState(x - 1, y - 1)	== LIFEGAME_SURVIVAL) NeighborValue++;
		}
		else if (x == 0) {  // ��߽�
			if (read_LifeState(  x  , y - 1)	== LIFEGAME_SURVIVAL) NeighborValue++;
			if (read_LifeState(  x  , y + 1)	== LIFEGAME_SURVIVAL) NeighborValue++;
			if (read_LifeState(x + 1, y - 1)	== LIFEGAME_SURVIVAL) NeighborValue++;
			if (read_LifeState(x + 1,   y  )	== LIFEGAME_SURVIVAL) NeighborValue++;
			if (read_LifeState(x + 1, y + 1)	== LIFEGAME_SURVIVAL) NeighborValue++;
		}
		else if (x == GRAPH_WIDTH / LIFE_SIZE - 1) {  // �ұ߽�
			if (read_LifeState(  x  , y - 1)	== LIFEGAME_SURVIVAL) NeighborValue++;
			if (read_LifeState(  x  , y + 1)	== LIFEGAME_SURVIVAL) NeighborValue++;
			if (read_LifeState(x - 1, y - 1)	== LIFEGAME_SURVIVAL) NeighborValue++;
			if (read_LifeState(x - 1,   y  )	== LIFEGAME_SURVIVAL) NeighborValue++;
			if (read_LifeState(x - 1, y + 1)	== LIFEGAME_SURVIVAL) NeighborValue++;
		}
		else if (y == 0) {  // �ϱ߽�
			if (read_LifeState(x - 1,   y  )	== LIFEGAME_SURVIVAL) NeighborValue++;
			if (read_LifeState(x + 1,   y  )	== LIFEGAME_SURVIVAL) NeighborValue++;
			if (read_LifeState(x - 1, y + 1)	== LIFEGAME_SURVIVAL) NeighborValue++;
			if (read_LifeState(  x  , y + 1)	== LIFEGAME_SURVIVAL) NeighborValue++;
			if (read_LifeState(x + 1, y + 1)	== LIFEGAME_SURVIVAL) NeighborValue++;
		}
		else {  // �±߽�
			if (read_LifeState(x - 1,   y  )	== LIFEGAME_SURVIVAL) NeighborValue++;
			if (read_LifeState(x + 1,   y  )	== LIFEGAME_SURVIVAL) NeighborValue++;
			if (read_LifeState(x - 1, y - 1)	== LIFEGAME_SURVIVAL) NeighborValue++;
			if (read_LifeState(  x  , y - 1)	== LIFEGAME_SURVIVAL) NeighborValue++;
			if (read_LifeState(x + 1, y - 1)	== LIFEGAME_SURVIVAL) NeighborValue++;
		}
	}
	else {  // ���岻�ڻ�������
		if (read_LifeState(x - 1, y - 1) == LIFEGAME_SURVIVAL) NeighborValue++;
		if (read_LifeState(x - 1,   y  ) == LIFEGAME_SURVIVAL) NeighborValue++;
		if (read_LifeState(x - 1, y + 1) == LIFEGAME_SURVIVAL) NeighborValue++;
		if (read_LifeState(  x  , y - 1) == LIFEGAME_SURVIVAL) NeighborValue++;
		if (read_LifeState(  x  , y + 1) == LIFEGAME_SURVIVAL) NeighborValue++;
		if (read_LifeState(x + 1, y - 1) == LIFEGAME_SURVIVAL) NeighborValue++;
		if (read_LifeState(x + 1,   y  ) == LIFEGAME_SURVIVAL) NeighborValue++;
		if (read_LifeState(x + 1, y + 1) == LIFEGAME_SURVIVAL) NeighborValue++;
	}

	if (LifeGame_Graph[x * LIFE_SIZE][y * LIFE_SIZE] == LIFEGAME_SURVIVAL) {  // ��һ��������
		if (NeighborValue >= LIFEGAME_SURVIVALLIFE_SUR_MIN && NeighborValue <= LIFEGAME_SURVIVALLIFE_SUR_MAX)
			return LIFEGAME_SURVIVAL;
		else return LIFEGAME_DEATH;
	}
	else  { // ��һ����������
		if (NeighborValue >= LIFEGAME_DEATHLIFE_SUR_MIN && NeighborValue <= LIFEGAME_DEATHLIFE_SUR_MIN)
			return LIFEGAME_SURVIVAL;
		else return LIFEGAME_DEATH;
	}
}

/**
 * @fn void update_NextGeneration(void)
 * @brief ������һ������
 * @return void
 */
void update_NextGeneration(void) {
	uint16_t i, j, r, l;
	LifePixel_State_t temp;
	LifePixel_State_t (*pLifeGame_Next_Graph)[GRAPH_HEIGH] =\
		(LifePixel_State_t(*)[GRAPH_HEIGH])malloc(sizeof(LifePixel_State_t) * GRAPH_WIDTH * GRAPH_HEIGH);

	assert(pLifeGame_Next_Graph);

	for (i = 0; i < GRAPH_WIDTH / LIFE_SIZE; i++) {
		for (j = 0; j < GRAPH_HEIGH / LIFE_SIZE; j++) {
			temp = judge_NextGeneration_Pixel(i, j);
			for (l = 0; l < LIFE_SIZE; l++) for (r = 0; r < LIFE_SIZE; r++) {
				pLifeGame_Next_Graph[i * LIFE_SIZE + l][j * LIFE_SIZE + r] = temp;
			}
		}
	}
	memcpy(LifeGame_Graph, pLifeGame_Next_Graph, sizeof(LifeGame_Graph));

	free(pLifeGame_Next_Graph);
	pLifeGame_Next_Graph = NULL;
}
