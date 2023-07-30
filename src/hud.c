#include <gb/gb.h>

#include "hud.h"
#include "state.h"
#include "savegame.h"

#define NUMSPRITE_BASE 24
#define NUMSPRITE_BLANK -NUMSPRITE_BASE
#define NUMSPRITE_PLUS 10
#define NUMSPRITE_MINUS 11

// The actual tiles from the tileset related to the
// timer that gets copied into framebuffer whenever
// repaint() is called.
static unsigned char hud_tiles_timer[4];

// The actual tiles from the tileset related to the
// mines that gets copied into framebuffer whenever
// repaint() is called.
static unsigned char hud_tiles_mines[4];

// Additionally, provide some macros to reduce the
// ceremony required to update the value of a sprite.
#define SET_TIMER_SPRITE(i, value) \
	(hud_tiles_timer[i] = NUMSPRITE_BASE + value)
#define SET_MINES_SPRITE(i, value) \
	(hud_tiles_mines[i] = NUMSPRITE_BASE + value)

static void
hud_update_timer()
{
	int value;

	// Copy the variable here because it will get rekt.
	value = gamestate.timer;

	// Test for overflow.
	if (value > 999) {
		SET_TIMER_SPRITE(0, NUMSPRITE_PLUS);
		SET_TIMER_SPRITE(1, 9);
		SET_TIMER_SPRITE(2, 9);
		SET_TIMER_SPRITE(3, 9);
	} else {
		SET_TIMER_SPRITE(3, value % 10);
		value /= 10;
		SET_TIMER_SPRITE(2, value % 10);
		value /= 10;
		SET_TIMER_SPRITE(1, value % 10);
		SET_TIMER_SPRITE(0, NUMSPRITE_BLANK);
	}
}

static void
hud_update_mines()
{
	int value;

	// Copy the variable here because it will get rekt.
	value = gamestate.mines;

	// Paint a minus sign if the mines are negative.
	if (value < 0) {
		SET_MINES_SPRITE(0, NUMSPRITE_MINUS);
		value *= -1;
	} else {
		SET_MINES_SPRITE(0, NUMSPRITE_BLANK);
	}

	SET_MINES_SPRITE(3, value % 10);
	value /= 10;
	SET_MINES_SPRITE(2, value % 10);
	value /= 10;
	SET_MINES_SPRITE(1, value % 10);
}

static void
hud_copy()
{
	set_bkg_tiles(4, 1, 4, 1, hud_tiles_timer);
	set_bkg_tiles(13, 1, 4, 1, hud_tiles_mines);
}

void
hud_repaint()
{
	hud_update_timer();
	hud_update_mines();
	hud_copy();
}

static uint8_t
maxtimer_positions[] = {
	//  0         1         2         3        4
	103, 104, 105, 114, 115, 116, 117, 118, 119, 120,
	//  5        6          7         8        9
	121, 122, 123, 124, 125, 126, 134, 135, 136, 137
};
#define MAXTIMER_POS_X 15
#define MAXTIMER_POS_Y 5

void
hud_draw_maxtimer()
{
	uint8_t upper[3], lower[3];
	uint16_t value, c, d, u;
	value = max_timer;
	u = value % 10;
	value /= 10;
	d = value % 10;
	value /= 10;
	c = value % 10;

	upper[0] = maxtimer_positions[c * 2];
	lower[0] = maxtimer_positions[c * 2 + 1];
	upper[1] = maxtimer_positions[d * 2];
	lower[1] = maxtimer_positions[d * 2 + 1];
	upper[2] = maxtimer_positions[u * 2];
	lower[2] = maxtimer_positions[u * 2 + 1];

	set_bkg_tiles(MAXTIMER_POS_X, MAXTIMER_POS_Y, 3, 1, upper);
	set_bkg_tiles(MAXTIMER_POS_X, MAXTIMER_POS_Y + 1, 3, 1, lower);
}