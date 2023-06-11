#pragma once

#include <stdint.h>

void grid_repaint();

void grid_unlock(uint8_t x, uint8_t y);

void grid_toggle_flag(uint8_t x, uint8_t y);
