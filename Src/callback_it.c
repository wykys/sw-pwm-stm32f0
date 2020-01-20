/******************************************************************************
* @file    callback_it.c
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

#include "callback_it.h"

/**
 * @brief operation of interrupting timer loading into the top
 * @retval void
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim_p)
{
    if (htim_p == sw_pwm.config_p->htim_p)
    {
        sw_pwm_fast_gpio_pin_set(MEASUREMENT_GPIO_Port, MEASUREMENT_Pin);
        sw_pwm.config_p->it_callback();
        sw_pwm_fast_gpio_pin_reset(MEASUREMENT_GPIO_Port, MEASUREMENT_Pin);
    }
}
