/*
 * @Author: highlightfip
 * @Date: 2023-09-23 16:33:50
 * @LastEditTime: 2023-09-23 16:35:06
 * @LastEditors: highlightfip 2793393724@qq.com
 * @Description: virtual clock
 * @FilePath: \stm32-boot\periph\clock.h
 */

#ifndef _CLOCK_H
#define _CLOCK_H
#include "tim.h"


/*** 
 * @brief: clock opr structure
 */
typedef struct 
{
    void (*open)(void *handle, void *dev_obj);
    int8_t (*write)(void *handle, void *data);
    int8_t (*read)(void *handle, void *data);
    void (*close)(void *handle);
} LED_OPR_T;

#endif
