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
#include "palette.h"

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

void init(void);
void init_gdtidt();
void set_segmdesc(struct SEGMENT_DESCRIPTOR *sd, unsigned int limit, int base, int ar);
set_gatedesc(struct GATE_DESCRIPTOR *gd, int offset, int selector, int ar);
extern void load_gdtr(int limit, int addr);
extern void load_idtr(int limit, int addr);

int main(void)
{
    // put_str("I am kernel\n");
    init_all();

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

    while (1);
}

void init_gdtidt() {
    struct SEGMENT_DESCRIPTOR *gdt = (struct SEGMENT_DESCRIPTOR*)0x00270000;
    struct GATE_DESCRIPTOR *idt = (struct GATE_DESCRIPTOR*)0x0026f800;

    int i;

    for (i = 0; i < 8192; i++)
    {
        set_segmdesc(gdt + i, 0, 0, 0);
    }
    set_segmdesc(gdt + 1, 0xffffffff, 0x00000000, 0x4092);
    set_segmdesc(gdt + 2, 0x0007ffff, 0x00280000, 0x409a);
    load_gdtr(0xffff, 0x00270000);

    for (i = 0; i < 256; i++)
    {
        set_gatedesc(idt + i, 0, 0, 0);
    }
    load_idtr(0x7ff, 0x0026f800);
    return;
}

void set_segmdesc(struct SEGMENT_DESCRIPTOR *sd, unsigned int limit, int base, int ar) {
    if (limit > 0xfffff)
    {
        ar |= 0x8000;
        limit /= 0x1000;
    }
    sd->limit_low = limit & 0xffff;
    sd->base_low = base & 0xffff;
    sd->base_mid = (base >> 16) & 0xff;
    sd->access_right = ar & 0xff;
    sd->limit_high = ((limit >> 16) & 0x0f) | ((ar >> 8) & 0xf0);
    sd->base_high = (base >> 24) & 0xff;
    return;
}

set_gatedesc(struct GATE_DESCRIPTOR *gd, int offset, int selector, int ar) {
    gd->offset_low = offset & 0xffff;
    gd->selector = selector;
    gd->dw_count = (ar >> 8) & 0xff;
    gd->access_right = ar & 0xff;
    gd->offset_high = (offset >> 16) & 0xffff;
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
