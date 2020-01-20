/*******************************************************************************
* @file    sw_pwm.c
* @brief   Library for generating software pulse width modulation.
* @version 1.0
* @author  wykys
* @date    20.1.2020
*******************************************************************************/

/**
 * "THE ROOT BEER LICENSE" (Revision 3) :
 * <vvykys@gmail.com> wrote this file.
 * As long as you retain this notice you
 * can do whatever you want with this stuff.
 * If we meet some day, and you think
 * this stuff is worth it, you can buy me a root beer in return.
 * Also, Jan Vykydal (wykys) is not responsible for anything that
 * might happen through use of this file.
 */

#include "sw_pwm.h"

extern volatile sw_pwm_channel_t sw_pwm_channel[];
volatile sw_pwm_config_t sw_pwm_config;

/**
 * @brief Macro for comparison.
 */
#define sw_pwm_comp()                                                                        \
    do {                                                                                     \
        for (int i = 0; i < sw_pwm_config.number_of_channels; i++)                           \
        {                                                                                    \
            if (sw_pwm_config.cnt <= sw_pwm_channel[i].comp && sw_pwm_channel[i].comp)       \
            {                                                                                \
                sw_pwm_fast_gpio_pin_set(sw_pwm_channel[i].port_p, sw_pwm_channel[i].pin);   \
            }                                                                                \
            else                                                                             \
            {                                                                                \
                sw_pwm_fast_gpio_pin_reset(sw_pwm_channel[i].port_p, sw_pwm_channel[i].pin); \
            }                                                                                \
        }                                                                                    \
    } while (false)

/**
 * @brief Callback for phase-correct PWM.
 * @retval void
 */
static void sw_pwm_callback_phase_correct(void)
{
    if (sw_pwm_config.cnt_mode == SW_PWM_CNT_MODE_UP)
    {
        if (++sw_pwm_config.cnt == SW_PWM_CNT_MAX)
            sw_pwm_config.cnt_mode = SW_PWM_CNT_MODE_DOWN;
    }
    else
    {
        if (!--sw_pwm_config.cnt)
            sw_pwm_config.cnt_mode = SW_PWM_CNT_MODE_UP;
    }
    sw_pwm_comp();
}

/**
 * @brief Callback for phase incorrect(fast) PWM.
 * @retval void
 */
static void sw_pwm_callback_phase_incorrect(void)
{
    ++sw_pwm_config.cnt;
    sw_pwm_comp();
}

/**
 * @brief Resets the counter and starts generating PWM.
 * @retval void
 */
static void sw_pwm_run(void)
{
    sw_pwm_config.cnt = 0;
    sw_pwm_tim_start();
}

/**
 * @brief Stops PWM generation and turns off outputs.
 * @retval void
 */
static void sw_pwm_stop(void)
{
    sw_pwm_tim_stop();
    for (int i = 0; i < sw_pwm_config.number_of_channels; i++)
        sw_pwm_fast_gpio_pin_reset(sw_pwm_channel[i].port_p, sw_pwm_channel[i].pin);
}

/**
 * @brief Sets the PWM frequency.
 * @param freq frequency [Hz] generated PWM signal
 * @param pahse type of PWM phase mode
 * @retval true is OK false is error
 */
static bool sw_pwm_set_freq(uint32_t freq, sw_pwm_phase_t phase)
{
    uint32_t arr;
    uint32_t freq_system = HAL_RCC_GetSysClockFreq();
    bool ret_val         = false;
    if (sw_pwm_config.htim_p != NULL)
    {
        if (phase == SW_PWM_PHASE_CORRECT)
        {
            arr = freq_system / (freq * (SW_PWM_CNT_MAX + 1) * 2) - 1;
        }
        else
        {
            arr = freq_system / (freq * (SW_PWM_CNT_MAX + 1)) - 1;
        }

        if (arr >= (SW_PWM_MINIMUM_OF_TICKS_TO_IT - 1))
        {
            ret_val = true;
        }
        else
        {
            arr = SW_PWM_MINIMUM_OF_TICKS_TO_IT - 1;
        }
        sw_pwm_config.freq = freq_system / ((arr + 1) * (SW_PWM_CNT_MAX + 1) * ((phase == SW_PWM_PHASE_CORRECT) ? 2 : 1));
        sw_pwm_config.htim_p->Instance->ARR = arr;
        sw_pwm_config.phase = phase;
    }
    return ret_val;
} /* sw_pwm_set_freq */

/**
 * @brief Initialization software PWM.
 * @param htim_p pointer to HAL timer structure
 * @param number_of_channels number of PWM channels
 * @param freq frequency [Hz] generated PWM signal
 * @param pahse type of PWM phase mode
 * @param comp comparation value
 * @retval void
 */
void sw_pwm_init(
    TIM_HandleTypeDef *htim_p,
    uint32_t           number_of_channels,
    uint32_t           freq,
    sw_pwm_phase_t     phase,
    sw_pwm_comp_init_t comp
)
{
    sw_pwm_config.htim_p   = htim_p;
    sw_pwm_config.phase    = SW_PWM_PHASE_CORRECT;
    sw_pwm_config.cnt_mode = SW_PWM_CNT_MODE_UP;
    sw_pwm_config.cnt      = 0;
    sw_pwm_config.number_of_channels = number_of_channels;

    sw_pwm_stop();

    if (phase == SW_PWM_PHASE_CORRECT)
    {
        sw_pwm_config.it_callback = sw_pwm_callback_phase_correct;
    }
    else
    {
        sw_pwm_config.it_callback = sw_pwm_callback_phase_incorrect;
    }

    if (comp != SW_PWM_COMP_NOINIT)
    {
        for (int i = 0; i < sw_pwm_config.number_of_channels; i++)
        {
            switch (comp)
            {
                case (SW_PWM_COMP_FULL):
                {
                    sw_pwm_channel[i].comp = SW_PWM_CNT_MAX;
                    break;
                }
                case (SW_PWM_COMP_HALF):
                {
                    sw_pwm_channel[i].comp = SW_PWM_CNT_MAX / 2;
                    break;
                }
                default:
                {
                    sw_pwm_channel[i].comp = 0;
                    break;
                }
            }
        }
    }

    sw_pwm_set_freq(freq, phase);
} /* sw_pwm_init */

/**
 * @brief singleton for SW PWM control
 */
volatile sw_pwm_t sw_pwm = {
    .init     = sw_pwm_init,
    .run      = sw_pwm_run,
    .stop     = sw_pwm_stop,
    .channel  = sw_pwm_channel,
    .config_p = &sw_pwm_config
};
