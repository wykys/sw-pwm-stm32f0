#include "sw_pwm.h"

typedef enum {
    PHASE_CORRECT,
    PHASE_INCORRECT
} sw_pwm_phase_t;

typedef struct {
    TIM_HandleTypeDef *htim_p;
    sw_pwm_phase_t     phase;
    uint8_t            cnt;
} sw_pwm_config_t;

volatile sw_pwm_config_t sw_pwm_config;

volatile sw_pwm_channel_t sw_pwm_channel[SW_PWM_NUMBER_OF_CHANNELS] = {
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
    { PWM15_GPIO_Port, PWM15_Pin }
};


void sw_pwm_tim_start(void)
{
    HAL_TIM_Base_Start_IT(sw_pwm_config.htim_p);
}

/**
 * @brief Initialization software PWM.
 * @param htim_p pointer to HAL timer struct
 * @retval void
 */
void sw_pwm_init(TIM_HandleTypeDef *htim_p)
{
    sw_pwm_config.htim_p = htim_p;
    sw_pwm_config.phase  = PHASE_INCORRECT;
    sw_pwm_config.cnt    = 0;

    for (int i = 0; i < SW_PWM_NUMBER_OF_CHANNELS; i++)
    {
        sw_pwm_channel[i].comp  = 255;
        sw_pwm_channel[i].mask  = i << sw_pwm_channel[i].pin;
        sw_pwm_channel[i].nmask = ~sw_pwm_channel[i].mask;
    }

    sw_pwm_tim_start();
}

static void sw_pwm_callback_phase_incorrect(void)
{
    ++sw_pwm_config.cnt;
    for (int i = 0; i < SW_PWM_NUMBER_OF_CHANNELS; i++)
    {
        if (sw_pwm_config.cnt < sw_pwm_channel[i].comp)
        {
            HAL_GPIO_WritePin(sw_pwm_channel[i].port_p, sw_pwm_channel[i].pin, GPIO_PIN_SET);
        }
        else
        {
            HAL_GPIO_WritePin(sw_pwm_channel[i].port_p, sw_pwm_channel[i].pin, GPIO_PIN_RESET);
        }
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim_p)
{
    if (htim_p == sw_pwm_config.htim_p)
    {
        sw_pwm_callback_phase_incorrect();
    }
}
