#include <gb/gb.h>
#include <stdint.h>

#include "../res/sweeper_tiles.h"
#include "../res/sweeper_back.h"
#include "../res/tiles.h"

#include "state.h"
#include "hud.h"
#include "grid.h"
#include "sprite.h"
#include "input.h"

void init(void)
{
	set_bkg_data(0, sweeper_tilesLen, sweeper_tiles);
	set_bkg_tiles(0, 0, 20, 18, sweeper_backend);
	SHOW_BKG;
	sprite_load();
}

void main(void)
{
	init();
	
	state_reset();
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
