/******************************************************************************
* @file    effekt.h
* @brief   Effects library for testing PWM software.
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

#ifndef INC_EFFECT_H
#define INC_EFFECT_H

#include "stm32f0xx.h"
#include "setup.h"
#include "sw_pwm.h"
#include "randn.h"
#include "scheduler.h"

void effect_init(void);
void effect1(void);
void effect2(void);
void effect3(void);

#endif // INC_EFFECT_H
