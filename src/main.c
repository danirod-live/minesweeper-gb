#include <gb/gb.h>
#include <stdint.h>

#include "../res/sweeper_tiles.h"
#include "../res/sweeper_back.h"

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
