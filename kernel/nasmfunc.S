[bits 32]

global io_hlt, io_cli, io_sti, io_stihlt
global io_in8, io_in16, io_in32
global io_out8, io_out16, io_out32
global io_load_eflags, io_store_eflags

section .text
io_hlt:
    hlt
    ret

io_cli:
    cli
    ret

io_sti:
    sti
    ret

io_stihlt:
    sti
    hlt
    ret

io_in8:
    mov edx, [esp + 4]
    mov eax, 0
    in al, dx
    ret

io_in16:
    mov edx, [esp + 4]
    mov eax, 0
    in ax, dx
    ret

io_in32:
    mov edx, [esp + 4]
    in eax, dx
    ret

io_out8:
    mov edx, [esp + 4]
    mov al, [esp + 8]
    out dx, al
    ret

io_out16:
    mov edx, [esp + 4]
    mov eax, [esp + 8]
    out dx, ax
    ret

io_out32:
    mov edx, [esp + 4]
    mov eax, [esp + 8]
    out dx, eax
    ret

io_load_eflags:
    pushfd
    pop eax
    ret

io_store_eflags:
    mov eax, [esp + 4]
    push eax
    popfd
    ret