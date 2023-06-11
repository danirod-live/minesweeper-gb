#include "input.h"
#include "state.h"
#include "grid.h"
#include "hud.h"
#include <gb/gb.h>
#include <stdint.h>

// TODO: move these variables to state.h
uint8_t frames = 0;
uint8_t is_flagging = 0;

#define J_CRUCETA (J_UP | J_DOWN | J_LEFT | J_RIGHT)

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
	
	if (input & J_A) {
		grid_unlock(gamestate.cursor_x, gamestate.cursor_y);
		grid_repaint();
	}
	if (input & J_B) {
		if (!is_flagging) {
			grid_toggle_flag(gamestate.cursor_x, gamestate.cursor_y);
			grid_repaint();
			hud_repaint();
			is_flagging = 1;
		}
	} else {
		is_flagging = 0;
	}
	
	// Number of consecutive frames where the keypad has been pressed.
	if (input & J_CRUCETA) {
		if (++frames == 60)
			frames = 0;
	} else {
		frames = 0;
	}
}
