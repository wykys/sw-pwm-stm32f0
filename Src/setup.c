/******************************************************************************
* @file    setup.c
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

#include "setup.h"

/**
 * @brief initialization of SW PWM channel structure
 */
volatile sw_pwm_channel_t sw_pwm_channel[] = {
    { PWM0_GPIO_Port,  PWM0_Pin  },
    { PWM1_GPIO_Port,  PWM1_Pin  },
    { PWM2_GPIO_Port,  PWM2_Pin  },
    { PWM3_GPIO_Port,  PWM3_Pin  },
    { PWM4_GPIO_Port,  PWM4_Pin  },
    { PWM5_GPIO_Port,  PWM5_Pin  },
    { PWM6_GPIO_Port,  PWM6_Pin  },
    { PWM7_GPIO_Port,  PWM7_Pin  },
    { PWM8_GPIO_Port,  PWM8_Pin  },
    { PWM9_GPIO_Port,  PWM9_Pin  },
    { PWM10_GPIO_Port, PWM10_Pin },
    { PWM11_GPIO_Port, PWM11_Pin },
    { PWM12_GPIO_Port, PWM12_Pin },
    { PWM13_GPIO_Port, PWM13_Pin },
    { PWM14_GPIO_Port, PWM14_Pin },
    { PWM15_GPIO_Port, PWM15_Pin },
    { PWM16_GPIO_Port, PWM16_Pin },
    { PWM17_GPIO_Port, PWM17_Pin },
    { PWM18_GPIO_Port, PWM18_Pin },
    { PWM19_GPIO_Port, PWM19_Pin }
};

/**
 * @brief application initialization
 * @retval void
 */
void setup(void)
{
    sw_pwm.init(
        &htim17,
        SW_PWM_NUMBER_OF_CHANNELS,
        SW_PWM_FREQ,
        SW_PWM_PHASE_INCORRECT,
        SW_PWM_COMP_HALF
    );
    sw_pwm.run();
}
