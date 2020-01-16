#ifndef INC_SW_PWM_H
#define INC_SW_PWM_H

#include "stm32f0xx.h"
#include "main.h"


typedef struct {
    GPIO_TypeDef *port_p;
    volatile uint32_t      pin;
    volatile uint32_t            mask;
    volatile uint32_t            nmask;
    volatile uint8_t             comp;
} sw_pwm_channel_t;

#define SW_PWM_NUMBER_OF_CHANNELS 16
extern volatile sw_pwm_channel_t sw_pwm_channel[SW_PWM_NUMBER_OF_CHANNELS];

void sw_pwm_init(TIM_HandleTypeDef *htim_p);

#endif // INC_SW_PWM_H
