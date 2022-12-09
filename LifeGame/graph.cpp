#include <graphics.h>
#include <conio.h>
#include "graph.h"

#include "sdkconfig.h"

void graphInit(void) {
	initgraph(GRAPH_WIDTH, GRAPH_HEIGH);
	setbkcolor(WHITE);
	cleardevice();
}
