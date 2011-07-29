#ifndef _LIBCTCUSER_H
#define _LIBCTCUSER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <libencore.h>

#define	HANDLE	encore_handle

typedef struct _CTC_config_reg {
  int cr_ext_start;
  int cr_cntr1_clk;
  int cr_cntr2_clk;
  int cr_mode;
  int cr_direction;
} ctc_cfg_reg_t;

	int ctc_setInputChan(HANDLE handle, int chan, unsigned long newVal);

	int ctc_getClock1(HANDLE handle, int chan, unsigned long *res);
	int ctc_setClock1(HANDLE handle, int chan, unsigned long newVal);

	int ctc_getClock2(HANDLE handle, int chan, unsigned long *res);
	int ctc_setClock2(HANDLE handle, int chan, unsigned long newVal);

	int ctc_getClock1Tick(HANDLE handle, int chan, unsigned long *res);
	int ctc_setClock1Tick(HANDLE handle, int chan, unsigned long newVal);

	int ctc_getClock2Tick(HANDLE handle, int chan, unsigned long *res);
	int ctc_setClock2Tick(HANDLE handle, int chan, unsigned long newVal);

	int ctc_getOutPutCounter(HANDLE handle, int chan, unsigned long *res);
	int ctc_getCntr1CurVal(HANDLE handle, int chan, unsigned long *res);
	int ctc_getCntr2CurVal(HANDLE handle, int chan, unsigned long *res);
	int ctc_getModuleStatus(HANDLE handle, unsigned long *res);
	int ctc_resetModule(HANDLE handle);
	int ctc_enableChannel(HANDLE handle, int outChan, int inpChan);
	int ctc_disableChannel(HANDLE handle, int outChan);
	ctc_cfg_reg_t* ctc_getChanConf(HANDLE handle, int outChan);
	int ctc_dbgPrintout(int toggle);
	int ctc_getChannelStatus(HANDLE handle, int outChan[8]);

#ifdef __cplusplus
}
#endif

#endif /* _LIBCTCUSER_H */
