#include "input.h"
#include "state.h"
#include "grid.h"
#include "hud.h"
#include <gb/gb.h>
#include <stdint.h>

// TODO: move these variables to state.h
uint8_t frames = 0;

// Used in order to detect when the user presses B to stop
// keyboard events until you release the B key again.
// Otherwise, it toggles the flag on every frame.
static uint8_t holding_flag_key = 0;

#define J_CRUCETA (J_UP | J_DOWN | J_LEFT | J_RIGHT)

static void
toggle_flag(void)
{
	if (!holding_flag_key) {
		grid_toggle_flag(gamestate.cursor_x, gamestate.cursor_y);
		holding_flag_key = 1;
		STATE_SET(STATE_REPAINT);
	}
}

void
input_check(void)
{
	int input = joypad();

	if (frames == 0) {
		if (input & J_UP) {
			if (gamestate.cursor_y > 0)
				gamestate.cursor_y--;
		}
		if (input & J_DOWN) {
			if (gamestate.cursor_y < GRID_HEIGHT-1)
				gamestate.cursor_y++;
		}
		if (input & J_LEFT) {
			if (gamestate.cursor_x > 0)
				gamestate.cursor_x--;
		}
		if (input & J_RIGHT) {
			if (gamestate.cursor_x < GRID_WIDTH-1)
				gamestate.cursor_x++;
		}
	}

	// If the user presses A, unlock the tile where the cursor is.
	if (input & J_A) {
		grid_unlock(gamestate.cursor_x, gamestate.cursor_y);
		STATE_SET(STATE_REPAINT);
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
