/******************************************************************************
* @file    sw_pwm.h
* @brief   Library for generating software pulse width modulation.
* @version 1.0
* @author  wykys
* @date    20.1.2020
******************************************************************************/

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

#ifndef INC_SW_PWM_H
#define INC_SW_PWM_H

#include <stdbool.h>
#include "stm32f0xx.h"
#include "main.h"

typedef enum {
    SW_PWM_CNT_MODE_UP,  // upward counting direction
    SW_PWM_CNT_MODE_DOWN // Count down direction
} sw_pwm_cnt_mode_t;

typedef enum {
    SW_PWM_PHASE_CORRECT,  // phase corect mode (counting up and down)
    SW_PWM_PHASE_INCORRECT // phase incorrect mode (counting up) (fast)
} sw_pwm_phase_t;

typedef enum {
    SW_PWM_COMP_NOINIT, // do not set the comparison level
    SW_PWM_COMP_ZERO,   // set the comparison level to zero
    SW_PWM_COMP_HALF,   // set the comparison level to half the range
    SW_PWM_COMP_FULL,   // set the comparison level to the top of the counter
} sw_pwm_comp_init_t;

typedef struct {
    TIM_HandleTypeDef *htim_p;             // pointer to HAL timer structure
    uint32_t           number_of_channels; // number of SW PWM channels
    uint32_t           freq;               // frequency [Hz] generated PWM signal
    sw_pwm_phase_t     phase;              // type of PWM phase mode
    sw_pwm_cnt_mode_t  cnt_mode;           // current count direction
    uint8_t            cnt;                // counter
    void (*it_callback)();                 // pointer to interrupt callback
} sw_pwm_config_t;

typedef struct {
    GPIO_TypeDef *port_p; // GPIO pointer
    uint16_t      pin;    // pin
    uint8_t       comp;   // comparation value
} sw_pwm_channel_t;

typedef struct {
    volatile sw_pwm_config_t * config_p;       // pointer to the configuration structure
    volatile sw_pwm_channel_t *channel;        // field of PWM channels
    void (*init)(                              // init function pointer
        TIM_HandleTypeDef *htim_p,             // pointer to HAL timer structure
        uint32_t           number_of_channels, // number of PWM channels
        uint32_t           freq,               // frequency [Hz] generated PWM signal
        sw_pwm_phase_t     phase,              // type of PWM phase mode
        sw_pwm_comp_init_t comp                // comparation value
    );
    void (*run)();  // pointer to the PWM run function
    void (*stop)(); // pointer to the PWM stop function
} sw_pwm_t;

#define SW_PWM_CNT_MAX                255 // top of the counter
#define SW_PWM_MINIMUM_OF_TICKS_TO_IT 555 // minimum number of ticks to IRQ

#define sw_pwm_fast_gpio_pin_set(port_p, pin)   ((port_p)->BSRR = (uint32_t) (pin))
#define sw_pwm_fast_gpio_pin_reset(port_p, pin) ((port_p)->BRR = (uint32_t) (pin))
#define sw_pwm_tim_stop()                       (HAL_TIM_Base_Stop_IT(sw_pwm_config.htim_p))
#define sw_pwm_tim_start()                      (HAL_TIM_Base_Start_IT(sw_pwm_config.htim_p))

extern volatile sw_pwm_t sw_pwm; // singleton for SW PWM control

#endif // INC_SW_PWM_H
