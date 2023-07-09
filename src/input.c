#include "input.h"
#include "state.h"
#include "grid.h"
#include "hud.h"
#include "sound.h"
#include <gb/gb.h>
#include <stdint.h>

// TODO: move these variables to state.h
uint8_t frames = 0;

// Used in order to detect when the user presses B to stop
// keyboard events until you release the B key again.
// Otherwise, it toggles the flag on every frame.
static uint8_t holding_flag_key = 0;
static uint8_t holding_activate_key = 0;

#define J_CRUCETA (J_UP | J_DOWN | J_LEFT | J_RIGHT)

static void
activate_key(void)
{
	if (!holding_activate_key) {
		grid_unlock(gamestate.cursor_x, gamestate.cursor_y);
		sound_activate();
		STATE_SET(STATE_REPAINT);
		holding_activate_key = 1;
	}
}

static void
check_first()
{
	unsigned int x, y, pos;
	int is_invalid = 0;
	
	if (STATE_GET(STATE_NEEDS_RESET)) {
		x = gamestate.cursor_x;
		y = gamestate.cursor_y;
		pos = GRID_IDX(x, y);
		
		do {
			state_reset();
			is_invalid = gamestate.tiles[pos] == 9;
		} while (is_invalid);
		gamestate.cursor_x = x;
		gamestate.cursor_y = y;
	}
}

static void
toggle_flag(void)
{
	if (!holding_flag_key) {
		grid_toggle_flag(gamestate.cursor_x, gamestate.cursor_y);
		holding_flag_key = 1;
		STATE_SET(STATE_REPAINT);
		sound_flag();
	}
}

void
input_check(void)
{
	int input = joypad();
	
	if (STATE_GET(STATE_GAMEOVER)) {
		return;
	}

	if (frames == 0) {
		if (input & J_UP) {
			sound_peep();
			if (gamestate.cursor_y > 0)
				gamestate.cursor_y--;
		}
		if (input & J_DOWN) {
			sound_peep();
			if (gamestate.cursor_y < GRID_HEIGHT-1)
				gamestate.cursor_y++;
		}
		if (input & J_LEFT) {
			sound_peep();
			if (gamestate.cursor_x > 0)
				gamestate.cursor_x--;
		}
		if (input & J_RIGHT) {
			sound_peep();
			if (gamestate.cursor_x < GRID_WIDTH-1)
				gamestate.cursor_x++;
		}
	}

	// If the user presses A, unlock the tile where the cursor is.
	if (input & J_A) {
		check_first();
		activate_key();
	} else {
		holding_activate_key = 0;
	}

	if (input & J_B) {
		toggle_flag();
	} else {
		// Because the user is not holding the B any more, raise flag.
		holding_flag_key = 0;
	}

	// Number of consecutive frames where the keypad has been pressed.
	if (input & J_CRUCETA) {
		if (++frames == 60)
			frames = 0;
	} else {
		frames = 0;
	}
}
