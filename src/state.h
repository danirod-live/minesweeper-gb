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
#define STATE_STARTED 0x08

#define STATE_GET(var) (gamestate.state & var)
#define STATE_SET(var) (gamestate.state |= var)
#define STATE_UNSET(var) (gamestate.state &= ~var)

struct state {
	// Binary state.
	int state;
	
	// Logical state.
	int lastsecond;
	int timer;
	int ticks;
	int mines;

	// TODO: maybe compact these arrays into a single array?
	// It is totally possible to pack the bits into a single
	// unsigned char:
	//
	// 7 6 5 4 3 2 1 0
	//   NUMBERS v F *
	//   |       | | |-> * = mines
	//   |       | |---> F = flagged
	//   |       |-----> v = opened
	//   |-------------> NUMBERS = precomputed numbers

	// 1 for each position if there is a mine
	unsigned char positions[GRID_TILES];
	// the precomputed number of mines around each tile
	unsigned char numbers[GRID_TILES];
	// the positions that have been marked by the user
	unsigned char flags[GRID_TILES];

	int cursor_x, cursor_y;
};

extern struct state gamestate;

unsigned state_tick();
void state_reset();
void state_waitforgameover();
void state_setnumbers();
