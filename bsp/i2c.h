/*
 * @Author: highlightfip
 * @Date: 2023-08-19 09:42:32
 * @LastEditTime: 2023-09-24 21:45:57
 * @LastEditors: highlightfip 2793393724@qq.com
 * @Description: 
 * @FilePath: \stm32-boot\bsp\i2c.h
 */


#ifndef _I2C_H
#define _I2C_H

#include "string.h"
#include "stm32f10x.h"
#include "stm32f10x_i2c.h"
#include "gpio.h"

#define I2C_NAME_T  uint16_t *
#define i2c1        (uint16_t *)0

/*** 
 * @brief: I2C information structure definition
 */
typedef struct
{
    BSP_INFO_T      bsp_info[2];
    uint32_t        rcc_clock;
    I2C_TypeDef*    i2cx;
    I2C_InitTypeDef i2c_arg;
} I2C_INFO_T;

/*** 
 * @brief: I2C operater structure definition  
 */
typedef struct
{
    void (*open)(void *handle, void *dev_obj);
    void (*write)(void *handle, uint8_t addr, uint8_t data);
}I2C_OPR_T;

/*** 
 * @brief: I2C handle structure definition
 */
typedef struct
{
    I2C_INFO_T i2c_info;
    I2C_OPR_T i2c_opr;
    GPIO_HANDLE_T gpio_handle;
}I2C_HANDLE_T;

#define I2C_ADDR_CMD (uint8_t)0x00
#define I2C_ADDR_DATA (uint8_t)0x40

extern void i2c_opr_init(void *dev_obj_opr);

#endif
