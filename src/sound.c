#include <gb/gb.h>

unsigned int
sound_isplaying()
{
	return NR52_REG & 0x1;
}

void
sound_peep()
{
	if (sound_isplaying()) {
		return;
	}
	
	NR52_REG = 0x80;
	NR51_REG = 0x11;
	NR50_REG = 0x77;
	
	NR10_REG = 0x00;
	NR11_REG = 0xDF;
	NR12_REG = 0x63;
	NR13_REG = 0x00;
	NR14_REG = 0xC7;
}

void
sound_activate()
{
	if (sound_isplaying()) {
		return;
	}
	
	NR52_REG = 0x80;
	NR51_REG = 0x11;
	NR50_REG = 0x77;
	
	NR10_REG = 0xC0;
	NR11_REG = 0xB0;
	NR12_REG = 0x56;
	NR13_REG = 0x80;
	NR14_REG = 0xC3;
}

void
sound_flag()
{
	if (sound_isplaying()) {
		return;
	}
	
	NR52_REG = 0x80;
	NR51_REG = 0x11;
	NR50_REG = 0x77;
	
	NR10_REG = 0xC0;
	NR11_REG = 0xB0;
	NR12_REG = 0x56;
	NR13_REG = 0x30;
	NR14_REG = 0xC3;
}

void
sound_gameover()
{
	if (sound_isplaying()) {
		return;
	}
	
	NR52_REG = 0x80;
	NR51_REG = 0x11;
	NR50_REG = 0x77;
	NR10_REG = 0x1E;
	NR11_REG = 0x10;
	NR12_REG = 0xF3;
	NR13_REG = 0x00;
	NR14_REG = 0xC7;
}

void
sound_gamewin()
{
	
}
