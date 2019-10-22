OBJS_BOOTPACK = bootpack.obj naskfunc.obj hankaku.obj graphic.obj dsctbl.obj int.obj fifo.obj keyboard.obj mouse.obj memory.obj sheet.obj timer.obj

TOOLPATH = /Users/natsunoyoru/Desktop/30days_OS/tolset/z_tools/
INCPATH  = /Users/natsunoyoru/Desktop/30days_OS/tolset/z_tools/vitality/

MAKE     = $(TOOLPATH)make.exe  -r
NASK     = $(TOOLPATH)nask.exe
CC1      = $(TOOLPATH)cc1.exe -I$(INCPATH) -Os -Wall -quiet
GAS2NASK = $(TOOLPATH)gas2nask.exe -a
OBJ2BIM  = $(TOOLPATH)obj2bim.exe
MAKEFONT = $(TOOLPATH)makefont.exe
BIN2OBJ  = $(TOOLPATH)bin2obj.exe
BIM2HRB  = $(TOOLPATH)bim2hrb.exe
RULEFILE = $(TOOLPATH)vitality/vitality.rul
EDIMG    = $(TOOLPATH)edimg.exe
COPY     = cp
DEL      = del

default :
	$(MAKE) img

########

#BUG: 运行make.exe只需要包一层wine，但调用过程中不可避免需要使用不同arg的情况，如何处理冲突？

ipl10.bin : ipl10.nas Makefile
	$(NASK) ipl10.nas ipl10.bin ipl10.lst

asmhead.bin : asmhead.nas Makefile
	$(NASK) asmhead.nas asmhead.bin asmhead.lst

hankaku.bin : hankaku.txt Makefile
	$(MAKEFONT) hankaku.txt hankaku.bin

hankaku.obj : hankaku.bin Makefile
	$(BIN2OBJ) hankaku.bin hankaku.obj _hankaku

bootpack.bim : $(OBJS_BOOTPACK) Makefile
	$(OBJ2BIM) @$(RULEFILE) out:bootpack.bim stack:3136k map:bootpack.map $(OBJS_BOOTPACK)

bootpack.hrb : bootpack.bim Makefile
	$(BIM2HRB) bootpack.bim bootpack.hrb 0

vitality.sys : asmhead.bin bootpack.hrb Makefile
	copy /B asmhead.bin+bootpack.hrb vitality.sys

vitality.img : ipl10.bin vitality.sys Makefile
	$(EDIMG) imgin:$(TOOLPATH)fdimg0at.tek wbinimg src:ipl10.bin len:512 from:0 to:0 copy from:vitality.sys to:@: imgout:vitality.img

#一般规则

%.gas : %.c Makefile
	$(CC1) -o $*.gas $*.c

%.nas : %.gas Makefile
	$(GAS2NASK) $*.gas $*.nas

%.obj : %.nas Makefile
	$(NASK) $*.nas $*.obj $*.lst

########

img :
	$(MAKE) vitality.img

run :
	wine $(MAKE) img
	qemu-system-i386 -fda vitality.img -m 32M #不设定分配内存则默认为128M（可能因机型而异）
	#cp vitality.img /Users/natsunoyoru/Desktop/30days_OS/tolset/z_tools/macOS_start/

#install : 不涉及写入磁盘的过程所以不使用，如需恢复则也需更改make.sh

#BUG: 当ipl.bin不存在无法删除已有的ipl.lst
clean :
	-$(DEL) *.bin
	-$(DEL) *.lst
	-$(DEL) *.gas
	-$(DEL) *.obj
	-$(DEL) bootpack.map
	-$(DEL) bootpack.bim
	-$(DEL) bootpack.hrb
	-$(DEL) vitality.sys

src_only :
	$(MAKE) clean
	-$(DEL) vitality.img
