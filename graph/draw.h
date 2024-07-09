#ifndef __KERNEL_DRAW_H
#define __KERNEL_DRAW_H

struct BOOTINFO
{
    char cyls, leds, vmode, reserve;
    short scrnx, scrny;
    unsigned char *vram;
};

void boxfill8(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1);
void draw_screen(unsigned char *vram, int xsize, int ysize);
void init_screen(void);

#endif
