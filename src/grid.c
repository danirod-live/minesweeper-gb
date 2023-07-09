#include "grid.h"
#include "state.h"
#include "sound.h"

#include <gb/gb.h>
#include <string.h>

// The base tile in the tileset where the sprites to be used for tile start.
#define TILE_SPRITE_BASE 36

// Some special tile indices.
#define TILE_BOMB 9
#define TILE_FLAG 10
#define TILE_UNDISCOVERED 11

// These are the offsets from the top of the screen on where the background
// tiles for the grid start. They have to be added for any framebuffer
// coordinate used when painting grids.
#define TILE_SPRITE_X 2
#define TILE_SPRITE_Y 4

static unsigned char grid_tileset[GRID_TILES * 4];

// Converts an (x, y) coordinate in the framebuffer coordinate system into
// the lineal position of grid_tileset that maps to the top-left of this
// specific tile. (Remember to do +1 on the sides for the four tiles).
#define TILESET_IDX(x, y) (4 * GRID_WIDTH * y + 2 * x)

// The actual sprite index (offseted to avoid drawing the borders.)
#define TILE_SPRITE(val) (TILE_SPRITE_BASE + 4 * val)

static void grid_paint16(unsigned int x, unsigned int y, unsigned int sprite)
{
	unsigned int spritepos = TILESET_IDX(x, y);
	
	grid_tileset[spritepos] = sprite + 0;
	grid_tileset[spritepos + 1] = sprite + 2;
	grid_tileset[spritepos + GRID_WIDTH * 2] = sprite + 1;
	grid_tileset[spritepos + GRID_WIDTH * 2 + 1] = sprite + 3;
}

static void
grid_update_tileset()
{
	unsigned x, y;
	int value, sprite;
	
	// I still haven't figured out how using linear fors here would help me,
	// therefore I am just going to use a two-coordinate loop here, to
	// place my tiles.
	for (y = 0; y < GRID_HEIGHT; y++) {
		for (x = 0; x < GRID_WIDTH; x++) {
			// If the tile is visible, put the sprite value of the tile.
			// Supposedly this tile will encode a value between 0 and 9 (inclusive)
			// with the number of bombs that are around. (0 is an empty tile,
			// and 9 is drawing a bomb.)
			if (gamestate.flags[GRID_IDX(x, y)] & FLAG_SHOWN) {
				value = gamestate.tiles[GRID_IDX(x, y)];
			}
			// If the flag is marked with a flag, use the flag sprite.
			else if (gamestate.flags[GRID_IDX(x, y)] & FLAG_FLAG) {
				value = TILE_FLAG;
			}
			// Use the wall sprite because we don't know what is there.
			else {
				value = TILE_UNDISCOVERED;
			}
			sprite = TILE_SPRITE(value);
			grid_paint16(x, y, sprite);
		}
	}
}

static void
grid_paint_gameover()
{
	grid_paint16(2, 2, 96);
	grid_paint16(2, 3, 100);
	grid_paint16(3, 2, 104);
	grid_paint16(3, 3, 108);
	grid_paint16(4, 2, 112);
	grid_paint16(4, 3, 116);
	grid_paint16(5, 2, 120);
	grid_paint16(5, 3, 124);
}

// { base + 0, base + 2, base + 1, base + 3 };
void grid_repaint()
{
	grid_update_tileset();
	if (STATE_GET(STATE_PAINTGAMEOVER)) {
		grid_paint_gameover();
	}
	set_bkg_tiles(TILE_SPRITE_X, TILE_SPRITE_Y, GRID_WIDTH * 2, GRID_HEIGHT * 2, grid_tileset);
}

void grid_unlock(uint8_t x, uint8_t y)
{
	register int id = GRID_IDX(x, y);
	if (!gamestate.flags[id]) {
		gamestate.flags[id] |= FLAG_SHOWN;
		if (gamestate.tiles[id] == TILE_BOMB && gamestate.flags[id] | FLAG_SHOWN) {
			sound_gameover();
			STATE_SET(STATE_GAMEOVER);
			STATE_SET(STATE_REPAINT);
		}
	}
}

void grid_toggle_flag(uint8_t x, uint8_t y)
{
	if (gamestate.flags[GRID_IDX(x, y)] & FLAG_SHOWN) {
		return;
	}
	if (gamestate.flags[GRID_IDX(x, y)] & FLAG_FLAG) {
		gamestate.flags[GRID_IDX(x, y)] &= ~FLAG_FLAG;
		gamestate.mines++;
	} else {
		gamestate.flags[GRID_IDX(x, y)] |= FLAG_FLAG;
		gamestate.mines--;
	}
}
