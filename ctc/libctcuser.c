#include <errno.h>
#include "libctcuser.h"

#define	BIT(n)	((unsigned)1<<(n))

#define CTC_CHANNELS		8
#define CTC_EXT_STARTS		40
#define CTC_CLOCKS			6

#define CTC_CHANNEL0		0x08
#define	CTC_CHANNEL_SIZE	0x18

/* channel conf register */
#define	MODE		0x1
#define	DIRECTION	0x2
#define	CLOCK1		(0x7<<CLOCK1_SHIFT)
#define	CLOCK1_SHIFT	19
#define	CLOCK2		(0x7<<CLOCK2_SHIFT)
#define	CLOCK2_SHIFT	16
#define	EXT_START_SHIFT	24
#define	EXT_START	(0x3f << EXT_START_SHIFT)

#define	STATUS		0
#define	COUNT_ENB	1

enum ctc_regnames {
	conf = 0,
	delay1,
	delay2,
	out_count,
	value1,
	value2,
};

static unsigned offsets[] = {
	[conf]		= 0x00,
	[delay1]	= 0x04,
	[delay2]	= 0x08,
	[out_count]	= 0x0c,
	[value1]	= 0x10,
	[value2]	= 0x14,
};

static int channel_ok(int ch)
{
	return (ch >= 1) && (ch <= CTC_CHANNELS);
}

static int ext_start_ok(int ext)
{
	return (ext >= 1) && (ext <= CTC_EXT_STARTS);
}

static int ext_clock_ok(int clock)
{
	return (clock >= 1) && (clock <= CTC_CLOCKS);
}

static int get_channel_register(encore_handle h,
	int ch, enum ctc_regnames regname, unsigned long *dst)
{
	unsigned offset;

	if (!channel_ok(ch))
		return -EINVAL;
	offset = CTC_CHANNEL0 + (ch-1) * CTC_CHANNEL_SIZE + offsets[regname];
	if (!encore_raw_read(h, 1, offset, 1, 32, dst))
		return -EIO;
	return 0;
}

static int set_channel_register(encore_handle h,
	int ch, enum ctc_regnames regname, unsigned long src)
{
	unsigned offset;

	if (!channel_ok(ch))
		return -EINVAL;
	offset = CTC_CHANNEL0 + (ch-1) * CTC_CHANNEL_SIZE + offsets[regname];
	if (!encore_raw_write(h, 1, offset, 1, 32, &src))
		return -EIO;
	return 0;
}

static int ctc_get_channel_conf(HANDLE h, int ch, unsigned long *dst)
{
	return get_channel_register(h, ch, conf, dst);
}

static int ctc_set_channel_conf(HANDLE h, int ch, unsigned long src)
{
	return set_channel_register(h, ch, conf, src);
}

int ctc_setInputChan(HANDLE h, int ch, unsigned long ext_start)
{
	unsigned long config;
	int cc;

	if (!ext_start_ok(ext_start))
		return -EINVAL;
	cc = ctc_get_channel_conf(h, ch, &config);
	if (cc < 0)
		return -EIO;
	config &= ~EXT_START;
	config |= ((ext_start-1) << EXT_START_SHIFT) & EXT_START;
	cc = ctc_set_channel_conf(h, ch, config);
	if (cc < 0)
		return -EIO;
	return 0;
}

int ctc_getClock1(HANDLE h, int ch, unsigned long *dst)
{
	unsigned long conf;
	int err;

	err = ctc_get_channel_conf(h, ch, &conf);
	if (err)
		return err;
	*dst = 1 + ((conf & CLOCK1) >> CLOCK1_SHIFT);
	return 0;
}

int ctc_getClock2(HANDLE h, int ch, unsigned long *dst)
{
	unsigned long conf;
	int err;

	err = ctc_get_channel_conf(h, ch, &conf);
	if (err)
		return err;
	*dst = 1 + ((conf & CLOCK2) >> CLOCK2_SHIFT);
	return 0;
}

int ctc_setClock1(HANDLE h, int ch, unsigned long ext_clock)
{
	unsigned long conf;
	int err;

	if (!ext_clock_ok(ext_clock))
		return -EINVAL;
	err = ctc_get_channel_conf(h, ch, &conf);
	if (err)
		return err;
	conf &= ~CLOCK1;
	conf |= ((ext_clock-1) << CLOCK1_SHIFT) & CLOCK1;
	err = ctc_set_channel_conf(h, ch, conf);
	if (err)
		return err;
	return 0;
}

