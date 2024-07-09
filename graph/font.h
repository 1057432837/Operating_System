#ifndef __KERNEL_FONT_H
#define __KERNEL_FONT_H

extern char fonts[16];

void putfont8(unsigned char *vram, int xsize, int x, int y, char c, char *font);
void putfonts8_asc(unsigned char *vram, int xsize, int x, int y, char c, unsigned char *s);

#endif