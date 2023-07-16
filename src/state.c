#include <string.h>
#include <rand.h>
#include <gb/gb.h>
#include <time.h>

#include "state.h"
#include "sound.h"

struct state gamestate;

// state_setmines will place mines.
static void
state_setmines()
{
	int i, rnd;
	
	for (i = 0; i < gamestate.mines; i++) {
		do {
			rnd = rand() % GRID_TILES;
		} while (gamestate.positions[rnd]);
		gamestate.positions[rnd] = 1;
	}
}

void
state_setnumbers()
{
	uint8_t tile, x, y, count;
	int dx, dy;
	
	for (y = 0; y < GRID_HEIGHT; y++) {
		for (x = 0; x < GRID_WIDTH; x++) {
			tile = GRID_IDX(x, y);
			if (gamestate.positions[tile]) {
				gamestate.numbers[tile] = 9;
				continue;
			}
			count = 0;
			for (dy = y - 1; dy <= y + 1; dy++) {
				for (dx = x - 1; dx <= x + 1; dx++) {
					if (dx < 0 || dy < 0 || dx >= GRID_WIDTH || dy >= GRID_HEIGHT) {
						continue;
					}
					if (gamestate.positions[GRID_IDX(dx, dy)]) {
						count++;
					}
				}
			}
			gamestate.numbers[tile] = count;
		}
	}
}

unsigned
state_tick()
{
	int seconds;
	if (STATE_GET(STATE_GAMEOVER)) {
		return 0;
	}
	if (STATE_GET(STATE_STARTED)) {
		time(&seconds);
		if (gamestate.lastsecond != seconds) {
			gamestate.timer++;
			gamestate.lastsecond = seconds;
			return 1;
		}
	}
	return 0;
}

void state_reset()
{
	initrand(DIV_REG);
	gamestate.state = 0;
	gamestate.timer = 0;
	gamestate.ticks = 0;
	gamestate.mines = 8;
	gamestate.cursor_x = 0;
	gamestate.cursor_y = 0;
	memset(gamestate.numbers, 0, GRID_TILES);
	memset(gamestate.positions, 0, GRID_TILES);
	memset(gamestate.flags, 0, GRID_TILES);
	state_setmines();
	state_setnumbers();
}
