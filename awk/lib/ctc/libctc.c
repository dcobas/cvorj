#include <vmeio_support.h>


/**
 * Library for CTC module 
 * Generated automatically by genlib.c.awk at:2011 Tue March- 1 16:44:43
 */

#include <libctc.h>


int GET_STATUS(void *handle, int *status) {
   int offset = 0;
   struct vmeio_riob_s riob;
   riob.winum  =1;
   riob.offset =0x00000000 + (offset * 4);
   riob.bsize  =4;
   riob.buffer =status;
   return RAW(handle,&riob,0);
}


int SET_CNTR_ENABLE(void *handle, int *cntr_enable) {
   int offset = 0;
   struct vmeio_riob_s riob;
   riob.winum  =1;
   riob.offset =0x00000004 + (offset * 4);
   riob.bsize  =4;
   riob.buffer =cntr_enable;
   return RAW(handle,&riob,1);
}

int GET_CNTR_ENABLE(void *handle, int *cntr_enable) {
   int offset = 0;
   struct vmeio_riob_s riob;
   riob.winum  =1;
   riob.offset =0x00000004 + (offset * 4);
   riob.bsize  =4;
   riob.buffer =cntr_enable;
   return RAW(handle,&riob,0);
}


int SET_clock2Delay(void *handle, int *clock2delay) {
   int offset = 0;
   struct vmeio_riob_s riob;
   riob.winum  =1;
   riob.offset =0x00000010 + (offset * 4);
   riob.bsize  =4;
   riob.buffer =clock2delay;
   return RAW(handle,&riob,1);
}

int GET_clock2Delay(void *handle, int *clock2delay) {
   int offset = 0;
   struct vmeio_riob_s riob;
   riob.winum  =1;
   riob.offset =0x00000010 + (offset * 4);
   riob.bsize  =4;
   riob.buffer =clock2delay;
   return RAW(handle,&riob,0);
}


int GET_cntr2CurVal(void *handle, int *cntr2curval) {
   int offset = 0;
   struct vmeio_riob_s riob;
   riob.winum  =1;
   riob.offset =0x0000001C + (offset * 4);
   riob.bsize  =4;
   riob.buffer =cntr2curval;
   return RAW(handle,&riob,0);
}


int SET_confChan(void *handle, int *confchan) {
   int offset = 0;
   struct vmeio_riob_s riob;
   riob.winum  =1;
   riob.offset =0x00000008 + (offset * 4);
   riob.bsize  =4;
   riob.buffer =confchan;
   return RAW(handle,&riob,1);
}

int GET_confChan(void *handle, int *confchan) {
   int offset = 0;
   struct vmeio_riob_s riob;
   riob.winum  =1;
   riob.offset =0x00000008 + (offset * 4);
   riob.bsize  =4;
   riob.buffer =confchan;
   return RAW(handle,&riob,0);
}


int GET_cntr1CurVal(void *handle, int *cntr1curval) {
   int offset = 0;
   struct vmeio_riob_s riob;
   riob.winum  =1;
   riob.offset =0x00000018 + (offset * 4);
   riob.bsize  =4;
   riob.buffer =cntr1curval;
   return RAW(handle,&riob,0);
}


int GET_outputCntr(void *handle, int *outputcntr) {
   int offset = 0;
   struct vmeio_riob_s riob;
   riob.winum  =1;
   riob.offset =0x00000014 + (offset * 4);
   riob.bsize  =4;
   riob.buffer =outputcntr;
   return RAW(handle,&riob,0);
}


int SET_clock1Delay(void *handle, int *clock1delay) {
   int offset = 0;
   struct vmeio_riob_s riob;
   riob.winum  =1;
   riob.offset =0x0000000C + (offset * 4);
   riob.bsize  =4;
   riob.buffer =clock1delay;
   return RAW(handle,&riob,1);
}

int GET_clock1Delay(void *handle, int *clock1delay) {
   int offset = 0;
   struct vmeio_riob_s riob;
   riob.winum  =1;
   riob.offset =0x0000000C + (offset * 4);
   riob.bsize  =4;
   riob.buffer =clock1delay;
   return RAW(handle,&riob,0);
}


int SET_channel_1(void *handle, int offset, int *channel_1) {
   struct vmeio_riob_s riob;
   riob.winum  =1;
   riob.offset =0x00000008 + (offset * 4);
   riob.bsize  =4;
   riob.buffer =channel_1;
   return RAW(handle,&riob,1);
}

int GET_channel_1(void *handle, int offset, int *channel_1) {
   struct vmeio_riob_s riob;
   riob.winum  =1;
   riob.offset =0x00000008 + (offset * 4);
   riob.bsize  =4;
   riob.buffer =channel_1;
   return RAW(handle,&riob,0);
}


