#include <string.h>
#include <rand.h>

#include "state.h"

struct state gamestate;

static void
state_setmines()
{
	int i, rnd;
	
	for (i = 0; i < gamestate.mines; i++) {
		do {
			rnd = rand() % GRID_TILES;
		} while (gamestate.tiles[rnd]);
		gamestate.tiles[rnd] = 9;
	}
}

void
state_computebounds()
{
	uint8_t tile, x, y, count;
	int dx, dy;
	
	for (y = 0; y < GRID_HEIGHT; y++) {
		for (x = 0; x < GRID_WIDTH; x++) {
			tile = GRID_IDX(x, y);
			if (gamestate.tiles[tile] == 9) {
				continue;
			}
			
			count = 0;
			for (dy = y - 1; dy <= y + 1; dy++) {
				for (dx = x - 1; dx <= x - 1; dx++) {
					if (dx < 0 || dy < 0 || dx >= GRID_WIDTH || dy >= GRID_HEIGHT) {
						continue;
					}
					if (gamestate.tiles[GRID_IDX(dx, dy)] == 9) {
						count++;
					}
				}
			}
			gamestate.tiles[tile] = count;
		}
	}
}

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
	gamestate.mines = 8;
	gamestate.cursor_x = 0;
	gamestate.cursor_y = 0;
	memset(gamestate.tiles, 0, GRID_TILES);
	state_setmines();
	state_computebounds();
}
