/******************************************************************************
* @file    super-loop.c
* @brief   Super loop application.
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

#include "super-loop.h"

/**
 * @brief super loop application
 * @retval void
 */
void super_loop(void)
{
    uint32_t delay = 0;
    uint32_t state = 0;

    while (true)
    {
        switch (state)
        {
            case 0:
            {
                effect1();
                if (has_delay_elapsed(20000, &delay, true))
                {
                    state = 1;
                    effect_init();
                }
                break;
            }
            case 1:
            {
                effect2();
                if (has_delay_elapsed(7000, &delay, true))
                {
                    state = 2;
                    effect_init();
                }
                break;
            }
            default:
            {
                effect3();
                if (has_delay_elapsed(10000, &delay, true))
                {
                    state = 0;
                    effect_init();
                }
                break;
            }
        }
    }
} /* super_loop */
