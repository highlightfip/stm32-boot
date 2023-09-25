/*
 * @Author: 2793393724@qq.com
 * @Date: 2023-09-20 21:39:23
 * @LastEditTime: 2023-09-23 18:20:05
 * @LastEditors: highlightfip 2793393724@qq.com
 * @Description: timer opr
 * @FilePath: \stm32-boot\bsp\tim.h
 */

#ifndef _TIM_H
#define _TIM_H

#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "gpio.h"

#define TIM_GROUP_NUM   1
#define TIM_NAME_T      uint16_t *
#define tim1            (uint16_t *)0
#define TIM_InitTypeDef TIM_OCInitTypeDef

/**
 * @brief: mode to define which InitTypeDef
 */
typedef enum
{
    TIM_BASE = 0x00, 
    TIM_OC = 0x10,
            TIM_OC1 = 0x11,TIM_OC2 = 0x12,
            TIM_OC3 = 0x13,TIM_OC4 = 0x14,
    TIM_IC = 0x20
}TIM_Mode;

/*** 
 * @brief: TIM information structure definition
 */
typedef struct
{
    TIM_NAME_T          tim_x;
    BSP_INFO_T          bsp_info;
    uint32_t            rcc_clock;
    TIM_TypeDef*        timx;
    TIM_Mode            tim_mode;
    TIM_InitTypeDef     tim_arg;
    NVIC_InitTypeDef    nvic_arg;
} TIM_INFO_T;

/*** 
 * @brief: TIM operater structure definition  
 */
typedef struct
{
    void (*open)(void *handle, void *dev_obj);
    void (*close)(void *handle);
}TIM_OPR_T;

/*** 
 * @brief: TIM handle structure definition
 */
typedef struct
{
    TIM_INFO_T tim_info;
    TIM_OPR_T tim_opr;
    GPIO_HANDLE_T gpio_handle;
}TIM_HANDLE_T;

extern void tim_opr_init(void *dev_obj_opr);

#endif
