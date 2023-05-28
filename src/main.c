#include <gb/gb.h>
#include <stdint.h>

#include "../res/sweeper_tiles.h"
#include "../res/sweeper_back.h"

#include "vars.h"
#include "timer.h"
#include "mines.h"





void main(void)
{
	set_bkg_data(0, sweeper_tilesLen, sweeper_tiles);
	set_bkg_tiles(0, 0, 20, 18, sweeper_backend);

	timer_reset();
	reset_mines();

	SHOW_BKG;
	
    // Loop forever
    while(1) {


		// Game main loop processing goes here


		// Done processing, yield CPU and wait for start of next frame
        wait_vbl_done();
		timer_tick();
    }
}
