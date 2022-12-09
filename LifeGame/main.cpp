#include <stdio.h>
#include <graphics.h>
#include <conio.h>

#include "sdkconfig.h"
#include "graph.h"
#include "lifeGame.h"

int main()
{
	graphInit();
	BeginBatchDraw();
	life_Random_Init();

	show_LifeState();
	FlushBatchDraw();

	while (!_kbhit()) {
		cleardevice();
		update_NextGeneration();
		show_LifeState();
		FlushBatchDraw();
		//Sleep(10);
	}

	EndBatchDraw();
	closegraph();

	return 0;
}
