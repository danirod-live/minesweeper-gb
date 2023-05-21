#include <gb/gb.h>
#include <stdint.h>

#include "../res/sweeper_tiles.h"
#include "../res/sweeper_back.h"

int score = 0;
int time = 0;

static unsigned char sweeper_front_timer[] = { 0x18, 0x18,0x18 };
static unsigned char sweeper_front_score[] = {0x18, 0x18, 0x18};

void main(void)
{
	set_bkg_data(0, 34, sweeper_tiles);
	set_bkg_tiles(0, 0, 20, 18, sweeper_backend);
	set_bkg_tiles(5, 1, 3, 1, sweeper_front_score);
	set_bkg_tiles(14, 1, 3, 1, sweeper_front_score);
	SHOW_BKG;
	
    // Loop forever
    while(1) {


		// Game main loop processing goes here


		// Done processing, yield CPU and wait for start of next frame
        wait_vbl_done();
    }
}
