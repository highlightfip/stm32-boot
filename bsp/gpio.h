/*** 
 * @Author       : highlight
 * @Date         : 2023-08-05 16:36:03
 * @LastEditTime : 2023-08-07 10:50:51
 * @LastEditors  : highlight
 * @Description  : gpio operation
 * @FilePath     : \stm32-boot\bsp\gpio.h
 */

#ifndef _GPIO_H
#define _GPIO_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"


/*** 
 * @brief: gpio pin simplfyed name, use in ../periph
 */
typedef enum
{
    PA0,PA1,PA2,PA3,PA4,PA5,PA6,PA7,PA8,PA9,PA10,PA11,PA12,PA13,PA14,PA15,
    PB0,PB1,PB2,PB3,PB4,PB5,PB6,PB7,PB8,PB9,PB10,PB11,PB12,PB13,PB14,PB15,
    PC0,PC1,PC2,PC3,PC4,PC5,PC6,PC7,PC8,PC9,PC10,PC11,PC12,PC13,PC14,PC15,
    PD0,PD1,PD2,PD3,PD4,PD5,PD6,PD7,PD8,PD9,PD10,PD11,PD12,PD13,PD14,PD15,
    PE0,PE1,PE2,PE3,PE4,PE5,PE6,PE7,PE8,PE9,PE10,PE11,PE12,PE13,PE14,PE15,
    PF0,PF1,PF2,PF3,PF4,PF5,PF6,PF7,PF8,PF9,PF10,PF11,PF12,PF13,PF14,PF15,
    PG0,PG1,PG2,PG3,PG4,PG5,PG6,PG7,PG8,PG9,PG10,PG11,PG12,PG13,PG14,PG15,
}GPIO_PIN_NAME_T;

/*** 
 * @brief: 
 */
typedef enum
{
    IN_AN,
    IN_FL,
    IN_UP,
    IN_DOWN,
    OUT_OD,
    OUT_PP,
    AF_OD,
    AF_PP
}GPIO_MODE_T;

typedef struct
{
    GPIO_PIN_NAME_T pin;
    GPIOMode_TypeDef mode;
	//GPIO_MODE_T mode;
}BSP_INFO_T;

/** 
  * @brief  GPIO dir definition  
  */
typedef enum  
{
  GPIO_IN,GPIO_OUT
}GPIO_DIR_T;

/*** 
 * @brief: GPIO information structure definition
 */
typedef struct
{
    uint32_t rcc_clock;
    GPIO_TypeDef* gpiox;
    GPIO_InitTypeDef gpio_arg;
}GPIO_INFO_T;

/*** 
 * @brief: GPIO operater structure definition  
 */
typedef struct
{
    void (*open)(void *handle, void *dev_obj);
    int8_t (*write)(void *handle, void *data);
    int8_t (*read)(void *handle, void *data);
    void (*close)(void *handle);
}GPIO_OPR_T;

/*** 
 * @brief: GPIO handle structure definition
 */
typedef struct
{
    GPIO_INFO_T gpio_info;
    GPIO_OPR_T gpio_opr;
}GPIO_HANDLE_T;

/*** 
 * @brief: gpio pin Exported Constants
 */
#define GPIO_GROUP_NUM 16
#define GPIO_TYPEDEF_GROUP(x)  (GPIO_TypeDef*)(APB2PERIPH_BASE + (0x0800+0x400*(x)))
#define GPIO_PIN(x) GPIO_Pin_0<<(x)
#define GPIO_RCC_CLOCK(x) RCC_APB2Periph_GPIOA<<(x)
#define GPIO_RCC_PeriphClockEnable(gpio_clock) RCC_APB2PeriphClockCmd(gpio_clock,ENABLE)
#define GPIO_MODE_IS(mode) ((mode) == GPIO_Mode_Out_OD ||  (mode) == GPIO_Mode_Out_PP)?GPIO_OUT:\
(((mode) == GPIO_Mode_IPU ||  (mode) == GPIO_Mode_IPD)?GPIO_IN:-1) 
#define GPIO_Speed_MAX GPIO_Speed_50MHz


extern void gpio_opr_init(void *dev_obj_opr);

#endif