int SET_channel_2(void *handle, int offset, int *channel_2) {
   struct vmeio_riob_s riob;
   riob.winum  =1;
   riob.offset =0x00000020 + (offset * 4);
   riob.bsize  =4;
   riob.buffer =channel_2;
   return RAW(handle,&riob,1);
}

int GET_channel_2(void *handle, int offset, int *channel_2) {
   struct vmeio_riob_s riob;
   riob.winum  =1;
   riob.offset =0x00000020 + (offset * 4);
   riob.bsize  =4;
   riob.buffer =channel_2;
   return RAW(handle,&riob,0);
}


int SET_channel_3(void *handle, int offset, int *channel_3) {
   struct vmeio_riob_s riob;
   riob.winum  =1;
   riob.offset =0x00000038 + (offset * 4);
   riob.bsize  =4;
   riob.buffer =channel_3;
   return RAW(handle,&riob,1);
}

int GET_channel_3(void *handle, int offset, int *channel_3) {
   struct vmeio_riob_s riob;
   riob.winum  =1;
   riob.offset =0x00000038 + (offset * 4);
   riob.bsize  =4;
   riob.buffer =channel_3;
   return RAW(handle,&riob,0);
}


int SET_channel_4(void *handle, int offset, int *channel_4) {
   struct vmeio_riob_s riob;
   riob.winum  =1;
   riob.offset =0x00000050 + (offset * 4);
   riob.bsize  =4;
   riob.buffer =channel_4;
   return RAW(handle,&riob,1);
}

int GET_channel_4(void *handle, int offset, int *channel_4) {
   struct vmeio_riob_s riob;
   riob.winum  =1;
   riob.offset =0x00000050 + (offset * 4);
   riob.bsize  =4;
   riob.buffer =channel_4;
   return RAW(handle,&riob,0);
}


int SET_channel_5(void *handle, int offset, int *channel_5) {
   struct vmeio_riob_s riob;
   riob.winum  =1;
   riob.offset =0x00000068 + (offset * 4);
   riob.bsize  =4;
   riob.buffer =channel_5;
   return RAW(handle,&riob,1);
}

int GET_channel_5(void *handle, int offset, int *channel_5) {
   struct vmeio_riob_s riob;
   riob.winum  =1;
   riob.offset =0x00000068 + (offset * 4);
   riob.bsize  =4;
   riob.buffer =channel_5;
   return RAW(handle,&riob,0);
}


int SET_channel_6(void *handle, int offset, int *channel_6) {
   struct vmeio_riob_s riob;
   riob.winum  =1;
   riob.offset =0x00000080 + (offset * 4);
   riob.bsize  =4;
   riob.buffer =channel_6;
   return RAW(handle,&riob,1);
}

int GET_channel_6(void *handle, int offset, int *channel_6) {
   struct vmeio_riob_s riob;
   riob.winum  =1;
   riob.offset =0x00000080 + (offset * 4);
   riob.bsize  =4;
   riob.buffer =channel_6;
   return RAW(handle,&riob,0);
}


int SET_channel_7(void *handle, int offset, int *channel_7) {
   struct vmeio_riob_s riob;
   riob.winum  =1;
   riob.offset =0x00000098 + (offset * 4);
   riob.bsize  =4;
   riob.buffer =channel_7;
   return RAW(handle,&riob,1);
}

int GET_channel_7(void *handle, int offset, int *channel_7) {
   struct vmeio_riob_s riob;
   riob.winum  =1;
   riob.offset =0x00000098 + (offset * 4);
   riob.bsize  =4;
   riob.buffer =channel_7;
   return RAW(handle,&riob,0);
}


int SET_channel_8(void *handle, int offset, int *channel_8) {
   struct vmeio_riob_s riob;
   riob.winum  =1;
   riob.offset =0x000000B0 + (offset * 4);
   riob.bsize  =4;
   riob.buffer =channel_8;
   return RAW(handle,&riob,1);
}

int GET_channel_8(void *handle, int offset, int *channel_8) {
   struct vmeio_riob_s riob;
   riob.winum  =1;
   riob.offset =0x000000B0 + (offset * 4);
   riob.bsize  =4;
   riob.buffer =channel_8;
   return RAW(handle,&riob,0);
}


int SET_ALL_CHANNELS(void *handle, int offset, int *all_channels) {
   struct vmeio_riob_s riob;
   riob.winum  =1;
   riob.offset =0x00000008 + (offset * 4);
   riob.bsize  =4;
   riob.buffer =all_channels;
   return RAW(handle,&riob,1);
}

int GET_ALL_CHANNELS(void *handle, int offset, int *all_channels) {
   struct vmeio_riob_s riob;
   riob.winum  =1;
   riob.offset =0x00000008 + (offset * 4);
   riob.bsize  =4;
   riob.buffer =all_channels;
   return RAW(handle,&riob,0);
}


