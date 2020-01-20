/******************************************************************************
* @file    scheduler.h
* @brief   Scheduler library based on the system timer.
* @version 1.0
* @author  wykys
* @date    20.1.2020
******************************************************************************/

/**
 * "THE ROOT BEER LICENSE" (Revision 3):
 * <vvykys@gmail.com> wrote this file.
 * As long as you retain this notice you
 * can do whatever you want with this stuff.
 * If we meet some day, and you think
 * this stuff is worth it, you can buy me a root beer in return.
 * Also, Jan Vykydal (wykys) is not responsible for anything that
 * might happen through use of this file.
 */

#ifndef INC_SCHEDULER_H
#define INC_SCHEDULER_H

#include <stdbool.h>
#include "stm32f0xx.h"

bool has_delay_elapsed(uint32_t delay, uint32_t *delay_counter_p, bool reset);

#endif // INC_SCHEDULER_H
