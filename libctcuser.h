/**
 * @file libctcuser.h
 * @brief CTC linux library.
 * @author Juan David Gonzalez Cobas, BE/CO/HT
 * @date Created on 2011.08.01
 *
 */
/** @mainpage CTC Library Index Page
 *
 * @section Introduction
 *
 *
 * This documentation describes the Linux CTC library API, roughly
 * compatible with the LynxOS library provided by Yury Georgievskiy.
 *
 * The main difference lies in the error reporting: success returns a
 * zero value, and a negative errno value signals some condition,
 * typically -EIO for register access error, and -EINVAL for
 * out-of-range parameters like channel numbers. Otherwise, the
 * prototypes are identical and the semantics is the same, even in the
 * most deviant cases.
 *
 * @b libctcuser relies on @b libencore, which can also be used to
 * access the module
 *
 * @subsection ctcapifunc API functions.
 * @subsection ctcliberr  Library error codes.
 */

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

/**
 * @brief set external start for a channel
 *
 * @param h         - encore handle
 * @param ch        - output channel. [1, 8] range
 * @param ext_start - input channel. [1, 40] range.
 *
 * @return 0                   - on success
 * @return -EINVAL             - on invalid channel
 * @return -EIO	               - on I/O error
 */
int ctc_setInputChan(HANDLE h, int ch, unsigned long ext_start);

/**
 * @brief Returns current clock setting for the first counter.
 *
 * @param h      - encore handle
 * @param ch     - channel, [1, 8] range
 * @param dst    - clock setting [1..6]
 *
 * @return 0                   - on success
 * @return -EINVAL             - on invalid channel
 * @return -EIO	               - on I/O error
 */
int ctc_getClock1(HANDLE h, int ch, unsigned long *dst);

/**
 * @brief Returns current clock setting for the second counter.
 *
 * @param h      - encore handle
 * @param ch     - channel, [1, 8] range
 * @param dst    - clock setting [1..6]
 *
 * @return 0                   - on success
 * @return -CTC_CH_OUT_OF_RANGE - input/output chan out of range
 * @return -CTC_DAL_ERR         - DAL return error
 */
int ctc_getClock2(HANDLE h, int ch, unsigned long *dst);

/**
 * @brief Set external clock for the first counter.
 *
 * @param h         - encore handle
 * @param ch        - channel, [1, 8] range
 * @param ext_clock - value to set [1, 6]
 *
 * @return 0                   - on success
 * @return -EINVAL             - on invalid channel
 * @return -EIO	               - on I/O error
 */
int ctc_setClock1(HANDLE h, int ch, unsigned long ext_clock);

/**
 * @brief Set external clock for the first counter.
 *
 * @param h         - encore handle
 * @param ch        - channel, [1, 8] range
 * @param ext_clock - value to set [1, 6]
 *
 * @return 0                   - on success
 * @return -EINVAL             - on invalid channel
 * @return -EIO	               - on I/O error
 */
int ctc_setClock2(HANDLE h, int ch, unsigned long ext_clock);

/**
 * @brief get delay counter of first clock
 *
 * @param h      - encore handle
 * @param ch     - channel, [1, 8] range
 * @param dst    - clock delay
 *
 * @return 0                   - on success
 * @return -EINVAL             - on invalid channel
 * @return -EIO	               - on I/O error
 */
int ctc_getClock1Tick(HANDLE h, int ch, unsigned long *dst);

/**
 * @brief set delay counter of first clock
 *
 * @param h      - encore handle
 * @param ch     - channel, [1, 8] range
 * @param src    - clock delay
 *
 * @return 0                   - on success
 * @return -EINVAL             - on invalid channel
 * @return -EIO	               - on I/O error
 */
int ctc_setClock1Tick(HANDLE h, int ch, unsigned long src);

