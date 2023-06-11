#include "grid.h"
#include "state.h"

#include <gb/gb.h>
#include <string.h>

// The base tile in the tileset where the sprites to be used for tile start.
#define TILE_SPRITE_BASE 36

// Some special tile indices.
#define TILE_EMPTY 0
#define TILE_BOMB 9
#define TILE_FLAG 10

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

#define TILE_SPRITE(val) (TILE_SPRITE_BASE + 4 * val)

static void
grid_update_tileset()
{
	unsigned x, y;
	int value, sprite, spritepos;
	
	// I still haven't figured out how using linear fors here would help me,
	// therefore I am just going to use a two-coordinate loop here, to
	// place my tiles.
	for (y = 0; y < GRID_HEIGHT; y++) {
		for (x = 0; x < GRID_WIDTH; x++) {
			value = gamestate.tiles[GRID_IDX(x, y)];
			sprite = TILE_SPRITE(value);
			spritepos = TILESET_IDX(x, y);
			
			// Ugh... this is going to be ugly, I am sorry.
			grid_tileset[spritepos] = sprite + 0;
			grid_tileset[spritepos + 1] = sprite + 2;
			grid_tileset[spritepos + GRID_WIDTH * 2] = sprite + 1;
			grid_tileset[spritepos + GRID_WIDTH * 2 + 1] = sprite + 3;
		}
	}
}

// { base + 0, base + 2, base + 1, base + 3};
void grid_repaint()
{
	grid_update_tileset();
	set_bkg_tiles(TILE_SPRITE_X, TILE_SPRITE_Y, GRID_WIDTH * 2, GRID_HEIGHT * 2, grid_tileset);
}
