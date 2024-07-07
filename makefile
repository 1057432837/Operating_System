#定义一大堆变量，实质就是将需要多次重复用到的语句定义一个变量方便使用与替换
BUILD_DIR=./build
RUN_DIR = ./bochs
ENTRY_POINT=0xc0001500
HD60M_PATH=bochs/hd60M.img
text="deb http://dk.archive.ubuntu.com/ubuntu/ trusty main universe"
#只需要把hd60m.img路径改成自己环境的路径，整个代码直接make all就完全写入了，能够运行成功
AS=nasm
CC=gcc-4.4
LD=ld
LIB= -I lib/ -I lib/kernel/ -I lib/user/ -I kernel/ -I device/ -I thread/ -I userprog/	-I fs/ -I shell/ -I graph/
ASFLAGS= -f elf -g
CFLAGS= -Wall $(LIB) -c -fno-builtin -W -Wstrict-prototypes -Wmissing-prototypes -m32 -fno-stack-protector -g
#-Wall warning all的意思，产生尽可能多警告信息，-fno-builtin不要采用内部函数，
#-W 会显示警告，但是只显示编译器认为会出现错误的警告
#-Wstrict-prototypes 要求函数声明必须有参数类型，否则发出警告。-Wmissing-prototypes 必须要有函数声明，否则发出警告

LDFLAGS= -Ttext $(ENTRY_POINT) -e main -Map $(BUILD_DIR)/kernel.map -m elf_i386
#-Map,生成map文件，就是通过编译器编译之后，生成的程序、数据及IO空间信息的一种映射文件
#里面包含函数大小，入口地址等一些重要信息

OBJS=$(BUILD_DIR)/main.o $(BUILD_DIR)/init.o \
	$(BUILD_DIR)/interrupt.o $(BUILD_DIR)/timer.o $(BUILD_DIR)/kernel.o \
	$(BUILD_DIR)/print.o $(BUILD_DIR)/debug.o $(BUILD_DIR)/string.o $(BUILD_DIR)/bitmap.o \
	$(BUILD_DIR)/memory.o $(BUILD_DIR)/thread.o	$(BUILD_DIR)/list.o	$(BUILD_DIR)/switch.o \
	$(BUILD_DIR)/sync.o	$(BUILD_DIR)/console.o $(BUILD_DIR)/keyboard.o $(BUILD_DIR)/ioqueue.o \
	$(BUILD_DIR)/tss.o	$(BUILD_DIR)/process.o	$(BUILD_DIR)/syscall.o $(BUILD_DIR)/syscall-init.o \
	$(BUILD_DIR)/stdio.o $(BUILD_DIR)/stdio-kernel.o $(BUILD_DIR)/ide.o $(BUILD_DIR)/fs.o $(BUILD_DIR)/inode.o \
	$(BUILD_DIR)/file.o $(BUILD_DIR)/dir.o $(BUILD_DIR)/fork.o $(BUILD_DIR)/shell.o $(BUILD_DIR)/buildin_cmd.o \
	$(BUILD_DIR)/exec.o $(BUILD_DIR)/assert.o $(BUILD_DIR)/wait_exit.o $(BUILD_DIR)/pipe.o $(BUILD_DIR)/nasmfunc.o \
	$(BUILD_DIR)/palette.o $(BUILD_DIR)/draw.o $(BUILD_DIR)/mouse.o
#顺序最好是调用在前，实现在后

######################编译两个启动文件的代码#####################################
boot:$(BUILD_DIR)/mbr.o $(BUILD_DIR)/loader.o
$(BUILD_DIR)/mbr.o:boot/mbr.S
	$(AS) -I boot/include/ -o build/mbr.o boot/mbr.S
	
$(BUILD_DIR)/loader.o:boot/loader.S
	$(AS) -I boot/include/ -o build/loader.o boot/loader.S
	
######################编译C内核代码###################################################
$(BUILD_DIR)/main.o:kernel/main.c
	$(CC) $(CFLAGS) -o $@ $<	
# $@表示规则中目标文件名的集合这里就是$(BUILD_DIR)/main.o  $<表示规则中依赖文件的第一个，这里就是kernle/main.c 

$(BUILD_DIR)/init.o:kernel/init.c
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR)/interrupt.o:kernel/interrupt.c
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR)/timer.o:device/timer.c
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR)/debug.o:kernel/debug.c
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR)/string.o:lib/string.c
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR)/bitmap.o:lib/kernel/bitmap.c
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR)/memory.o:kernel/memory.c
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR)/thread.o:thread/thread.c
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR)/list.o:lib/kernel/list.c
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR)/sync.o:thread/sync.c
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR)/console.o:device/console.c
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR)/keyboard.o:device/keyboard.c
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR)/ioqueue.o:device/ioqueue.c
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR)/tss.o:userprog/tss.c
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR)/process.o:userprog/process.c
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR)/syscall.o:lib/user/syscall.c
	$(CC) $(CFLAGS) -o $@ $<
$(BUILD_DIR)/syscall-init.o:userprog/syscall-init.c
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR)/stdio.o:lib/stdio.c
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR)/stdio-kernel.o:lib/kernel/stdio-kernel.c
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR)/ide.o:device/ide.c
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR)/fs.o:fs/fs.c
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR)/inode.o:fs/inode.c
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR)/file.o:fs/file.c
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR)/dir.o:fs/dir.c
	$(CC) $(CFLAGS) -o $@ $<
	
