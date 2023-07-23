#include <gb/gb.h>
#include <stdint.h>

#include "../res/sweeper_tiles.h"
#include "../res/sweeper_back.h"
#include "../res/intro_tiles.h"
#include "../res/front.h"
#include "../res/tiles.h"

#include "state.h"
#include "hud.h"
#include "grid.h"
#include "sprite.h"
#include "input.h"

void
main_menu()
{
	// Load the front assets.
	HIDE_BKG;
	set_bkg_data(0, intro_tilesLen, intro_tiles);
	set_bkg_tiles(0, 0, 20, 18, front);
	SHOW_BKG;

	// Paint the main menu screen.
	uint8_t start = 0, joy;

	while (!start) {
		// Check if START or A is pressed.
		joy = joypad();
		start = joy & (J_START | J_A);
	}
}

void
main_game()
{
	HIDE_BKG;
	set_bkg_data(0, sweeper_tilesLen, sweeper_tiles);
	set_bkg_tiles(0, 0, 20, 18, sweeper_backend);
	sprite_load();
	state_reset();
	SHOW_BKG;
	
	STATE_SET(STATE_REPAINT);
	
	// Loop until you lose.
	while(!STATE_GET(STATE_GAMEOVER) && !STATE_GET(STATE_GAMEWIN)) {
		// Input
		input_check();

		// Tick the game state and maybe repaint the counters.
		if (state_tick()) {
			STATE_SET(STATE_REPAINT);
		}

		if (STATE_GET(STATE_REPAINT)) {
			grid_repaint();
			hud_repaint();
			sprite_redraw();
		}

		// Yield CPU and wait for the next frame.
		wait_vbl_done();
	}
	
	while (sound_isplaying());
	if (STATE_GET(STATE_GAMEOVER)) {
		STATE_SET(STATE_PAINTGAMEOVER);
	} else if (STATE_GET(STATE_GAMEWIN)) {
		STATE_SET(STATE_PAINTWIN);
	}
	
	while (1) {
		grid_repaint();
		hud_repaint();
		
		// Yield CPU and wait for the next frame.
		wait_vbl_done();
	}
}

void
main(void)
{
	for (;;) {
		main_menu();
		main_game();
	}
}
