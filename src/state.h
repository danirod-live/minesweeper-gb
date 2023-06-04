#pragma once

// The size of the grid.
#define GRID_WIDTH 8
#define GRID_HEIGHT 6
#define GRID_TILES (GRID_WIDTH * GRID_HEIGHT)

// Converts some coordinates into the linear index.
#define GRID_IDX(x, y) (GRID_WIDTH * y + x)

struct state {
	// Logical state.
	int timer;
	int ticks;
	int mines;

	// Actual gameplay.
	unsigned char tiles[GRID_TILES];
	
	// Cursor
	int cursor_x, cursor_y;
};

extern struct state gamestate;

unsigned state_tick();
void state_reset();
