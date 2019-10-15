default :
	wine /Users/natsunoyoru/Desktop/30days_OS/tolset/z_tools/make.exe img

########

#BUG: 运行make.exe只需要包一层wine，但调用过程中不可避免需要使用不同arg的情况，如何处理冲突？

ipl.bin : ipl.nas Makefile
	/Users/natsunoyoru/Desktop/30days_OS/tolset/z_tools/nask.exe ipl.nas ipl.bin ipl.lst

vitality.img : ipl.bin Makefile
	/Users/natsunoyoru/Desktop/30days_OS/tolset/z_tools/edimg.exe imgin:/Users/natsunoyoru/Desktop/30days_OS/tolset/z_tools/fdimg0at.tek   wbinimg src:ipl.bin len:512 from:0 to:0   imgout:vitality.img

########

asm :
	wine /Users/natsunoyoru/Desktop/30days_OS/tolset/z_tools/make.exe -r ipl.bin

img :
	/Users/natsunoyoru/Desktop/30days_OS/tolset/z_tools/make.exe -r vitality.img

run :
	wine /Users/natsunoyoru/Desktop/30days_OS/tolset/z_tools/make.exe img
	qemu-system-i386 -drive format=raw,file=vitality.img
	#cp vitality.img /Users/natsunoyoru/Desktop/30days_OS/tolset/z_tools/macOS_start/

#install : 未发现用处，先注释掉，如需恢复则也需更改make.sh

#BUG: 当ipl.bin不存在无法删除已有的ipl.lst

clean :
	rm ipl.bin
	rm ipl.lst

src_only :
	wine /Users/natsunoyoru/Desktop/30days_OS/tolset/z_tools/make.exe clean
	rm vitality.img
