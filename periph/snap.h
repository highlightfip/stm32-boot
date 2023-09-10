/*
 * @Author: highlightfip
 * @Date: 2023-08-18 09:18:57
 * @LastEditTime: 2023-08-30 17:12:19
 * @LastEditors: highlightfip 2793393724@qq.com
 * @Description: control S2 & 4X4keyboard
 * @FilePath: \stm32-boot\periph\snap.h
 */

#ifndef _SNAP_H
#define _SNAP_H

#include "string.h"
#include "exti.h"

//debug check
#define PORT_OUTPUT_EXTI  1

#define SNAP_NAME_T         uint8_t *
#define snap0               (uint8_t *)0

/*** 
 * @brief: SNAP info structure
 */
typedef struct
{
    SNAP_NAME_T         snap_x;
    EXTI_NAME_T         exti_x[4];
} SNAP_INFO_T;

/*** 
 * @brief: SNAP operater structure definition
 */
typedef struct
{
    void (*open)(void *handle, void *dev_obj);
    void (*close)(void);
} SNAP_OPR_T;

#define SNAP_NAME_T uint16_t *
#define snap0 (uint8_t *)0

/*** 
 * @brief: SNAP handle structure definition
 */
typedef struct
{
    SNAP_NAME_T snapx;
    SNAP_INFO_T snap_info;
    SNAP_OPR_T snap_opr;
    EXTI_HANDLE_T exti_handle[4];
    GPIO_HANDLE_T vcc_gh[4];
} SNAPKB_HANDLE_T;

#define SNAPKB_GROUP_NUM (uint16_t)1

#define PortSource_GROUP(x)   (uint8_t)(x/GPIO_GROUP_NUM)
#define PinSource_GROUP(x)    (uint8_t)(x%GPIO_GROUP_NUM)

extern void snap_opr_init(void *dev_obj_opr);
extern void SNAP1_IRQ(uint8_t index);
extern void SNAP2_IRQ(uint8_t index);
extern void SNAP3_IRQ(uint8_t index);
extern void SNAP4_IRQ(uint8_t index);
#endif
