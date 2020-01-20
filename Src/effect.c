/******************************************************************************
* @file    effekt.c
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

#include "effect.h"

uint8_t state[SW_PWM_NUMBER_OF_CHANNELS]   = { 0 }; // an array of states for effects
uint8_t compare[SW_PWM_NUMBER_OF_CHANNELS] = { 0 }; // an array of comparative layers for effects
uint32_t time[SW_PWM_NUMBER_OF_CHANNELS]   = { 0 }; // an array of times for effects [ms]
uint32_t delay[SW_PWM_NUMBER_OF_CHANNELS]  = { 0 }; // an array of delays for effects [ms]

/**
 * @brief initialization of effect library
 * @retval void
 */
void effect_init(void)
{
    for (uint8_t i = 0; i < SW_PWM_NUMBER_OF_CHANNELS; i++)
    {
        state[i]   = 0;
        time[i]    = randn();
        compare[i] = randn() + 50;
        delay[i]   = HAL_GetTick();
    }
}

/**
 * @brief effect1 increase and decrease of the duty cycleto pseudo-random values
 * @retval void
 */
void effect1(void)
{
    for (uint8_t i = 0; i < SW_PWM_NUMBER_OF_CHANNELS; i++)
    {
        if (has_delay_elapsed(time[i], &delay[i], true))
        {
            switch (state[i])
            {
                case 0:
                {
                    if (++sw_pwm.channel[i].comp > compare[i])
                    {
                        state[i]   = 1;
                        time[i]    = randn();
                        compare[i] = randn() + 50;
                    }
                    break;
                }
                case 1:
                {
                    state[i] = 2;
                    time[i]  = randn();
                    break;
                }
                case 2:
                {
                    if (--sw_pwm.channel[i].comp < 1)
                    {
                        state[i] = 3;
                        sw_pwm.channel[i].comp = 0;
                        time[i] = randn();
                    }
                    break;
                }
                default:
                {
                    state[i] = 0;
                    time[i]  = randn();
                    break;
                }
            }
        }
    }
} /* effect1 */

/**
 * @brief effect1 increase and duty cycle after pseudo-random steps
 * @retval void
 */
void effect2(void)
{
    for (uint8_t i = 0; i < SW_PWM_NUMBER_OF_CHANNELS; i++)
    {
        if (has_delay_elapsed(time[i], &delay[i], true) && sw_pwm.channel[i].comp != 255)
        {
            ++sw_pwm.channel[i].comp;
            time[i] = randn();
        }
    }
} /* effect2 */

/**
 * @brief effect3 reduction and duty cycle after pseudo-random steps
 * @retval void
 */
void effect3(void)
{
    for (uint8_t i = 0; i < SW_PWM_NUMBER_OF_CHANNELS; i++)
    {
        if (has_delay_elapsed(time[i], &delay[i], true) && sw_pwm.channel[i].comp != 0)
        {
            --sw_pwm.channel[i].comp;
            time[i] = randn();
        }
    }
}/* effect3 */
