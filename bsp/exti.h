/*** 
 * @Author       : highlight
 * @Date         : 2023-08-09 22:39:50
 * @LastEditTime : 2023-08-09 22:41:18
 * @LastEditors  : highlight
 * @Description  : exti
 * @FilePath     : \stm32-boot\bsp\exti.h
 */

#ifndef _EXTI_H
#define _EXTI_H

#include "gpio.h"
#include "stm32f10x_exti.h"

#define EXTI_NAME_T uint16_t *
#define exti0       (uint16_t *)0
#define exti1       (uint16_t *)1
#define exti2       (uint16_t *)2
#define exti3       (uint16_t *)3
#define exti4       (uint16_t *)4

/*** 
 * @brief: EXTI info structure
 */
typedef struct
{
    EXTI_NAME_T         exti_x;
    BSP_INFO_T          exti_io;
    EXTI_InitTypeDef    exti_arg;
    NVIC_InitTypeDef    nvic_arg;
} EXTI_INFO_T;

/*** 
 * @brief: EXTI operater structure definition
 */
typedef struct
{
    void (*open)(void *handle, void *dev_obj);
    void (*close)(void);
} EXTI_OPR_T;

/*** 
 * @brief: EXTI handle structure definition
 */
typedef struct
{
    EXTI_INFO_T exti_info;
    EXTI_OPR_T exti_opr;
    GPIO_HANDLE_T gpio_handle;
} EXTI_HANDLE_T;

#define EXTI_GROUP_NUM 5
#define exti_group1 (uint32_t)0

#define PortSource_GROUP(IO) (IO/GPIO_GROUP_NUM)
#define PinSource_GROUP(IO)  (IO%GPIO_GROUP_NUM)

extern void exti_opr_init(void *dev_obj_opr);

#endif
