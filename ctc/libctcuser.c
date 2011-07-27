#include <errno.h>
#include "libctcuser.h"

#define	BIT(n)	((unsigned)1<<(n))

#define CTC_CHANNELS		8
#define CTC_EXT_STARTS		40
#define CTC_CLOCKS		6

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
	encore_raw_read(h, 1, offset, 1, 32, dst);
	return 0;
}

static int set_channel_register(encore_handle h,
	int ch, enum ctc_regnames regname, unsigned long src)
{
	unsigned offset;

	if (!channel_ok(ch))
		return -EINVAL;
	offset = CTC_CHANNEL0 + (ch-1) * CTC_CHANNEL_SIZE + offsets[regname];
	encore_raw_write(h, 1, offset, 1, 32, &src);
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
	config |= ((ext_start-1) << EXT_START_SHIFT);
	cc = ctc_set_channel_conf(h, ch, config);
	if (cc < 0)
		return -EIO;
	return 0;
}

int ctc_getClock1(HANDLE h, int ch, unsigned long *dst)
{
	unsigned long conf;

	ctc_get_channel_conf(h, ch, &conf);
	*dst = 1 + ((conf & CLOCK1) >> CLOCK1_SHIFT);
	return 0;
}

int ctc_getClock2(HANDLE h, int ch, unsigned long *dst)
{
	unsigned long conf;

	ctc_get_channel_conf(h, ch, &conf);
	*dst = 1 + ((conf & CLOCK2) >> CLOCK2_SHIFT);
	return 0;
}

int ctc_setClock1(HANDLE h, int ch, unsigned long ext_clock)
{
	unsigned long conf;

	if (!ext_clock_ok(ext_clock))
		return -EINVAL;
	ctc_get_channel_conf(h, ch, &conf);
	conf &= ~CLOCK1;
	conf |= ((ext_clock-1) & CLOCK1 << CLOCK1_SHIFT);
	ctc_set_channel_conf(h, ch, conf);

	return 0;
}

int ctc_setClock2(HANDLE h, int ch, unsigned long ext_clock)
{
	unsigned long conf;

	if (!ext_clock_ok(ext_clock))
		return -EINVAL;
	ctc_get_channel_conf(h, ch, &conf);
	conf &= ~CLOCK2;
	conf |= ((ext_clock-1) & CLOCK2 << CLOCK2_SHIFT);
	ctc_set_channel_conf(h, ch, conf);

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
	encore_get_register(h, STATUS, &status);
	*dst = status;
	return 0;
}

int ctc_resetModule(HANDLE h)
{
	int cc;
	int ch;

	cc |= encore_set_register(h, COUNT_ENB, 1);
	cc |= encore_set_register(h, COUNT_ENB, 0);

	for (ch = 1; ch <= CTC_CHANNELS; ch++) {
		cc |= ctc_setInputChan(h, ch, 1);
		cc |= ctc_setClock1Tick(h, ch, 1);
		cc |= ctc_setClock2Tick(h, ch, 1);
	}
	if (cc)
		return cc;
	return 0;
}

static int ctc_enable(HANDLE h, int ch)
{
	unsigned conf;

	encore_get_register(h, COUNT_ENB, &conf);
	conf |= BIT(8-ch+1);
	encore_set_register(h, COUNT_ENB, conf);

	return 0;
}

static int ctc_disable(HANDLE h, int ch)
{
	unsigned conf;

	encore_get_register(h, COUNT_ENB, &conf);
	conf &= ~BIT(8-ch+1);
	encore_set_register(h, COUNT_ENB, conf);

	return 0;
}

int ctc_enableChannel(HANDLE h, int ch, int ext_start)
{
	ctc_setInputChan(h, ch, ext_start);
	ctc_enable(h, ch);

	return 0;
}

int ctc_disableChannel(HANDLE h, int ch)
{
	ctc_setInputChan(h, ch, 1);
	ctc_disable(h, ch);
}

ctc_cfg_reg_t* ctc_getChanConf(HANDLE h, int outChan)
{
	static ctc_cfg_reg_t data[CTC_CHANNELS];
	int ch;

	for (ch = 0; ch < CTC_CHANNELS; ch++) {
		ctc_cfg_reg_t *chconf = &data[ch];
		unsigned long conf;

		ctc_get_channel_conf(h, ch, &conf);
		chconf->cr_ext_start = 1 + ((conf & EXT_START) >> EXT_START_SHIFT);
		chconf->cr_cntr1_clk = 1 + ((conf & CLOCK1) >> CLOCK1_SHIFT);
		chconf->cr_cntr2_clk = 1 + ((conf & CLOCK2) >> CLOCK2_SHIFT);
		chconf->cr_direction = conf & DIRECTION;
		chconf->cr_mode      = conf & MODE;
	}
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
		ctc_get_channel_conf(h, ch, &conf);
		if (cc < 0)
			goto out;
		outChan[ch] = 1 + ((conf & EXT_START) >> EXT_START_SHIFT);
	}
	return 0;
out:
	return cc;
}
