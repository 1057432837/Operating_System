#include "graphic.h"
#include "global.h"
#include "stdio.h"
#include "bootpack.h"
#include "dsctbl.h"
#include "int.h"

char fonts[16] = {
//A

    0x00, 0x18, 0x18, 0x18, 0x18, 0x24, 0x24, 0x24,
    0x24, 0x7e, 0x42, 0x42, 0x42, 0xe7, 0x00, 0x00

//B
// {
//     0x00, 0xfc, 0x82, 0x81, 0x81, 0x81, 0x82, 0xfc,
//     0x82, 0x81, 0x81, 0x81, 0x82, 0xfc, 0x00, 0x00
// }
};


char cursor[16][16] = {
    "**************..",
	"*OOOOOOOOOOO*...",
	"*OOOOOOOOOO*....",
	"*OOOOOOOOO*.....",
	"*OOOOOOOO*......",
	"*OOOOOOO*.......",
	"*OOOOOOO*.......",
	"*OOOOOOOO*......",
	"*OOOO**OOO*.....",
	"*OOO*..*OOO*....",
	"*OO*....*OOO*...",
	"*O*......*OOO*..",
	"**........*OOO*.",
	"*..........*OOO*",
	"............*OO*",
	".............***"
};

void set_palette(int start, int end, unsigned char* rgb) {
    int i, eflags;
    eflags = io_load_eflags();
    io_cli();
    io_out8(0x03c8, start);
    for (i = start; i <= end; i++)
    {
        io_out8(0x03c9, rgb[0] / 4);
        io_out8(0x03c9, rgb[1] / 4);
        io_out8(0x03c9, rgb[2] / 4);
        rgb += 3;
    }
    io_store_eflags(eflags);
    return;
}

void init_palette(void) {
    static unsigned char table_rgb[16 * 3] = {
        0x00, 0x00, 0x00,
        0xff, 0x00, 0x00,
        0x00, 0xff, 0x00,
        0xff, 0xff, 0x00,
        0x00, 0x00, 0xff,
        0xff, 0x00, 0xff,
        0x00, 0xff, 0xff,
        0xff, 0xff, 0xff,
        0xc6, 0xc6, 0xc6,
        0x84, 0x00, 0x00,
        0x00, 0x84, 0x00,
        0x84, 0x84, 0x00,
        0x00, 0x00, 0x84,
        0x84, 0x00, 0x84,
        0x00, 0x84, 0x84,
        0x84, 0x84, 0x84,
    };
    set_palette(0, 15, table_rgb);
    return;
}

void boxfill8(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1) {
    int x, y;
    for (y = y0; y <= y1; y++)
    {
        for (x = x0; x <= x1; x++)
        {
           vram[y * xsize + x] = c;
        }
    }
    return;
}

void init_screen8(unsigned char *vram, int xsize, int ysize) {
    boxfill8(vram, xsize, COL8_008484,          0,          0,  xsize - 1, ysize - 29);
    boxfill8(vram, xsize, COL8_c6c6c6,          0, ysize - 28,  xsize - 1, ysize - 28);
    boxfill8(vram, xsize, COL8_FFFFFF,          0, ysize - 27,  xsize - 1, ysize - 27);
    boxfill8(vram, xsize, COL8_c6c6c6,          0, ysize - 26,  xsize - 1,  ysize - 1);
    boxfill8(vram, xsize, COL8_FFFFFF,          3, ysize - 24,         59, ysize - 24);
    boxfill8(vram, xsize, COL8_FFFFFF,          2, ysize - 24,          2,  ysize - 4);
    boxfill8(vram, xsize, COL8_848484,          3,  ysize - 4,         59,  ysize - 4);
    boxfill8(vram, xsize, COL8_848484,         59, ysize - 23,         59,  ysize - 5);
    boxfill8(vram, xsize, COL8_000000,          2,  ysize - 3,         59,  ysize - 3);
    boxfill8(vram, xsize, COL8_000000,         60, ysize - 24,         60,  ysize - 3);
    boxfill8(vram, xsize, COL8_848484, xsize - 47, ysize - 24,  xsize - 4, ysize - 24);
    boxfill8(vram, xsize, COL8_848484, xsize - 47, ysize - 23, xsize - 47,  ysize - 4);
    boxfill8(vram, xsize, COL8_FFFFFF, xsize - 47,  ysize - 3,  xsize - 4,  ysize - 3);
    boxfill8(vram, xsize, COL8_FFFFFF,  xsize - 3, ysize - 24,  xsize - 3,  ysize - 3);
}

void putfont8(unsigned char *vram, int xsize, int x, int y, char c, char *font) {
    int i;
    char *p, d;
    for (i = 0; i < 16; i++)
    {
        p = vram + (y + i) * xsize + x;
        d = font[i];
        if ((d & 0x80) != 0)
        {
            p[0] = c;
        }
        if ((d & 0x40) != 0)
        {
            p[1] = c;
        }
        if ((d & 0x20) != 0)
        {
            p[2] = c;
        }
        if ((d & 0x10) != 0)
        {
            p[3] = c;
        }
        if ((d & 0x08) != 0)
        {
            p[4] = c;
        }
        if ((d & 0x04) != 0)
        {
            p[5] = c;
        }
        if ((d & 0x02) != 0)
        {
            p[6] = c;
        }
        if ((d & 0x01) != 0)
        {
            p[7] = c;
        }
    }
    return;
}

void putfonts8_asc(unsigned char *vram, int xsize, int x, int y, char c, unsigned char *s) {
    for (; *s != 0x00; s++)
    {
        putfont8(vram, xsize, x, y, c, fonts + *s * 16);   //书上p96暂未解决
        x += 8;
    }
    return;
}

void init_mouse_cursor8(char *mouse, char bc) {
    // extern cursor[16][16];
    int x, y;
    for (y = 0; y < 16; y++)
    {
        for (x = 0; x < 16; x++)
        {
            if (cursor[y][x] == '*')
            {
                mouse[y * 16 + x] = COL8_000000;
            }
            if (cursor[y][x] == 'O')
            {
                mouse[y * 16 + x] = COL8_FFFFFF;
            }
            if (cursor[y][x] == '.')
            {
                mouse[y * 16 + x] = bc;
            }
            
        }
        
    }
    return;
}

void putblock8_8(unsigned char *vram, int vxsize, int pxsize, int pysize, int px0, int py0, char *buf, int bxsize) {
    int x, y;
    for (y = 0; y < pysize; y++)
    {
        for (x = 0; x < pxsize; x++)
        {
            vram[(py0 + y) * vxsize + (px0 + x)] = buf[y * bxsize + x];
        }
    }
    return;
}

void init_screen(void) {
    struct BOOTINFO *binfo = (struct BOOTINFO*)ADR_BOOTINFO;
    char mcursor[256];
    int mx, my;

    init_gdtidt();
    init_pic();
    io_sti();

    binfo->vram = (unsigned char*)0xa0000;
    binfo->scrnx = 320;
    binfo->scrny = 200;
    init_palette();
    init_screen8(binfo->vram, binfo->scrnx, binfo->scrny);
    mx = (binfo->scrnx - 16) / 2; /* 计算画面的中心坐标*/
	my = (binfo->scrny - 28 - 16) / 2;

    init_mouse_cursor8(mcursor, COL8_008484);
    putblock8_8(binfo->vram, binfo->scrnx, 16, 16, mx, my, mcursor, 16);

    putfont8(binfo->vram, binfo->scrnx, 20, 20, COL8_FFFFFF, fonts);

    io_out8(PIC0_IMR, 0xf9);
	io_out8(PIC1_IMR, 0xef);
    
}