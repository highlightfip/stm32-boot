/*
 * @Author: highlightfip
 * @Date: 2023-08-18 09:18:57
 * @LastEditTime: 2023-09-13 22:14:21
 * @LastEditors: 2793393724@qq.com 2793393724@qq.com
 * @Description: control S2 & 4X4keyboard
 * @FilePath: \stm32-boot\periph\snap.h
 */

#ifndef _SNAP_H
#define _SNAP_H

#include "string.h"
#include "exti.h"

//debug check
#define PORT_OUTPUT_EXTI  1

#define SNAPKB_NAME_T         uint8_t *
#define snapKB               (uint8_t *)0

/*** 
 * @brief: SNAP info structure
 */
typedef struct
{
    SNAPKB_NAME_T         snap_x;
    EXTI_NAME_T         exti_x[4];
} SNAP_INFO_T;

/*** 
 * @brief: SNAP operater structure definition
 */
typedef struct
{
    void (*open)(void *handle, void *dev_obj);
    void (*read)(void *handle, void *data);
    void (*close)(void *handle);
} SNAP_OPR_T;

#define SNAPKB_NAME_T uint16_t *
#define snapKB (uint8_t *)0

/*** 
 * @brief: SNAP handle structure definition
 */
typedef struct
{
    SNAPKB_NAME_T snapx;
    SNAP_INFO_T snap_info;
    SNAP_OPR_T snap_opr;
    EXTI_HANDLE_T exti_handle[4];
    GPIO_HANDLE_T vcc_gh[4];
} SNAPKB_HANDLE_T;

/**
 * @brief: record the snap keyboard touch feedback
 */
typedef struct
{
    uint8_t snapkb_state;
    uint8_t act_record[16];
} SNAPKB_FEEDBACK_T;

typedef enum
{
    S11,S12,S13,S14,
    S21,S22,S23,S24,
    S31,S32,S33,S34,
    S41,S42,S43,S54,
} SNAP_NAME_T;

#define SNAPKB_GROUP_NUM (uint16_t)1

#define PortSource_GROUP(x)   (uint8_t)(x/GPIO_GROUP_NUM)
#define PinSource_GROUP(x)    (uint8_t)(x%GPIO_GROUP_NUM)

extern void snap_opr_init(void *dev_obj_opr);
#endif
