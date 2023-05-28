#include "vars.h"
#include <gb/gb.h>

static int timer_ticks = 0;

static void
convert_to_sprite(unsigned int number, unsigned char *sprites)
{
	if (number > 999) {
		sprites[0] = SPRITE_NUMBER_BASE + 10;
		sprites[1] = SPRITE_NUMBER_BASE + 9;
		sprites[2] = SPRITE_NUMBER_BASE + 9;
		sprites[3] = SPRITE_NUMBER_BASE + 9;
	} else {
		sprites[3] = SPRITE_NUMBER_BASE + (number % 10);
		number /= 10;
		sprites[2] = SPRITE_NUMBER_BASE + (number % 10);
		number /= 10;
		sprites[1] = SPRITE_NUMBER_BASE + (number % 10);
		sprites[0] = 0;
	}
}

static void
repaint_timer()
{
    convert_to_sprite(timer, sprite_timer);
    set_bkg_tiles(4, 1, 4, 1, sprite_timer);
}

void
timer_tick()
{
	if (++timer_ticks % 60 == 0) {
		timer_ticks = 0;
		timer++;
		repaint_timer();
	}
}

void
timer_reset()
{
    timer = 0;
    repaint_timer();
}
