#pragma once

#include <stdint.h>

#define GRAPH_WIDTH			(1280)
#define GRAPH_HEIGH			(640)
#define GRAPH_DENSITY		(20)			// 画布个体密度（短边上的个体线密度，如：值为10时表示短边上大概有10个）

#define LIFE_SIZE			(15)				// 生命个体的尺寸（方形边长）

#define LIFEGAME_SURVIVALLIFE_SUR_MAX			(3)			// 存活个体下一代成活条件上限
#define LIFEGAME_SURVIVALLIFE_SUR_MIN			(2)			// 存活个体下一代成活条件下限
#define LIFEGAME_DEATHLIFE_SUR_MAX				(3)			// 死亡个体下一代成活条件上限
#define LIFEGAME_DEATHLIFE_SUR_MIN				(3)			// 死亡个体下一代成活条件下限
