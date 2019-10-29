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

hello4.bim : hello4.obj a_nask.obj Makefile
	$(OBJ2BIM) @$(RULEFILE) out:hello4.bim stack:1k map:hello4.map \
		hello4.obj a_nask.obj

hello4.hrb : hello4.bim Makefile
	$(BIM2HRB) hello4.bim hello4.hrb 0

hello5.bim : hello5.obj Makefile
	$(OBJ2BIM) @$(RULEFILE) out:hello5.bim stack:1k map:hello5.map hello5.obj

hello5.hrb : hello5.bim Makefile
	$(BIM2HRB) hello5.bim hello5.hrb 0

winhelo.bim : winhelo.obj a_nask.obj Makefile
	$(OBJ2BIM) @$(RULEFILE) out:winhelo.bim stack:1k map:winhelo.map \
		winhelo.obj a_nask.obj

winhelo.hrb : winhelo.bim Makefile
	$(BIM2HRB) winhelo.bim winhelo.hrb 0

winhelo2.bim : winhelo2.obj a_nask.obj Makefile
	$(OBJ2BIM) @$(RULEFILE) out:winhelo2.bim stack:1k map:winhelo2.map \
		winhelo2.obj a_nask.obj

winhelo2.hrb : winhelo2.bim Makefile
	$(BIM2HRB) winhelo2.bim winhelo2.hrb 0

winhelo3.hrb : winhelo3.bim Makefile
	$(BIM2HRB) winhelo3.bim winhelo3.hrb 0

winhelo3.bim : winhelo3.obj a_nask.obj Makefile
	$(OBJ2BIM) @$(RULEFILE) out:winhelo3.bim stack:1k map:winhelo3.map \
		winhelo3.obj a_nask.obj

stars2.hrb : stars2.bim Makefile
	$(BIM2HRB) stars2.bim stars2.hrb 0

stars2.bim : stars2.obj a_nask.obj Makefile
	$(OBJ2BIM) @$(RULEFILE) out:stars2.bim stack:1k map:stars2.map \
		stars2.obj a_nask.obj

lines.hrb : lines.bim Makefile
	$(BIM2HRB) lines.bim lines.hrb 0

lines.bim : lines.obj a_nask.obj Makefile
	$(OBJ2BIM) @$(RULEFILE) out:lines.bim stack:1k map:lines.map \
		lines.obj a_nask.obj

walk.hrb : walk.bim Makefile
	$(BIM2HRB) walk.bim walk.hrb 0

walk.bim : walk.obj a_nask.obj Makefile
	$(OBJ2BIM) @$(RULEFILE) out:walk.bim stack:1k map:walk.map \
		walk.obj a_nask.obj

noodle.hrb : noodle.bim Makefile
	$(BIM2HRB) noodle.bim noodle.hrb 0

noodle.bim : noodle.obj a_nask.obj Makefile
	$(OBJ2BIM) @$(RULEFILE) out:noodle.bim stack:1k map:noodle.map \
		noodle.obj a_nask.obj

vitality.img : ipl10.bin vitality.sys Makefile \
		hello4.hrb hello5.hrb \
		winhelo.hrb winhelo2.hrb winhelo3.hrb \
		stars2.hrb lines.hrb walk.hrb noodle.hrb
	$(EDIMG) imgin:$(TOOLPATH)fdimg0at.tek \
		wbinimg src:ipl10.bin len:512 from:0 to:0 \
		copy from:vitality.sys to:@: \
		copy from:ipl10.nas to:@: \
		copy from:make.sh to:@: \
		copy from:hello4.hrb to:@: \
		copy from:hello5.hrb to:@: \
		copy from:winhelo.hrb to:@: \
		copy from:winhelo2.hrb to:@: \
		copy from:winhelo3.hrb to:@: \
		copy from:stars2.hrb to:@: \
		copy from:lines.hrb to:@: \
		copy from:walk.hrb to:@: \
		copy from:noodle.hrb to:@: \
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
