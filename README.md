- 在根目录下执行make install_env
```makefile
make install_env
```

- 在根目录新建bochs文件夹
```bash
mkdir bochs
```

- 进入bochs-2.6.8打开终端，输入./configure --prefix=${realpath bochs} --enable-debugger --enable-disasm --enable-iodebug --enable-x86-debugger --with-x --with-x11 LDFLAGS='-pthread'，其中修改${realpath bochs}为你的bochs文件子目录，例如./configure --prefix=/home/XXX/桌面/bochs --enable-debugger --enable-disasm --enable-iodebug --enable-x86-debugger --with-x --with-x11 LDFLAGS='-pthread'
```bash
./configure --prefix=${realpath bochs} --enable-debugger --enable-disasm --enable-iodebug --enable-x86-debugger --with-x --with-x11 LDFLAGS='-pthread'
```

- 继续在bochs-2.6.8文件夹下输入make
```bash
make
```

- 继续在bochs-2.6.8文件夹下输入make install
```bash
make install
```

- 返回根目录并进入bochs文件夹，创建bochsrc.disk
```bash
touch bochsrc.disk
```

- 在bochs.disk中输入，其中${realpath bochs}修改为bochs绝对路径
```yaml
megs : 32

romimage: file=${realpath bochs}/share/bochs/BIOS-bochs-latest
vgaromimage: file=${realpath bochs}/share/bochs/VGABIOS-lgpl-latest

boot: disk

log: bochs.out

mouse:enabled=0
keyboard:keymap=${realpath bochs}/share/bochs/keymaps/x11-pc-us.map

ata0:enabled=1,ioaddr1=0x1f0,ioaddr2=0x3f0,irq=14
ata0-master: type=disk, path="hd60M.img", mode=flat,cylinders=121,heads=16,spt=63   #启动盘配置
ata0-slave: type=disk, path="hd80M.img", mode=flat,cylinders=162,heads=16,spt=63    #从盘配置

#gdbstub:enabled=1,port=1234,text_base=0,data_base=0,bss_base=0
```

- 继续在bochs文件夹下打开终端，输入bin/bximage，创建启动盘
```bash
bin/bximage
```
```bash
1
```
```bash
hd
```
```bash
flat
```
```bash
60
```
```bash
hd60M.img
```

- 继续在bochs文件夹下打开终端，输入bin/bximage，创建从盘
```bash
bin/bximage
```
```bash
1
```
```bash
hd
```
```bash
flat
```
```bash
80
```
```bash
hd80M.img
```

- 打开/etc/apt/sources.list增加
```yaml
deb http://dk.archive.ubuntu.com/ubuntu/ trusty main universe
deb http://dk.archive.ubuntu.com/ubuntu/ trusty-updates main universe
```

- 更新源，有公钥警告就到网上找一下就行
```bash
sudo apt-get update
```

- 安装gcc4.4版本
```bash
sudo apt-get install g++-4.4
```

- 如果有gcc版本冲突，换一下优先级
```bash
gcc -v
```
```bash
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.4 40
```
```bash
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-5 60
```
```bash
update-alternatives --config gcc
```

- 在bochs目录下打开终端，从盘分区
```bash
fdisk ./hd80M.img
```
```bash
m
```
```bash
x
```
```bash
m
```
```bash
c
```
```bash
162
```
```bash
h
```
```bash
16
```
```bash
r
```
```bash
n
```
```bash
p
```
```bash
1
```
```bash
2048
```
```bash
33263
```
```bash
n
```
```bash
e
```
```bash
4
```
```bash
33264
```
```bash
163295
```
```bash
p
```
```bash
n
```
```bash
35312
```
```bash
51407
```
```bash
n
```
```bash
53456
```
```bash
76607
```
```bash
n
```
```bash
78656
```
```bash
91727
```
```bash
n
```
```bash
93776
```
```bash
121967
```
```bash
n
```
```bash
124016
```
```bash
163295
```
```bash
p
```
```bash
t
```
```bash
5
```
```bash
66
```
```bash
t
```
```bash
6
```
```bash
66
```
```bash
t
```
```bash
7
```
```bash
66
```
```bash
t
```
```bash
8
```
```bash
66
```
```bash
t
```
```bash
9
```
```bash
66
```
```bash
p
```
```bash
w
```

- 查看分区
```bash
fdisk -l hd80M.img
```

- 最后终端编译所有文件
```makefile
make all
```

- 运行程序
```makefile
make run
```