#include "bootpack.h"

struct FIFO32 *mousefifo;
int mousedata0;

void inthandler2c(int *esp)
{
	int data;
	io_out8(PIC1_OCW2, 0x64);
	io_out8(PIC0_OCW2, 0x62);
	data = io_in8(PORT_KEYDAT);
	fifo32_put(mousefifo, data + mousedata0);
	return;
}

#define KEYCMD_SENDTO_MOUSE    0xd4
#define MOUSECMD_ENABLE        0xf4

void enable_mouse(struct FIFO32 *fifo, int data0, struct MOUSE_DEC *mdec)
{
	//将FIFO缓冲区的内容保存到全局变量
	mousefifo = fifo;
	mousedata0 = data0;

	wait_KBC_sendready();
	io_out8(PORT_KEYCMD, KEYCMD_SENDTO_MOUSE);
	wait_KBC_sendready();
	io_out8(PORT_KEYDAT, MOUSECMD_ENABLE);

	mdec->phase = 0; //等待鼠标的0xfa字节
	return;
}

int mouse_decode(struct MOUSE_DEC *mdec, unsigned char dat)
{
	if (mdec->phase == 0) {
		if (dat == 0xfa) {
			mdec->phase = 1;
		}
		return 0;
	}
	if (mdec->phase == 1) {
		//等待鼠标数据buf[0]
		mdec->buf[0] = dat;
		mdec->phase = 2;
		return 0;
	}
	if (mdec->phase == 2) {
		//等待鼠标数据buf[1]
		mdec->buf[1] = dat;
		mdec->phase = 3;
		return 0;
	}
	if (mdec->phase == 3) {
		//等待鼠标数据buf[2]
		mdec->buf[2] = dat;
		mdec->phase = 1;
		mdec->btn = mdec->buf[0] & 0x07; //取后三个字节
		mdec->x = mdec->buf[1];
		mdec->y = mdec->buf[2];
		if ((mdec->buf[0] & 0x10) != 0) {
			mdec->x |= 0xffffff00;
		}
		if ((mdec->buf[0] & 0x20) != 0) {
			mdec->y |= 0xffffff00;
		}
		mdec->y = - mdec->y;
		return 1;
	}
	return -1;
}