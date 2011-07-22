#include <sys/ioctl.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "vmeio.h"
#include "ctc_regs.h"

#define MAX_DEVNAME	256

int ctc_open(int lun)
{
	char devname[MAX_DEVNAME];
	static char devnamefmt[] = "/dev/ctc.%d";
	int cc;

	cc = snprintf(devname, MAX_DEVNAME, devnamefmt, lun);
	if (cc < 0 || cc >= MAX_DEVNAME)
		return -EINVAL;
	return open(devname, O_RDWR);
}

int ctc_close(int fd)
{
	return close(fd);
}

int ctc_wait(int fd)
{
	struct vmeio_read_buf_s rb;

	return read(fd, &rb, sizeof(rb));
}

enum encore_direction {
	ENCORE_READ = 0,
	ENCORE_WRITE = 1,
};

int ctc_raw(int fd, int mapping,
	unsigned offset, unsigned items, unsigned data_width,
	void *buffer, enum encore_direction write)
{
	struct vmeio_riob riob, *riobp = &riob;

	riobp->mapnum = mapping;
	riobp->offset = offset;
	riobp->wsize  = items;
	riobp->buffer = buffer;
	riobp->data_width = data_width;

	if (write)
		return ioctl(fd, VMEIO_RAW_WRITE, riobp);
	else
		return ioctl(fd, VMEIO_RAW_READ, riobp);
}

static int reg_wnum(struct encore_reginfo *reg)
{
	char sz = reg->wordsize[0];

	switch (sz) {
	case 'c':
		return 8;
	case 's':
		return 16;
	case 'l':
		return 32;
	default:
		return 0;
	}
}

static int get_set_register(int fd,
	struct encore_reginfo *reg, void *buffer,
	enum encore_direction direction)
{
	int data_width = reg_wnum(reg);

	return ctc_raw(fd,
		reg->block_address_space,
		reg->offset, reg->depth,
		data_width, buffer, direction);
}

static int get_set_window(int fd,
	struct encore_reginfo *reg,
	void *buffer, int from, int to,
	enum encore_direction direction)
{
	int data_width = reg_wnum(reg);
	int bytesize = data_width/8;

	return ctc_raw(fd,
		reg->block_address_space,
		reg->offset + from*bytesize,
		to - from,
		data_width, buffer, direction);
}


int ctc_get_STATUS(int fd, long *buf)
{
	struct encore_reginfo *reg = &ctc_registers[STATUS];
	return get_set_register(fd, reg, buf, ENCORE_READ);
}

int ctc_get_CNTR_ENABLE(int fd, long *buf)
{
	struct encore_reginfo *reg = &ctc_registers[CNTR_ENABLE];
	return get_set_register(fd, reg, buf, ENCORE_READ);
}

int ctc_set_CNTR_ENABLE(int fd, long buf)
{
	struct encore_reginfo *reg = &ctc_registers[CNTR_ENABLE];
	return get_set_register(fd, reg, &buf, ENCORE_WRITE);
}

int ctc_get_confChan(int fd, long *buf)
{
	struct encore_reginfo *reg = &ctc_registers[confChan];
	return get_set_register(fd, reg, buf, ENCORE_READ);
}

int ctc_set_confChan(int fd, long buf)
{
	struct encore_reginfo *reg = &ctc_registers[confChan];
	return get_set_register(fd, reg, &buf, ENCORE_WRITE);
}

int ctc_get_clock1Delay(int fd, long *buf)
{
	struct encore_reginfo *reg = &ctc_registers[clock1Delay];
	return get_set_register(fd, reg, buf, ENCORE_READ);
}

int ctc_set_clock1Delay(int fd, long buf)
{
	struct encore_reginfo *reg = &ctc_registers[clock1Delay];
	return get_set_register(fd, reg, &buf, ENCORE_WRITE);
}

int ctc_get_clock2Delay(int fd, long *buf)
{
	struct encore_reginfo *reg = &ctc_registers[clock2Delay];
	return get_set_register(fd, reg, buf, ENCORE_READ);
}

int ctc_set_clock2Delay(int fd, long buf)
{
	struct encore_reginfo *reg = &ctc_registers[clock2Delay];
	return get_set_register(fd, reg, &buf, ENCORE_WRITE);
}

