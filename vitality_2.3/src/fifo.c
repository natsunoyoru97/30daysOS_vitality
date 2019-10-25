//the FIFO Library
#include "bootpack.h"

#define FLAGS_OVERRUN    0x0001

void fifo32_init(struct FIFO32 *fifo, int size, int *buf, struct TASK *task)
//初始化FIFO
{
	fifo->size = size;
	fifo->buf = buf;
	fifo->free = size; //缓冲区大小
	fifo->flags = 0;
	fifo->p = 0; //写入位置
	fifo->q = 0; //读取位置
	fifo->task = task;
	return;
}

int fifo32_put(struct FIFO32 *fifo, int data)
//向FIFO传递数据
{
	if (fifo->free == 0) {
		//没有闲置空间
		fifo->flags |= FLAGS_OVERRUN;
		return -1;
	}
	fifo->buf[fifo->p] = data;
	fifo->p++;
	if (fifo->p == fifo->size) {
		fifo->p = 0;
	}
	fifo->free--;

	if (fifo->task != 0) {
		if (fifo->task->flags != 2) { //任务处于休眠状态
			task_run(fifo->task, -1, 0); //唤醒任务
		}
	}
	return 0;
}

int fifo32_get(struct FIFO32 *fifo)
//从FIFO取出数据
{
	int data;
	if (fifo->free == fifo->size) {
		//缓冲区为空
		return -1;
	}
	data = fifo->buf[fifo->q];
	fifo->q++;
	if (fifo->q == fifo->size) {
		fifo->q = 0;
	}
	fifo->free++;
	return data;
}

int fifo32_status(struct FIFO32 *fifo)
//查看缓冲区状态
{
	return fifo->size - fifo->free;
}
