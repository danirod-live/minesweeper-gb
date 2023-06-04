#include <gb/gb.h>
#include <stdint.h>

#include "../res/sweeper_tiles.h"
#include "../res/sweeper_back.h"
#include "../res/tiles.h"

#include "state.h"
#include "hud.h"
#include "grid.h"

void main(void)
{
	set_bkg_data(0, sweeper_tilesLen, sweeper_tiles);
	set_bkg_tiles(0, 0, 20, 18, sweeper_backend);
	

	state_reset();
	grid_repaint();
	hud_repaint();

	SHOW_BKG;
	
	SPRITES_8x8;
	set_sprite_data(0, 4, sweeper_sprites);
	SHOW_SPRITES;
	set_sprite_tile(0, 0);
	set_sprite_tile(1, 1);
	set_sprite_tile(2, 2);
	set_sprite_tile(3, 3);

	// Loop forever.
	while(1) {
		// Yield CPU and wait for the next frame.
		wait_vbl_done();
		
		// Tick the game state and maybe repaint the counters.
		if (state_tick()) {
			hud_repaint();
		}
	}
}
