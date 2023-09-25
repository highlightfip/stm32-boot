/*** 
 * @Author       : highlight
 * @Date         : 2023-08-04 21:55:56
 * @LastEditTime : 2023-08-07 15:59:08
 * @LastEditors  : highlight
 * @Description  : led control
 * @FilePath     : \stm32-boot\periph\led.h
 */


#ifndef _LED_H
#define _LED_H

#include "gpio.h"
#include "tim.h"

/*** 
 * @brief: led name
 */
typedef uint32_t * LED_NAME_T;

/*** 
 * @brief: led state
 */
typedef enum
{
    LV0,LV1,LV2,LV3,LV4
} LED_STATE;

/*** 
 * @brief: led opr structure
 */
typedef struct 
{
    void (*open)(void *handle, void *dev_obj);
    int8_t (*write)(void *handle, void *data);
    int8_t (*read)(void *handle, void *data);
    void (*close)(void *handle);
} LED_OPR_T;

/*** 
 * @brief: led info structure
 */
typedef struct
{
    LED_NAME_T led_name;
    BSP_INFO_T bsp_info;
    LED_STATE  LVx;
} LED_INFO_T;

/*** 
 * @brief: led handle structure
 */
typedef struct
{
    LED_OPR_T led_opr;
    LED_INFO_T led_info;
    GPIO_HANDLE_T gh;
} LED_HANDLE_T;

#define led1 (uint32_t *)0
#define LED_GROUP_NUM 1
#define ON (uint32_t *)0
#define OFF ON+1

extern void led_opr_init(void *dev_obj_opr);

#endif
