#include "print.h"
#include "init.h"
#include "fork.h"
#include "stdio.h"
#include "syscall.h"
#include "assert.h"
#include "shell.h"
#include "console.h"
#include "ide.h"
#include "stdio-kernel.h"

#define COL8_000000   0
#define COL8_FF0000   1
#define COL8_00FF00   2
#define COL8_FFFF00   3
#define COL8_0000FF   4
#define COL8_FF00FF   5
#define COL8_00FFFF   6
#define COL8_FFFFFF   7
#define COL8_c6c6c6   8
#define COL8_840000   9
#define COL8_008400   10
#define COL8_848400   11
#define COL8_000084   12
#define COL8_840084   13
#define COL8_008484   14
#define COL8_848484   15

extern void io_cli(void);
extern void io_out8(int port, int data);
extern int io_load_eflags(void);
extern void io_store_eflags(int eflags);

void init(void);
void init_palette(void);
void set_palette(int start, int end, unsigned char* rgb);
void boxfill8(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1);

int main(void)
{
    // put_str("I am kernel\n");
    // init_all();

    // uint32_t file_size = 21816;
    // uint32_t sec_cnt = DIV_ROUND_UP(file_size, 512);
    // struct disk *sda = &channels[0].devices[0];
    // void *prog_buf = sys_malloc(file_size);
    // ide_read(sda, 300, prog_buf, sec_cnt);
    // int32_t fd = sys_open("/cat", O_CREAT | O_RDWR);
    // if (fd != -1)
    // {
    //     if (sys_write(fd, prog_buf, file_size) == -1)
    //     {
    //         printk("file write error!\n");
    //         while (1)
    //             ;
    //     }
    // }

    // cls_screen();
    // console_put_str("[rabbit@localhost /]$ ");
    // thread_exit(running_thread(), true);
    // return 0;
    char *p;
    init_palette();
    p = (char*) 0xa0000;

    boxfill8(p, 320, COL8_FF0000, 20, 20, 120, 120);
    boxfill8(p, 320, COL8_00FF00, 70, 50, 170, 150);
    boxfill8(p, 320, COL8_0000FF, 120, 80, 220, 180);

    while (1);
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

/* init进程 */
void init(void)
{
    uint32_t ret_pid = fork();
    if (ret_pid)
    { // 父进程
        int status;
        int child_pid;
        /* init在此处不停的回收僵尸进程 */
        while (1)
        {
            child_pid = wait(&status);
            printf("I`m init, My pid is 1, I recieve a child, It`s pid is %d, status is %d\n", child_pid, status);
        }
    }
    else
    { // 子进程
        my_shell();
    }
    panic("init: should not be here");
}
