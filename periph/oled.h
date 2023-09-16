/*
 * @Author: highlightfip
 * @Date: 2023-08-19 11:13:33
 * @LastEditTime: 2023-09-16 21:44:27
 * @LastEditors: 2793393724@qq.com 2793393724@qq.com
 * @Description: oled opr
 * @FilePath: \stm32-boot\periph\oled.h
 */

#ifndef _OLED_H
#define _OLED_H

#include "i2c.h"
#include "string.h"

#define OLED_NAME_T             uint16_t *
#define oled1                   (uint16_t *)0

#define OLED_PRINT_MODE_T       uint16_t
#define OLED_PRINT_CLEAR        (uint16_t)0
#define OLED_PRINT_FILL         (uint16_t)1
#define OLED_PRINT_BMP          (uint16_t)2
#define OLED_PRINT_CH           (uint16_t)3
#define DATA_MAX_LEN            (uint16_t)16

#define IS_DATA_SPILL(y_entity, y_offset)\
            ((y_entity/8+1)!=((y_entity+y_offset)/8+1))

#define FONT_DEFAULT            (uint8_t *)0
#define FONT_F6x8               (uint8_t *)0
#define FONT_F16x24             (uint8_t *)1
#define FONT_F4x6               (uint8_t *)2

typedef struct
{
    uint8_t data_ptr[DATA_MAX_LEN];
    uint8_t *data_ptr1;
    uint8_t x;
    uint8_t y;
    uint8_t x1;
    uint8_t y1;
} OLED_PRINT_DATA_T;

#define CLEAR_OLED &OLED_PRINT_GROUP[0x2]
#define FILL_OLED  &OLED_PRINT_GROUP[0x3]

typedef struct
{
    OLED_PRINT_MODE_T mode;
    OLED_PRINT_DATA_T data;
} OLED_PRINT_T;

typedef struct 
{
    OLED_NAME_T oledx;
    I2C_NAME_T i2cx;
} OLED_INFO_T;

/*** 
 * @brief: I2C operater structure definition  
 */
typedef struct
{
    void (*open)(void *handle, void *dev_obj);
    int8_t (*print)(void *handle, void *data);
    void (*close)(void *handle);
} OLED_OPR_T;

typedef struct
{
    OLED_INFO_T     oled_info;
    OLED_OPR_T      oled_opr;
    I2C_HANDLE_T    i2c_handle;
} OLED_HANDLE_T;

extern OLED_PRINT_T OLED_PRINT_GROUP[4];
extern void oled_opr_init(void *handle);

#endif
