#include <vmeio_support.h>

#ifndef GEN_LIB_API
#define GEN_LIB_API

/**
 * API for CTC module 
 * Generated automatically by genlib.h.awk at:2011 Tue March- 1 16:44:43
 */

#define OFFSET_STATUS (0x00000000)
#define GET_STATUS DRV_SYMB(_get_status)
int GET_STATUS(void *handle, int *status);

#define OFFSET_CNTR_ENABLE (0x00000004)
#define SET_CNTR_ENABLE DRV_SYMB(_set_cntr_enable)
int SET_CNTR_ENABLE(void *handle, int *cntr_enable);
#define GET_CNTR_ENABLE DRV_SYMB(_get_cntr_enable)
int GET_CNTR_ENABLE(void *handle, int *cntr_enable);

#define OFFSET_clock2Delay (0x00000010)
#define SET_clock2Delay DRV_SYMB(_set_clock2delay)
int SET_clock2Delay(void *handle, int *clock2delay);
#define GET_clock2Delay DRV_SYMB(_get_clock2delay)
int GET_clock2Delay(void *handle, int *clock2delay);

#define OFFSET_cntr2CurVal (0x0000001C)
#define GET_cntr2CurVal DRV_SYMB(_get_cntr2curval)
int GET_cntr2CurVal(void *handle, int *cntr2curval);

#define OFFSET_confChan (0x00000008)
#define SET_confChan DRV_SYMB(_set_confchan)
int SET_confChan(void *handle, int *confchan);
#define GET_confChan DRV_SYMB(_get_confchan)
int GET_confChan(void *handle, int *confchan);

#define OFFSET_cntr1CurVal (0x00000018)
#define GET_cntr1CurVal DRV_SYMB(_get_cntr1curval)
int GET_cntr1CurVal(void *handle, int *cntr1curval);

#define OFFSET_outputCntr (0x00000014)
#define GET_outputCntr DRV_SYMB(_get_outputcntr)
int GET_outputCntr(void *handle, int *outputcntr);

#define OFFSET_clock1Delay (0x0000000C)
#define SET_clock1Delay DRV_SYMB(_set_clock1delay)
int SET_clock1Delay(void *handle, int *clock1delay);
#define GET_clock1Delay DRV_SYMB(_get_clock1delay)
int GET_clock1Delay(void *handle, int *clock1delay);

#define OFFSET_channel_1 (0x00000008)
#define SET_channel_1 DRV_SYMB(_set_channel_1)
int SET_channel_1(void *handle, int offset, int *channel_1);
#define GET_channel_1 DRV_SYMB(_get_channel_1)
int GET_channel_1(void *handle, int offset, int *channel_1);

#define OFFSET_channel_2 (0x00000020)
#define SET_channel_2 DRV_SYMB(_set_channel_2)
int SET_channel_2(void *handle, int offset, int *channel_2);
#define GET_channel_2 DRV_SYMB(_get_channel_2)
int GET_channel_2(void *handle, int offset, int *channel_2);

#define OFFSET_channel_3 (0x00000038)
#define SET_channel_3 DRV_SYMB(_set_channel_3)
int SET_channel_3(void *handle, int offset, int *channel_3);
#define GET_channel_3 DRV_SYMB(_get_channel_3)
int GET_channel_3(void *handle, int offset, int *channel_3);

#define OFFSET_channel_4 (0x00000050)
#define SET_channel_4 DRV_SYMB(_set_channel_4)
int SET_channel_4(void *handle, int offset, int *channel_4);
#define GET_channel_4 DRV_SYMB(_get_channel_4)
int GET_channel_4(void *handle, int offset, int *channel_4);

#define OFFSET_channel_5 (0x00000068)
#define SET_channel_5 DRV_SYMB(_set_channel_5)
int SET_channel_5(void *handle, int offset, int *channel_5);
#define GET_channel_5 DRV_SYMB(_get_channel_5)
int GET_channel_5(void *handle, int offset, int *channel_5);

#define OFFSET_channel_6 (0x00000080)
#define SET_channel_6 DRV_SYMB(_set_channel_6)
int SET_channel_6(void *handle, int offset, int *channel_6);
#define GET_channel_6 DRV_SYMB(_get_channel_6)
int GET_channel_6(void *handle, int offset, int *channel_6);

#define OFFSET_channel_7 (0x00000098)
#define SET_channel_7 DRV_SYMB(_set_channel_7)
int SET_channel_7(void *handle, int offset, int *channel_7);
#define GET_channel_7 DRV_SYMB(_get_channel_7)
int GET_channel_7(void *handle, int offset, int *channel_7);

#define OFFSET_channel_8 (0x000000B0)
#define SET_channel_8 DRV_SYMB(_set_channel_8)
int SET_channel_8(void *handle, int offset, int *channel_8);
#define GET_channel_8 DRV_SYMB(_get_channel_8)
int GET_channel_8(void *handle, int offset, int *channel_8);

#define OFFSET_ALL_CHANNELS (0x00000008)
#define SET_ALL_CHANNELS DRV_SYMB(_set_all_channels)
int SET_ALL_CHANNELS(void *handle, int offset, int *all_channels);
#define GET_ALL_CHANNELS DRV_SYMB(_get_all_channels)
int GET_ALL_CHANNELS(void *handle, int offset, int *all_channels);

#endif
