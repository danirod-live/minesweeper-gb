#include <gb/gb.h>
#include "sprite.h"
#include "state.h"
#include "../res/tiles.h"

#define SPRITE_OFFSET_X 30
#define SPRITE_OFFSET_Y 52

#define SPRITE_SEPARATION 16
#define SPRITE_POS(cursor) (SPRITE_SEPARATION * cursor)
#define SPRITE_POS_X(cursor) (SPRITE_OFFSET_X + SPRITE_POS(cursor))
#define SPRITE_POS_Y(cursor) (SPRITE_OFFSET_Y + SPRITE_POS(cursor))

void
sprite_load(void)
{
	SPRITES_8x8;
	set_sprite_data(0, 7, sweeper_sprites);
	SHOW_SPRITES;
	
	set_sprite_tile(0, 0);
	set_sprite_tile(1, 1);
	set_sprite_tile(2, 4);
	set_sprite_tile(3, 2);
	set_sprite_tile(4, 3);
	set_sprite_tile(5, 6);
}

void
sprite_redraw(void)
{
	int i;
	if (STATE_GET(STATE_GAMEOVER)) {
		for (i = 0; i < 7; i++) {
			hide_sprite(i);
		}
		return;
	}
	move_sprite(0, SPRITE_POS_X(gamestate.cursor_x), SPRITE_POS_Y(gamestate.cursor_y));
	move_sprite(1, SPRITE_POS_X(gamestate.cursor_x), SPRITE_POS_Y(gamestate.cursor_y) + 8);
	move_sprite(2, SPRITE_POS_X(gamestate.cursor_x), SPRITE_POS_Y(gamestate.cursor_y) + 16);
	move_sprite(3, SPRITE_POS_X(gamestate.cursor_x) + 8, SPRITE_POS_Y(gamestate.cursor_y));
	move_sprite(4, SPRITE_POS_X(gamestate.cursor_x) + 8, SPRITE_POS_Y(gamestate.cursor_y) + 8);
	move_sprite(5, SPRITE_POS_X(gamestate.cursor_x) + 8, SPRITE_POS_Y(gamestate.cursor_y) + 16);
}
