/*** 
 * @Author       : highlight
 * @Date         : 2023-08-07 20:48:44
 * @LastEditTime : 2023-08-09 14:43:50
 * @LastEditors  : highlight
 * @Description  : port for interaction
 * @FilePath     : \stm32-boot\periph\port.h
 */

#ifndef _PORT_H
#define _PORT_H

#include "usart.h"
#include "stdarg.h"
#include "string.h"

#define u32 uint32_t
#define port1 (uint32_t)0
typedef uint32_t PORT_NAME_T;

typedef struct 
{
    PORT_NAME_T portx;
    USART_NAME_T usartx;
} PORT_INFO_T;

/*** 
 * @brief: PORT operater structure definition
 */
typedef struct
{
    void        (*open)(void *handle, void *dev_obj);
    int32_t     (*print)(void *handle, const char *frm , ...);
    void        (*close)(void *handle);
} PORT_OPR_T;


/*** 
 * @brief: port handle
 */
typedef struct
{
    PORT_INFO_T port_info;
    PORT_OPR_T port_opr;
    USART_HANDLE_T usart_handle;
} PORT_HANDLE_T;


extern void port_opr_init(void *dev_obj_opr);

#endif
