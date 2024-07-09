#ifndef __KERNEL_MOUSE_H
#define __KERNEL_MOUSE_H

extern char cursor[16][16];

void init_mouse_cursor8(char *mouse, char bc);
void putblock8_8(unsigned char *vram, int vxsize, int pxsize, int pysize, int px0, int py0, char *buf, int bxsize);

#endif