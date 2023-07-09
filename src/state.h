#pragma once

// The size of the grid.
#define GRID_WIDTH 8
#define GRID_HEIGHT 6
#define GRID_TILES (GRID_WIDTH * GRID_HEIGHT)

// Converts some coordinates into the linear index.
#define GRID_IDX(x, y) (GRID_WIDTH * y + x)

// Flag: is currently visible.
#define FLAG_SHOWN 0x01
// Flag: is marked with a flag.
#define FLAG_FLAG 0x02

#define STATE_GAMEOVER 0x01
#define STATE_REPAINT 0x02
#define STATE_PAINTGAMEOVER 0x04
#define STATE_NEEDS_RESET 0x08

#define STATE_GET(var) (gamestate.state & var)
#define STATE_SET(var) (gamestate.state |= var)
#define STATE_UNSET(var) (gamestate.state &= ~var)

struct state {
	// Binary state.
	int state;
	
	// Logical state.
	int timer;
	int ticks;
	int mines;

	// Actual gameplay.
	unsigned char tiles[GRID_TILES];
	
	// The flag for each one of the cells.
	unsigned char flags[GRID_TILES];
	
	// Cursor
	int cursor_x, cursor_y;
};

extern struct state gamestate;

unsigned state_tick();
void state_reset();
void state_waitforgameover();
