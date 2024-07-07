#ifndef __KERNEL_DRAW_H
#define __KERNEL_DRAW_H

struct BOOTINFO
{
    char cyls, leds, vmode, reserve;
    short scrnx, scrny;
    char *vram;
};

void boxfill8(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1);
void draw_screen(unsigned char *vram, int xsize, int ysize);

#endif
