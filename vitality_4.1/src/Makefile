TOOLPATH = /Users/natsunoyoru/Desktop/30days_OS/tolset/z_tools/
INCPATH  = /Users/natsunoyoru/Desktop/30days_OS/tolset/z_tools/vitality/

MAKE     = $(TOOLPATH)make.exe  -r
EDIMG    = $(TOOLPATH)edimg.exe
COPY     = copy
DEL      = del

default :
	wine $(MAKE) img

########
vitality.img : vitality/ipl20.bin vitality/vitality.sys Makefile \
		winhelo/winhelo.hrb winhelo2/winhelo2.hrb winhelo3/winhelo3.hrb \
		stars2/stars2.hrb lines/lines.hrb walk/walk.hrb noodle/noodle.hrb \
		color/color.hrb color2/color2.hrb typeipl/typeipl.hrb type/type.hrb \
		iroha/iroha.hrb chklang/chklang.hrb
	$(EDIMG) imgin:$(TOOLPATH)fdimg0at.tek \
		wbinimg src:vitality/ipl20.bin len:512 from:0 to:0 \
		copy from:vitality/vitality.sys to:@: \
		copy from:vitality/ipl20.nas to:@: \
		copy from:make.sh to:@: \
		copy from:winhelo/winhelo.hrb to:@: \
		copy from:winhelo2/winhelo2.hrb to:@: \
		copy from:winhelo3/winhelo3.hrb to:@: \
		copy from:stars2/stars2.hrb to:@: \
		copy from:lines/lines.hrb to:@: \
		copy from:walk/walk.hrb to:@: \
		copy from:noodle/noodle.hrb to:@: \
		copy from:color/color.hrb to:@: \
		copy from:color2/color2.hrb to:@: \
		copy from:typeipl/typeipl.hrb to:@: \
		copy from:type/type.hrb to:@: \
		copy from:chklang/chklang.hrb to:@: \
		copy from:euc.txt to:@: \
		copy from:gb.txt to:@: \
		copy from:iroha/iroha.hrb to:@: \
		copy from:nihongo/nihongo.fnt to:@: \
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

full :
	$(MAKE) -C vitality
	$(MAKE) -C apilib
	$(MAKE) -C a
	$(MAKE) -C hello3
	$(MAKE) -C hello4
	$(MAKE) -C hello5
	$(MAKE) -C winhelo
	$(MAKE) -C winhelo2
	$(MAKE) -C winhelo3
	$(MAKE) -C stars2
	$(MAKE) -C lines
	$(MAKE) -C walk
	$(MAKE) -C noodle
	$(MAKE) -C color
	$(MAKE) -C color2
	$(MAKE) -C typeipl
	$(MAKE) -C type
	$(MAKE) -C iroha
	$(MAKE) -C chklang
	$(MAKE) vitality.img

run_full :
	wine $(MAKE) full
	qemu-system-i386 -fda vitality.img -m 64M

run_os :
	wine $(MAKE) -C vitality
	$(MAKE) run

clean :
# 何もしない

src_only :
	$(MAKE) clean
	-$(DEL) vitality.img

clean_full :
	$(MAKE) -C vitality		clean
	$(MAKE) -C apilib		clean
	$(MAKE) -C a			clean
	$(MAKE) -C hello3		clean
	$(MAKE) -C hello4		clean
	$(MAKE) -C hello5		clean
	$(MAKE) -C winhelo		clean
	$(MAKE) -C winhelo2		clean
	$(MAKE) -C winhelo3		clean
	$(MAKE) -C stars2		clean
	$(MAKE) -C lines		clean
	$(MAKE) -C walk			clean
	$(MAKE) -C noodle		clean
	$(MAKE) -C color		clean
	$(MAKE) -C color2		clean
	$(MAKE) -C typeipl		clean
	$(MAKE) -C type  		clean
	$(MAKE) -C iroha  		clean
	$(MAKE) -C chklang		clean

src_only_full :
	$(MAKE) -C vitality		src_only
	$(MAKE) -C apilib		src_only
	$(MAKE) -C a			src_only
	$(MAKE) -C hello3		src_only
	$(MAKE) -C hello4		src_only
	$(MAKE) -C hello5		src_only
	$(MAKE) -C winhelo		src_only
	$(MAKE) -C winhelo2		src_only
	$(MAKE) -C winhelo3		src_only
	$(MAKE) -C stars2		src_only
	$(MAKE) -C lines		src_only
	$(MAKE) -C walk			src_only
	$(MAKE) -C noodle		src_only
	$(MAKE) -C color		src_only
	$(MAKE) -C color2		src_only
	$(MAKE) -C typeipl		src_only
	$(MAKE) -C type 		src_only
	$(MAKE) -C iroha 		src_only
	$(MAKE) -C chklang		src_only
	-$(DEL) vitality.img

refresh :
	wine $(MAKE) full
	wine $(MAKE) clean_full
	rm vitality.img