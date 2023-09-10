/*
 * @Author: highlightfip 2793393724@qq.com
 * @Date: 2023-08-07 22:30:13
 * @LastEditors: highlightfip 2793393724@qq.com
 * @LastEditTime: 2023-08-10 14:22:00
 * @FilePath: \stm32-boot\bsp\usart.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
/*** 
 * @Author       : highlight
 * @Date         : 2023-08-07 22:30:13
 * @LastEditTime : 2023-08-09 22:40:17
 * @LastEditors  : highlight
 * @Description  : 
 * @FilePath     : \stm32-boot\bsp\usart.h
 */

#ifndef _USART_H
#define _USART_H

#include "gpio.h"

#include "stm32f10x_usart.h"

#define USART_NAME_T uint32_t
#define MAX_USART_RECEIVE_LEN 
/*** 
 * @brief: USART info structure
 */
typedef struct
{
    USART_NAME_T        usart_x;
    BSP_INFO_T          usart_io[2];
    uint32_t            usart_io_num;
    USART_TypeDef*      usartx;
    uint32_t            usart_clock;
    USART_InitTypeDef   usart_initstruct;
} USART_INFO_T;

/*** 
 * @brief: USART operater structure definition
 */
typedef struct
{
    void (*open)(void *handle, void *dev_obj);
    void (*write)(void *handle, void *data);
    uint16_t (*read)(void *handle);
    void (*close)(void *handle);
} USART_OPR_T;

/*** 
 * @brief: USART handle structure definition
 */
typedef struct
{
    USART_INFO_T usart_info;
    USART_OPR_T usart_opr;
    GPIO_HANDLE_T gpio_handle;
} USART_HANDLE_T;

#define USART_GROUP_NUM 1
#define usart1 (uint32_t)0

extern void usart_opr_init(void *dev_obj_opr);
extern void uart_send(char *string);

#endif
