/******************************************************************************
* @file    callback_it.h
* @brief   Callback function callable for interrupt handler.
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

#ifndef INC_CALLBACK_IT_H
#define INC_CALLBACK_IT_H

#include "stm32f0xx.h"
#include "main.h"
#include "sw_pwm.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim_p);

#endif // INC_CALLBACK_IT_H
