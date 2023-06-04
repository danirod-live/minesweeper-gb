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

// { base + 0, base + 2, base + 1, base + 3};
void grid_repaint()
{

}
