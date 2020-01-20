/******************************************************************************
* @file    setup.h
* @brief   Setting application parameters.
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

#ifndef INC_SETUP_H
#define INC_SETUP_H

#include "stm32f0xx.h"
#include "main.h"
#include "tim.h"
#include "sw_pwm.h"

#define SW_PWM_NUMBER_OF_CHANNELS 18  // number of SW PWM channels
#define SW_PWM_FREQ               300 // frequency of SW PWM channels [Hz]

void setup(void);

#endif // INC_SETUP_H