int ctc_setClock2(HANDLE h, int ch, unsigned long ext_clock)
{
	unsigned long conf;
	int err;

	if (!ext_clock_ok(ext_clock))
		return -EINVAL;
	err = ctc_get_channel_conf(h, ch, &conf);
	if (err)
		return err;
	conf &= ~CLOCK2;
	conf |= ((ext_clock-1) << CLOCK2_SHIFT) & CLOCK2;
	err = ctc_set_channel_conf(h, ch, conf);
	if (err)
		return err;
	return 0;
}

int ctc_getClock1Tick(HANDLE h, int ch, unsigned long *dst)
{
	return get_channel_register(h, ch, delay1, dst);
}

int ctc_setClock1Tick(HANDLE h, int ch, unsigned long src)
{
	return set_channel_register(h, ch, delay1, src);
}

int ctc_getClock2Tick(HANDLE h, int ch, unsigned long *dst)
{
	return get_channel_register(h, ch, delay2, dst);
}

int ctc_setClock2Tick(HANDLE h, int ch, unsigned long src)
{
	return set_channel_register(h, ch, delay2, src);
}

int ctc_getOutPutCounter(HANDLE h, int ch, unsigned long *dst)
{
	return get_channel_register(h, ch, out_count, dst);
}

int ctc_getCntr1CurVal(HANDLE h, int ch, unsigned long *dst)
{
	return get_channel_register(h, ch, value1, dst);
}

int ctc_getCntr2CurVal(HANDLE h, int ch, unsigned long *dst)
{
	return get_channel_register(h, ch, value2, dst);
}

int ctc_getModuleStatus(HANDLE h, unsigned long *dst)
{
	unsigned status;
	int err;

	err = encore_get_register(h, STATUS, &status);
	if (err)
		return err;
	*dst = status;
	return 0;
}

int ctc_resetModule(HANDLE h)
{
	int err;
	int ch;

	err |= encore_set_register(h, COUNT_ENB, 1);
	err |= encore_set_register(h, COUNT_ENB, 0);

	for (ch = 1; ch <= CTC_CHANNELS; ch++) {
		err |= ctc_setInputChan(h, ch, 1);
		err |= ctc_setClock1Tick(h, ch, 1);
		err |= ctc_setClock2Tick(h, ch, 1);
	}
	if (err)
		return -EIO;
	return 0;
}

static int ctc_enable(HANDLE h, int ch)
{
	unsigned conf;
	int err;

	err = encore_get_register(h, COUNT_ENB, &conf);
	if (err)
		return err;
	conf |= BIT(8-ch+1);
	return encore_set_register(h, COUNT_ENB, conf);
}

static int ctc_disable(HANDLE h, int ch)
{
	unsigned conf;
	int err;

	err = encore_get_register(h, COUNT_ENB, &conf);
	if (err)
		return err;
	conf &= ~BIT(8-ch+1);
	return encore_set_register(h, COUNT_ENB, conf);
}

int ctc_enableChannel(HANDLE h, int ch, int ext_start)
{
	int err;

	err = ctc_setInputChan(h, ch, ext_start);
	if (err)
		return err;
	return ctc_enable(h, ch);
}

int ctc_disableChannel(HANDLE h, int ch)
{
	int err;

	err = ctc_setInputChan(h, ch, 1);
	if (err)
		return err;
	return ctc_disable(h, ch);
}

ctc_cfg_reg_t* ctc_getChanConf(HANDLE h, int outChan)
{
	static ctc_cfg_reg_t data[CTC_CHANNELS];
	int ch;
	int err = 0;

	for (ch = 0; ch < CTC_CHANNELS; ch++) {
		ctc_cfg_reg_t *chconf = &data[ch];
		unsigned long conf;

		err |= ctc_get_channel_conf(h, ch, &conf);
		chconf->cr_ext_start = 1 + ((conf & EXT_START) >> EXT_START_SHIFT);
		chconf->cr_cntr1_clk = 1 + ((conf & CLOCK1) >> CLOCK1_SHIFT);
		chconf->cr_cntr2_clk = 1 + ((conf & CLOCK2) >> CLOCK2_SHIFT);
		chconf->cr_direction = conf & DIRECTION;
		chconf->cr_mode      = conf & MODE;
	}
	if (err)
		return NULL;
	return data;
}

int ctc_getChannelStatus(HANDLE h, int outChan[8])
{
	int ch;
	unsigned count_enb;
	unsigned long conf;
	int cc;

	cc = encore_get_register(h, COUNT_ENB, &count_enb);
	if (cc < 0)
		goto out;
	for (ch = 0; ch < CTC_CHANNELS; ch++) {
		if ((count_enb & BIT(8-ch)) == 0) {
			outChan[ch] = 0;
			continue;
		}
		cc = ctc_get_channel_conf(h, ch, &conf);
		if (cc < 0)
			goto out;
		outChan[ch] = 1 + ((conf & EXT_START) >> EXT_START_SHIFT);
	}
	return 0;
out:
	return cc;
}
