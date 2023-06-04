#include <string.h>

#include "state.h"

struct state gamestate;

unsigned
state_tick()
{
	if (++gamestate.ticks > 60) {
		gamestate.ticks -= 60;
		gamestate.timer++;
		return 1;
	}
	return 0;
}

void state_reset()
{
	gamestate.timer = 0;
	gamestate.ticks = 0;
	gamestate.mines = 10;
	memset(gamestate.tiles, 0, GRID_TILES);
}