int ctc_get_outputCntr(int fd, long *buf)
{
	struct encore_reginfo *reg = &ctc_registers[outputCntr];
	return get_set_register(fd, reg, buf, ENCORE_READ);
}

int ctc_get_cntr1CurVal(int fd, long *buf)
{
	struct encore_reginfo *reg = &ctc_registers[cntr1CurVal];
	return get_set_register(fd, reg, buf, ENCORE_READ);
}

int ctc_get_cntr2CurVal(int fd, long *buf)
{
	struct encore_reginfo *reg = &ctc_registers[cntr2CurVal];
	return get_set_register(fd, reg, buf, ENCORE_READ);
}

int ctc_get_channel_1(int fd, long *buf)
{
	struct encore_reginfo *reg = &ctc_registers[channel_1];
	return get_set_register(fd, reg, buf, ENCORE_READ);
}

int ctc_get_channel_1_window(int fd, long buf[], int from, int to)
{
	struct encore_reginfo *reg = &ctc_registers[channel_1];
	return get_set_window(fd, reg, buf, from, to, ENCORE_READ);
}

int ctc_set_channel_1(int fd, long buf)
{
	struct encore_reginfo *reg = &ctc_registers[channel_1];
	return get_set_register(fd, reg, &buf, ENCORE_WRITE);
}

int ctc_set_channel_1_window(int fd, long buf[], int from, int to)
{
	struct encore_reginfo *reg = &ctc_registers[channel_1];
	return get_set_window(fd, reg, buf, from, to, ENCORE_WRITE);
}

int ctc_get_channel_2(int fd, long *buf)
{
	struct encore_reginfo *reg = &ctc_registers[channel_2];
	return get_set_register(fd, reg, buf, ENCORE_READ);
}

int ctc_get_channel_2_window(int fd, long buf[], int from, int to)
{
	struct encore_reginfo *reg = &ctc_registers[channel_2];
	return get_set_window(fd, reg, buf, from, to, ENCORE_READ);
}

int ctc_set_channel_2(int fd, long buf)
{
	struct encore_reginfo *reg = &ctc_registers[channel_2];
	return get_set_register(fd, reg, &buf, ENCORE_WRITE);
}

int ctc_set_channel_2_window(int fd, long buf[], int from, int to)
{
	struct encore_reginfo *reg = &ctc_registers[channel_2];
	return get_set_window(fd, reg, buf, from, to, ENCORE_WRITE);
}

int ctc_get_channel_3(int fd, long *buf)
{
	struct encore_reginfo *reg = &ctc_registers[channel_3];
	return get_set_register(fd, reg, buf, ENCORE_READ);
}

int ctc_get_channel_3_window(int fd, long buf[], int from, int to)
{
	struct encore_reginfo *reg = &ctc_registers[channel_3];
	return get_set_window(fd, reg, buf, from, to, ENCORE_READ);
}

int ctc_set_channel_3(int fd, long buf)
{
	struct encore_reginfo *reg = &ctc_registers[channel_3];
	return get_set_register(fd, reg, &buf, ENCORE_WRITE);
}

int ctc_set_channel_3_window(int fd, long buf[], int from, int to)
{
	struct encore_reginfo *reg = &ctc_registers[channel_3];
	return get_set_window(fd, reg, buf, from, to, ENCORE_WRITE);
}

int ctc_get_channel_4(int fd, long *buf)
{
	struct encore_reginfo *reg = &ctc_registers[channel_4];
	return get_set_register(fd, reg, buf, ENCORE_READ);
}

int ctc_get_channel_4_window(int fd, long buf[], int from, int to)
{
	struct encore_reginfo *reg = &ctc_registers[channel_4];
	return get_set_window(fd, reg, buf, from, to, ENCORE_READ);
}

int ctc_set_channel_4(int fd, long buf)
{
	struct encore_reginfo *reg = &ctc_registers[channel_4];
	return get_set_register(fd, reg, &buf, ENCORE_WRITE);
}

int ctc_set_channel_4_window(int fd, long buf[], int from, int to)
{
	struct encore_reginfo *reg = &ctc_registers[channel_4];
	return get_set_window(fd, reg, buf, from, to, ENCORE_WRITE);
}

int ctc_get_channel_5(int fd, long *buf)
{
	struct encore_reginfo *reg = &ctc_registers[channel_5];
	return get_set_register(fd, reg, buf, ENCORE_READ);
}

