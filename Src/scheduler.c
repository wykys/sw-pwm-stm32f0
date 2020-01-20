/******************************************************************************
* @file    scheduler.c
* @brief   Scheduler library based on the system timer.
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

#include "scheduler.h"

/**
 * @brief Checks if the specified time has elapsed since the function was previously run
 * @param delay [ms]
 * @param delay_counter_p pointer to the start time value
 * @param reset after the time has passed, start measuring new time
 * @retval true if time has passed
 */
bool has_delay_elapsed(uint32_t delay, uint32_t *delay_counter_p, bool reset)
{
    uint32_t current_tick_value;
    uint32_t delay_counter;
    uint32_t sys_tick_counter = HAL_GetTick();

    current_tick_value = sys_tick_counter;
    delay_counter      = *delay_counter_p;

    if (current_tick_value >= delay_counter)
    {
        if ((current_tick_value - delay_counter) >= delay)
        {
            if (reset)
                *delay_counter_p = current_tick_value;
            return true;
        }
    }
    else
    {
        if (((0xFFFFFFFF - delay_counter) + current_tick_value) >= delay)
        {
            if (reset)
                *delay_counter_p = current_tick_value;
            return true;
        }
    }

    return false;
}
