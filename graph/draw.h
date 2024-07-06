#ifndef __KERNEL_DRAW_H
#define __KERNEL_DRAW_H

void boxfill8(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1);
void draw_desktop(unsigned char *vram, int xsize, int ysize);

#endif
