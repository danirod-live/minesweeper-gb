#include "mines.h"
#include "vars.h"
#include <gb/gb.h>

static void
draw_counter(int decimal, unsigned char *sprites)
{
    unsigned int ptr = 3;

    // Paint a minus sign if the number is negative.
    if (decimal < 0) {
        sprites[0] = SPRITE_NUMBER_BASE + 12;
    }

    // Clamp the number (hold your horse, dude)
    if (decimal > 999) {
        decimal = 999;
    } else if (decimal < -999) {
        decimal = -999;
    }
    if (decimal < 0) {
        decimal *= -1;
    }
    sprites[3] = decimal % 10 + SPRITE_NUMBER_BASE;
    decimal /= 10;
    sprites[2] = decimal % 10 + SPRITE_NUMBER_BASE;
    decimal /= 10;
    sprites[1] = decimal % 10 + SPRITE_NUMBER_BASE;
}

static void
repaint_mines()
{
    draw_counter(mines, sprite_mines);
    set_bkg_tiles(13, 1, 4, 1, sprite_mines);
}

void
mark_mine(void)
{
    mines--;
    repaint_mines();
}

void
unmark_mine(void)
{
    mines++;
    repaint_mines();
}

void
reset_mines(void)
{
    mines = 10;
    repaint_mines();
}