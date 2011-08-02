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

int ctc_setInputChan(HANDLE h, int ch, unsigned long ext_start);
int ctc_getClock1(HANDLE h, int ch, unsigned long *dst);
int ctc_getClock2(HANDLE h, int ch, unsigned long *dst);
int ctc_setClock1(HANDLE h, int ch, unsigned long ext_clock);
int ctc_setClock2(HANDLE h, int ch, unsigned long ext_clock);
int ctc_getClock1Tick(HANDLE h, int ch, unsigned long *dst);
int ctc_setClock1Tick(HANDLE h, int ch, unsigned long src);
int ctc_getClock2Tick(HANDLE h, int ch, unsigned long *dst);
int ctc_setClock2Tick(HANDLE h, int ch, unsigned long src);
int ctc_getOutPutCounter(HANDLE h, int ch, unsigned long *dst);
int ctc_getCntr1CurVal(HANDLE h, int ch, unsigned long *dst);
int ctc_getCntr2CurVal(HANDLE h, int ch, unsigned long *dst);
int ctc_getModuleStatus(HANDLE h, unsigned long *dst);
int ctc_resetModule(HANDLE h);
int ctc_enableChannel(HANDLE h, int ch, int ext_start);
int ctc_disableChannel(HANDLE h, int ch);
ctc_cfg_reg_t* ctc_getChanConf(HANDLE h, int outChan);
int ctc_getChannelStatus(HANDLE h, int outChan[8]);

#ifdef __cplusplus
}
#endif

#endif /* _LIBCTCUSER_H */
