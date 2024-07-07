extern char fonts[26][16];

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