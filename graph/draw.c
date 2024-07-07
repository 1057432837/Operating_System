#include "draw.h"
#include "global.h"
#include "palette.h"
#include "font.h"
#include "stdio.h"

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

void draw_screen(unsigned char *vram, int xsize, int ysize) {
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

void putfont8(char *vram, int xsize, int x, int y, char c, char *font) {
    int i;
    char d;
    for (i = 0; i < 16; i++)
    {
        d = font[i];
        if ((d & 0x80) != 0)
        {
            vram[(y + i) * xsize + x + 0] = c;
        }
        if ((d & 0x40) != 0)
        {
            vram[(y + i) * xsize + x + 1] = c;
        }
        if ((d & 0x20) != 0)
        {
            vram[(y + i) * xsize + x + 2] = c;
        }
        if ((d & 0x10) != 0)
        {
            vram[(y + i) * xsize + x + 3] = c;
        }
        if ((d & 0x08) != 0)
        {
            vram[(y + i) * xsize + x + 4] = c;
        }
        if ((d & 0x04) != 0)
        {
            vram[(y + i) * xsize + x + 5] = c;
        }
        if ((d & 0x02) != 0)
        {
            vram[(y + i) * xsize + x + 6] = c;
        }
        if ((d & 0x01) != 0)
        {
            vram[(y + i) * xsize + x + 7] = c;
        }
    }
    return;
}

void putfonts8_asc(char *vram, int xsize, int x, int y, char c, unsigned char *s) {
    for (; *s != 0x00; s++)
    {
        putfont8(vram, xsize, x, y, c, fonts + *s * 16);   //书上p96暂未解决
        x += 8;
    }
    return;
}





void init_screen() {
    // char *vram;
    // int xsize, ysize;
    struct BOOTINFO *binfo = (struct BOOTINFO*)0x0ff0;

    init_palette();

    binfo->vram = (char*)0xa0000;
    binfo->scrnx = 320;
    binfo->scrny = 200;
    draw_screen(binfo->vram, binfo->scrnx, binfo->scrny);

    putfont8(binfo->vram, binfo->scrnx, 20, 20, COL8_FFFFFF, fonts[0]);

    char s[40];
    printf(s, "scrnx = %d", binfo->scrnx);
    putfonts8_asc(binfo->vram, binfo->scrnx, 8, 8, COL8_FFFFFF, s);
    
    char mcursor[256];
    int mx, my;
    mx = (binfo->scrnx - 16) / 2; /* 计算画面的中心坐标*/
	my = (binfo->scrny - 28 - 16) / 2;
    init_mouse_cursor8(mcursor, COL8_008484);
    putblock8_8(binfo->vram, binfo->scrnx, 16, 16, mx, my, mcursor, 16);
    
}