$(BUILD_DIR)/fork.o:userprog/fork.c
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR)/shell.o:shell/shell.c
	$(CC) $(CFLAGS) -o $@ $<
	
$(BUILD_DIR)/buildin_cmd.o:shell/buildin_cmd.c
	$(CC) $(CFLAGS) -o $@ $<
	
$(BUILD_DIR)/exec.o:userprog/exec.c
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR)/assert.o:lib/user/assert.c
	$(CC) $(CFLAGS) -o $@ $<
	
$(BUILD_DIR)/pipe.o:shell/pipe.c
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR)/palette.o:graph/palette.c
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR)/draw.o:graph/draw.c
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR)/mouse.o:graph/mouse.c
	$(CC) $(CFLAGS) -o $@ $<
###################编译汇编内核代码#####################################################
$(BUILD_DIR)/kernel.o:kernel/kernel.S 
	$(AS) $(ASFLAGS) -o $@ $<

$(BUILD_DIR)/print.o:lib/kernel/print.S
	$(AS) $(ASFLAGS) -o $@ $<

$(BUILD_DIR)/switch.o:thread/switch.S
	$(AS) $(ASFLAGS) -o $@ $<
	
$(BUILD_DIR)/wait_exit.o:userprog/wait_exit.c
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR)/nasmfunc.o:kernel/nasmfunc.S 
	$(AS) $(ASFLAGS) -o $@ $<
##################链接所有内核目标文件##################################################
$(BUILD_DIR)/kernel.bin:$(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^
# $^表示规则中所有依赖文件的集合，如果有重复，会自动去重

.PHONY:install_env install_bochs update_sources install_compiler mk_disk mk_dir hd clean build all boot gdb_symbol run	#定义了7个伪目标

install_env:
	cd ..; sudo apt install build-essential; sudo apt-get install libghc-x11-dev; sudo apt-get install xorg-dev; sudo apt install nasm

# install_bochs:
# 	tar -zxvf bochs-2.6.8.tar.gz; mkdir bochs; cd bochs-2.6.8; ./configure --prefix=${realpath bochs} --enable-debugger --enable-disasm --enable-iodebug --enable-x86-debugger --with-x --with-x11 LDFLAGS='-pthread'; make; make install

# update_sources:
# 	if [ `grep text /etc/apt/sources.list` -eq '0' ]; then @cd /etc/apt; sudo echo "\n"; sudo echo "deb http://dk.archive.ubuntu.com/ubuntu/ trusty main universe" >> /etc/apt/sources.list; sudo echo "deb http://dk.archive.ubuntu.com/ubuntu/ trusty-updates main universe" >> /etc/apt/sources.list; sudo apt-get update; fi

install_compiler:
	sudo apt-get install g++-4.4; sudo update-alternatives --config gcc

# mk_disk:
# 	cd bochs;
# 	touch bochsrc.disk;
# 	echo "
# 		megs : 32

# 		romimage: file=${realpath bochs}/share/bochs/BIOS-bochs-latest
# 		vgaromimage: file=${realpath bochs}/share/bochs/VGABIOS-lgpl-latest

# 		boot: disk

# 		log: bochs.out

# 		mouse:enabled=0
# 		keyboard:keymap=${realpath bochs}/share/bochs/keymaps/x11-pc-us.map

# 		ata0:enabled=1,ioaddr1=0x1f0,ioaddr2=0x3f0,irq=14
# 		ata0-master: type=disk, path="hd60M.img", mode=flat,cylinders=121,heads=16,spt=63

# 		#gdbstub:enabled=1,port=1234,text_base=0,data_base=0,bss_base=0
# 	" >> bochsrc.disk;
# 	bin/bximage

mk_dir:
	if [ ! -d $(BUILD_DIR) ];then mkdir $(BUILD_DIR);fi 
#判断build文件夹是否存在，如果不存在，则创建

hd:
	dd if=build/mbr.o of=$(HD60M_PATH) count=1 bs=512 conv=notrunc && \
	dd if=build/loader.o of=$(HD60M_PATH) count=4 bs=512 seek=2 conv=notrunc && \
	dd if=$(BUILD_DIR)/kernel.bin of=$(HD60M_PATH) bs=512 count=200 seek=9 conv=notrunc
	
clean:
	@cd $(BUILD_DIR) && rm -f ./* && echo "remove ./build all done"
#-f, --force忽略不存在的文件，从不给出提示，执行make clean就会删除build下所有文件

build:$(BUILD_DIR)/kernel.bin
#执行build需要依赖kernel.bin，但是一开始没有，就会递归执行之前写好的语句编译kernel.bin

#生成可以被GDB理解的符号表，用于GDB调试
gdb_symbol:
	objcopy --only-keep-debug $(BUILD_DIR)/kernel.bin $(BUILD_DIR)/kernel.sym

all:mk_dir boot build hd gdb_symbol
#make all 就是依次执行mk_dir build hd gdb_symbol

run:
	@cd $(RUN_DIR) && bin/bochs -f bochsrc.disk && "program running...	ʕ•ᴥ•ʔ"

