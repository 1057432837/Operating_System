#ifndef __KERNEL_PALETTE_H
#define __KERNEL_PALETTE_H

extern void io_cli(void);
extern void io_out8(int port, int data);
extern int io_load_eflags(void);
extern void io_store_eflags(int eflags);
void set_palette(int start, int end, unsigned char* rgb);
void init_palette(void);

#endif