int ctc_get_channel_5_window(int fd, long buf[], int from, int to)
{
	struct encore_reginfo *reg = &ctc_registers[channel_5];
	return get_set_window(fd, reg, buf, from, to, ENCORE_READ);
}

int ctc_set_channel_5(int fd, long buf)
{
	struct encore_reginfo *reg = &ctc_registers[channel_5];
	return get_set_register(fd, reg, &buf, ENCORE_WRITE);
}

int ctc_set_channel_5_window(int fd, long buf[], int from, int to)
{
	struct encore_reginfo *reg = &ctc_registers[channel_5];
	return get_set_window(fd, reg, buf, from, to, ENCORE_WRITE);
}

int ctc_get_channel_6(int fd, long *buf)
{
	struct encore_reginfo *reg = &ctc_registers[channel_6];
	return get_set_register(fd, reg, buf, ENCORE_READ);
}

int ctc_get_channel_6_window(int fd, long buf[], int from, int to)
{
	struct encore_reginfo *reg = &ctc_registers[channel_6];
	return get_set_window(fd, reg, buf, from, to, ENCORE_READ);
}

int ctc_set_channel_6(int fd, long buf)
{
	struct encore_reginfo *reg = &ctc_registers[channel_6];
	return get_set_register(fd, reg, &buf, ENCORE_WRITE);
}

int ctc_set_channel_6_window(int fd, long buf[], int from, int to)
{
	struct encore_reginfo *reg = &ctc_registers[channel_6];
	return get_set_window(fd, reg, buf, from, to, ENCORE_WRITE);
}

int ctc_get_channel_7(int fd, long *buf)
{
	struct encore_reginfo *reg = &ctc_registers[channel_7];
	return get_set_register(fd, reg, buf, ENCORE_READ);
}

int ctc_get_channel_7_window(int fd, long buf[], int from, int to)
{
	struct encore_reginfo *reg = &ctc_registers[channel_7];
	return get_set_window(fd, reg, buf, from, to, ENCORE_READ);
}

int ctc_set_channel_7(int fd, long buf)
{
	struct encore_reginfo *reg = &ctc_registers[channel_7];
	return get_set_register(fd, reg, &buf, ENCORE_WRITE);
}

int ctc_set_channel_7_window(int fd, long buf[], int from, int to)
{
	struct encore_reginfo *reg = &ctc_registers[channel_7];
	return get_set_window(fd, reg, buf, from, to, ENCORE_WRITE);
}

int ctc_get_channel_8(int fd, long *buf)
{
	struct encore_reginfo *reg = &ctc_registers[channel_8];
	return get_set_register(fd, reg, buf, ENCORE_READ);
}

int ctc_get_channel_8_window(int fd, long buf[], int from, int to)
{
	struct encore_reginfo *reg = &ctc_registers[channel_8];
	return get_set_window(fd, reg, buf, from, to, ENCORE_READ);
}

int ctc_set_channel_8(int fd, long buf)
{
	struct encore_reginfo *reg = &ctc_registers[channel_8];
	return get_set_register(fd, reg, &buf, ENCORE_WRITE);
}

int ctc_set_channel_8_window(int fd, long buf[], int from, int to)
{
	struct encore_reginfo *reg = &ctc_registers[channel_8];
	return get_set_window(fd, reg, buf, from, to, ENCORE_WRITE);
}

int ctc_get_ALL_CHANNELS(int fd, long *buf)
{
	struct encore_reginfo *reg = &ctc_registers[ALL_CHANNELS];
	return get_set_register(fd, reg, buf, ENCORE_READ);
}

int ctc_get_ALL_CHANNELS_window(int fd, long buf[], int from, int to)
{
	struct encore_reginfo *reg = &ctc_registers[ALL_CHANNELS];
	return get_set_window(fd, reg, buf, from, to, ENCORE_READ);
}

int ctc_set_ALL_CHANNELS(int fd, long buf)
{
	struct encore_reginfo *reg = &ctc_registers[ALL_CHANNELS];
	return get_set_register(fd, reg, &buf, ENCORE_WRITE);
}

int ctc_set_ALL_CHANNELS_window(int fd, long buf[], int from, int to)
{
	struct encore_reginfo *reg = &ctc_registers[ALL_CHANNELS];
	return get_set_window(fd, reg, buf, from, to, ENCORE_WRITE);
}


