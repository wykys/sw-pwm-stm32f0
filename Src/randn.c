/******************************************************************************
* @file    super-randn.c
* @brief   A library for generating pseudo - random numbers.
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

#include "randn.h"

/**
 * @brief table for generating pseudo - random numbers
 */
const uint8_t random[256] = {
    45, 34, 55, 29, 22, 61, 47, 62, 25, 25, 42, 28, 31, 34, 41, 63, 57,
    32, 29, 59, 37, 24, 27, 62, 28, 57, 41, 47, 57, 29, 25, 60, 43, 42,
    47, 51, 50, 41, 23, 41, 61, 52, 58, 27, 28, 27, 45, 60, 22, 29, 51,
    25, 61, 39, 24, 56, 24, 25, 39, 49, 39, 27, 40, 32, 23, 63, 53, 29,
    34, 25, 49, 34, 53, 33, 27, 43, 38, 35, 32, 40, 31, 33, 59, 62, 52,
    28, 23, 44, 38, 54, 60, 33, 49, 24, 35, 35, 22, 28, 51, 26, 63, 31,
    30, 63, 46, 49, 24, 58, 27, 29, 33, 58, 51, 42, 33, 62, 38, 56, 57,
    47, 32, 56, 50, 46, 30, 28, 55, 38, 45, 62, 58, 29, 22, 37, 22, 61,
    43, 61, 54, 27, 45, 34, 26, 26, 41, 22, 58, 34, 49, 54, 48, 56, 45,
    43, 45, 58, 22, 32, 24, 36, 43, 37, 25, 30, 56, 22, 46, 26, 27, 42,
    46, 28, 54, 44, 48, 36, 36, 35, 35, 35, 57, 25, 60, 52, 35, 44, 59,
    36, 40, 34, 35, 29, 54, 63, 54, 38, 28, 26, 30, 25, 56, 46, 49, 27,
    51, 57, 48, 44, 26, 48, 33, 58, 23, 27, 29, 37, 26, 60, 43, 24, 29,
    42, 35, 41, 52, 26, 45, 30, 23, 61, 22, 35, 23, 58, 29, 36, 49, 36,
    34, 55, 34, 50, 30, 62, 35, 42, 40, 49, 36, 32, 62, 34, 25, 39, 41,
    58
};

/**
 * @brief generating a pseudo - random 8b number
 * @retval pseudo - random number
 */
uint8_t randn(void)
{
    static uint8_t i = 0;
    return random[i++];
}