/**
 * @brief get delay counter of second clock
 *
 * @param h      - encore handle
 * @param ch     - channel, [1, 8] range
 * @param dst    - clock delay
 *
 * @return 0                   - on success
 * @return -EINVAL             - on invalid channel
 * @return -EIO	               - on I/O error
 */
int ctc_getClock2Tick(HANDLE h, int ch, unsigned long *dst);

/**
 * @brief set delay counter of second clock
 *
 * @param h      - encore handle
 * @param ch     - channel, [1, 8] range
 * @param src    - clock delay
 *
 * @return 0                   - on success
 * @return -EINVAL             - on invalid channel
 * @return -EIO	               - on I/O error
 */
int ctc_setClock2Tick(HANDLE h, int ch, unsigned long src);

/**
 * @brief get value of channel output counter
 *
 * @param h      - encore handle
 * @param ch     - channel, [1, 8] range
 * @param dst    - counter value
 *
 * @return 0                   - on success
 * @return -EINVAL             - on invalid channel
 * @return -EIO	               - on I/O error
 */
int ctc_getOutPutCounter(HANDLE h, int ch, unsigned long *dst);

/**
 * @brief get current value of counter 1
 *
 * @param h      - encore handle
 * @param ch     - channel, [1, 8] range
 * @param dst    - counter value
 *
 * @return 0                   - on success
 * @return -EINVAL             - on invalid channel
 * @return -EIO	               - on I/O error
 */
int ctc_getCntr1CurVal(HANDLE h, int ch, unsigned long *dst);

/**
 * @brief get current value of counter 2
 *
 * @param h      - encore handle
 * @param ch     - channel, [1, 8] range
 * @param dst    - counter value
 *
 * @return 0                   - on success
 * @return -EINVAL             - on invalid channel
 * @return -EIO	               - on I/O error
 */
int ctc_getCntr2CurVal(HANDLE h, int ch, unsigned long *dst);

/**
 * @brief get module status register
 *
 * @param h      - encore handle
 * @param dst    - status (hardware version)
 *
 * @return 0                   - on success
 * @return -EINVAL             - on invalid channel
 * @return -EIO	               - on I/O error
 */
int ctc_getModuleStatus(HANDLE h, unsigned long *dst);

/**
 * @brief reset module
 *
 * @param h      - encore handle
 *
 * @return 0                   - on success
 * @return -EIO	               - on error
 */
int ctc_resetModule(HANDLE h);

/**
 * @brief enable channel and set its external start
 *
 * @param h             - encore handle
 * @param ch            - channel, [1, 8] range
 * @param ext_start     - [1, 40] range
 *
 * @return 0                   - on success
 * @return -EINVAL             - on invalid channel
 * @return -EIO	               - on I/O error
 */
int ctc_enableChannel(HANDLE h, int ch, int ext_start);

/**
 * @brief disable channel
 *
 * @param h      - encore handle
 * @param ch     - channel, [1, 8] range
 *
 * @return 0                   - on success
 * @return -EINVAL             - on invalid channel
 * @return -EIO	               - on I/O error
 */
int ctc_disableChannel(HANDLE h, int ch);

/**
 * @brief get channel configuration
 *
 * @param h       - encore handle
 * @param ch      - channel, [1, 8] range (UNUSED)
 *
 * @return NULL        - on error
 * @return != NULL     - pointer to a static ctc_cfg_reg_t[8] array
 *				containing the configured values of the
 *				eight channels
 */
ctc_cfg_reg_t* ctc_getChanConf(HANDLE h, int ch);

/**
 * @brief get channels enable/disable configuration
 *
 * @param h   - encore handle
 * @param dst - address of int[8], to return the state
 *   of each of the 8 channels: 0 if disabled, e in [1..40]
 *   if enabled with external start e.
 *
 * @return 0                   - on success
 * @return -EINVAL             - on invalid channel
 * @return -EIO	               - on I/O error
 */
int ctc_getChannelStatus(HANDLE h, int dst[8]);

#ifdef __cplusplus
}
#endif
#endif /* _LIBCTCUSER_H */
