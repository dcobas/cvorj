/* lib_ctc API */
#ifndef _LIBCTC_H
#define _LIBCTC_H

#ifdef __cplusplus
extern "C" {
#endif

/* ctc lib declarations */

int ctc_open(int lun);
int ctc_close(int fd);
int ctc_raw(int fd, int mapping,
	unsigned offset, unsigned items, unsigned data_width,
	void *buffer, int write);
int ctc_wait(int fd);

/* accessor prototypes */
int ctc_get_STATUS(int fd, long *buf);
int ctc_get_CNTR_ENABLE(int fd, long *buf);
int ctc_set_CNTR_ENABLE(int fd, long buf);
int ctc_get_confChan(int fd, long *buf);
int ctc_set_confChan(int fd, long buf);
int ctc_get_clock1Delay(int fd, long *buf);
int ctc_set_clock1Delay(int fd, long buf);
int ctc_get_clock2Delay(int fd, long *buf);
int ctc_set_clock2Delay(int fd, long buf);
int ctc_get_outputCntr(int fd, long *buf);
int ctc_get_cntr1CurVal(int fd, long *buf);
int ctc_get_cntr2CurVal(int fd, long *buf);
int ctc_get_channel_1(int fd, long *buf);
int ctc_get_channel_1_window(int fd, long buf[], int from, int to);
int ctc_set_channel_1(int fd, long buf);
int ctc_set_channel_1_window(int fd, long buf[], int from, int to);
int ctc_get_channel_2(int fd, long *buf);
int ctc_get_channel_2_window(int fd, long buf[], int from, int to);
int ctc_set_channel_2(int fd, long buf);
int ctc_set_channel_2_window(int fd, long buf[], int from, int to);
int ctc_get_channel_3(int fd, long *buf);
int ctc_get_channel_3_window(int fd, long buf[], int from, int to);
int ctc_set_channel_3(int fd, long buf);
int ctc_set_channel_3_window(int fd, long buf[], int from, int to);
int ctc_get_channel_4(int fd, long *buf);
int ctc_get_channel_4_window(int fd, long buf[], int from, int to);
int ctc_set_channel_4(int fd, long buf);
int ctc_set_channel_4_window(int fd, long buf[], int from, int to);
int ctc_get_channel_5(int fd, long *buf);
int ctc_get_channel_5_window(int fd, long buf[], int from, int to);
int ctc_set_channel_5(int fd, long buf);
int ctc_set_channel_5_window(int fd, long buf[], int from, int to);
int ctc_get_channel_6(int fd, long *buf);
int ctc_get_channel_6_window(int fd, long buf[], int from, int to);
int ctc_set_channel_6(int fd, long buf);
int ctc_set_channel_6_window(int fd, long buf[], int from, int to);
int ctc_get_channel_7(int fd, long *buf);
int ctc_get_channel_7_window(int fd, long buf[], int from, int to);
int ctc_set_channel_7(int fd, long buf);
int ctc_set_channel_7_window(int fd, long buf[], int from, int to);
int ctc_get_channel_8(int fd, long *buf);
int ctc_get_channel_8_window(int fd, long buf[], int from, int to);
int ctc_set_channel_8(int fd, long buf);
int ctc_set_channel_8_window(int fd, long buf[], int from, int to);
int ctc_get_ALL_CHANNELS(int fd, long *buf);
int ctc_get_ALL_CHANNELS_window(int fd, long buf[], int from, int to);
int ctc_set_ALL_CHANNELS(int fd, long buf);
int ctc_set_ALL_CHANNELS_window(int fd, long buf[], int from, int to);


#ifdef __cplusplus
}
#endif
#endif /* _LIBCTC_H */
