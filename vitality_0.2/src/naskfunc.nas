; naskfunc
; TAB=4

[FORMAT "WCOFF"]
[INSTRSET "i486p"]
[BITS 32]

; 制作目标文件信息

[FILE "naskfunc.nas"]

	GLOBAL _io_hlt,_write_mem8

[SECTION .text] ; 目标文件中写了这些后再写程序

_io_hlt:
	HLT
	RET

_write_mem8:	; void write_mem8(int addr, int data);
	MOV    ECX,[ESP+4]		;向ECX写入addr
	MOV    AL,[ESP+8]		;向AL写入data
	MOV    [ECX],AL
	RET
