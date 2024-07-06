#ifndef __KERNEL_PALETTE_H
#define __KERNEL_PALETTE_H

void init_palette(void);
void set_palette(int start, int end, unsigned char* rgb);

#endif