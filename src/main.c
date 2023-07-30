#include <gb/gb.h>
#include <stdint.h>

#include "../res/pal_game.h"
#include "../res/pal_cursor.h"
#include "../res/pal_intro.h"
#include "../res/map_intro.h"
#include "../res/map_game.h"

#include "state.h"
#include "sound.h"
#include "hud.h"
#include "grid.h"
#include "sprite.h"
#include "input.h"
#include "savegame.h"

static void
wait_for_nokey()
{
	while (joypad()) {
		wait_vbl_done();
	}
}

static void
wait_for_start()
{
	uint8_t start = 0, joy;

	while (!start) {
		// Check if START or A is pressed.
		joy = joypad();
		start = joy & (J_START | J_A);
		wait_vbl_done();
	}
}

void
main_menu()
{
	// Load the front assets.
	HIDE_BKG;
	set_bkg_data(0, pal_introLen, pal_intro);
	set_bkg_tiles(0, 0, 20, 18, map_intro);

	ENABLE_RAM_MBC1;
	if (max_timer > 999) {
		max_timer = 999;
	}
	hud_draw_maxtimer();
	DISABLE_RAM_MBC1;
	SHOW_BKG;
	
	wait_for_nokey();
	wait_for_start();
	sound_peep();
	wait_for_nokey();
}

void
main_game()
{
	HIDE_BKG;
	set_bkg_data(0, pal_gameLen, pal_game);
	set_bkg_tiles(0, 0, 20, 18, map_game);
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

	HIDE_SPRITES;
	
	// while (sound_isplaying());
	if (STATE_GET(STATE_GAMEOVER)) {
		STATE_SET(STATE_PAINTGAMEOVER);
	} else if (STATE_GET(STATE_GAMEWIN)) {
		ENABLE_RAM_MBC1;
		if (gamestate.timer < max_timer) {
			max_timer = gamestate.timer;
		}
		DISABLE_RAM_MBC1;
		STATE_SET(STATE_PAINTWIN);
	}

	grid_repaint();
	hud_repaint();
	wait_for_nokey();
	wait_for_start();
}

void
main(void)
{
	for (;;) {
		main_menu();
		main_game();
	}
}
