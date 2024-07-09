#ifndef __KERNEL_GDTIDT_H
#define __KERNEL_GDTIDT_H

struct SEGMENT_DESCRIPTOR {
    short limit_low, base_low;
    char base_mid, access_right;
    char limit_high, base_high;
};

struct GATE_DESCRIPTOR {
    short offset_low, selector;
    char dw_count, access_right;
    short offset_high;
};

extern void load_gdtr(int limit, int addr);
extern void load_idtr(int limit, int addr);
void set_segmdesc(struct SEGMENT_DESCRIPTOR *sd, unsigned int limit, int base, int ar);
void set_gatedesc(struct GATE_DESCRIPTOR *gd, int offset, int selector, int ar);
void init_gdtidt(void);

#endif