OBJS_BOOTPACK = bootpack.obj naskfunc.obj hankaku.obj graphic.obj dsctbl.obj \
		int.obj fifo.obj keyboard.obj mouse.obj memory.obj sheet.obj timer.obj \
		mtask.obj window.obj console.obj file.obj

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
DEL      = rm

default :
	wine $(MAKE) img

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

hello.hrb : hello.nas Makefile
	$(NASK) hello.nas hello.hrb hello.lst

hello2.hrb : hello2.nas Makefile
	$(NASK) hello2.nas hello2.hrb hello2.lst

a.bim : a.obj a_nask.obj Makefile
	$(OBJ2BIM) @$(RULEFILE) out:a.bim map:a.map a.obj a_nask.obj

a.hrb : a.bim Makefile
	$(BIM2HRB) a.bim a.hrb 0

hello3.bim : hello3.obj a_nask.obj Makefile
	$(OBJ2BIM) @$(RULEFILE) out:hello3.bim map:hello3.map hello3.obj a_nask.obj

hello3.hrb : hello3.bim Makefile
	$(BIM2HRB) hello3.bim hello3.hrb 0

crack1.bim : crack1.obj Makefile
	$(OBJ2BIM) @$(RULEFILE) out:crack1.bim map:crack1.map crack1.obj a_nask.obj

crack1.hrb : crack1.bim Makefile
	$(BIM2HRB) crack1.bim crack1.hrb 0

crack2.hrb : crack2.nas Makefile
	$(NASK) crack2.nas crack2.hrb crack2.lst

vitality.img : ipl10.bin vitality.sys Makefile \
		hello.hrb hello2.hrb a.hrb hello3.hrb crack1.hrb crack2.hrb
	$(EDIMG) imgin:$(TOOLPATH)fdimg0at.tek \
		wbinimg src:ipl10.bin len:512 from:0 to:0 \
		copy from:vitality.sys to:@: \
		copy from:ipl10.nas to:@: \
		copy from:make.sh to:@: \
		copy from:hello.hrb to:@: \
		copy from:hello2.hrb to:@: \
		copy from:a.hrb to:@: \
		copy from:hello3.hrb to:@: \
		copy from:crack1.hrb to:@: \
		copy from:crack2.hrb to:@: \
		imgout:vitality.img

#一般规则

%.gas : %.c bootpack.h Makefile
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
	qemu-system-i386 -fda vitality.img -m 64M #不设定分配内存则默认为128M（可能因机型而异）
	#cp vitality.img /Users/natsunoyoru/Desktop/30days_OS/tolset/z_tools/macOS_start/

#install : 不涉及写入磁盘的过程所以不使用，如需恢复则也需更改make.sh

#BUG: 当ipl.bin不存在无法删除已有的ipl.lst
clean :
	$(DEL) *.bin
	$(DEL) *.lst
	$(DEL) *.obj
	#$(DEL) bootpack.map
	$(DEL) bootpack.bim
	$(DEL) bootpack.hrb
	$(DEL) vitality.sys

src_only :
	$(MAKE) clean
	$(DEL) vitality.img
	$(DEL) *.hrb
