/*
 * @Author       : highlight
 * @Date         : 2023-08-07 22:30:04
 * @LastEditTime: 2023-08-10 14:21:17
 * @LastEditors: highlightfip 2793393724@qq.com
 * @Description  : 
 * @FilePath     : \stm32-boot\bsp\usart.c
 */

#include "gpio.h"
#include "usart.h"
#include "string.h"

static USART_INFO_T USART_INFO_GROUP[USART_GROUP_NUM] =
{
    {
        usart1,
        {
            {  /*TX*/
                PA9,  
                GPIO_Mode_AF_PP
            },
            {   /*RX*/
                PA10, 
                GPIO_Mode_IN_FLOATING
            }
        },
        2,
        USART1,
        RCC_APB2Periph_USART1,
        {
            /* USART_InitStruct members default value */
            9600,
            USART_WordLength_8b,
            USART_StopBits_1,
            USART_Parity_No,
            USART_Mode_Rx | USART_Mode_Tx,
            USART_HardwareFlowControl_None
        }
    }
};

static void open(void *handle, void *dev_obj);
static void write(void *handle, void *data);
static uint16_t read(void *handle);
static void close(void *handle);

/**
 * @brief: int the operator
 * @param {USART_OPR_T} *dev_obj_opr
 * @retval: None
 */
extern void usart_opr_init(void *dev_obj_opr)
{
    ((USART_OPR_T *)dev_obj_opr)->open = open;
    ((USART_OPR_T *)dev_obj_opr)->write = write;
    ((USART_OPR_T *)dev_obj_opr)->read = read;
    ((USART_OPR_T *)dev_obj_opr)->close = close;
}

/**
 * @brief: open the device
 * @param {USART_HANDLE_T} *handle
 * @param {void} *dev_obj select the device
 * @retval: None
 */
static uint8_t i = 0;
static void open(void *handle, void *dev_obj)
{
    USART_HANDLE_T *uh = (USART_HANDLE_T *)handle;
    
    memcpy(&(uh->usart_info), &USART_INFO_GROUP+(*((uint32_t *)dev_obj)), sizeof(USART_INFO_T));
    
    gpio_opr_init(&(uh->gpio_handle.gpio_opr));
    while (i < uh->usart_info.usart_io_num)
    {
        uh->gpio_handle.gpio_opr.open(&(uh->gpio_handle), &(uh->usart_info.usart_io)+i);
        i++;
    }

    RCC_APB2PeriphClockCmd(uh->usart_info.usart_clock, ENABLE);
    USART_Init(uh->usart_info.usartx, &(uh->usart_info.usart_initstruct));
    USART_Cmd(uh->usart_info.usartx, ENABLE);
}

/**
 * @brief: write the device
 * @param {USART_HANDLE_T} *handle
 * @param {uint16_t *} *data
 * @retval: 
 */
static void write(void *handle, void *data)
{

    USART_HANDLE_T *uh = (USART_HANDLE_T *)handle;
    while(RESET == USART_GetFlagStatus(uh->usart_info.usartx, USART_FLAG_TC));
    USART_SendData(uh->usart_info.usartx, (uint16_t )data);
}

/**
 * @brief: read the device
 * @param {USART_HANDLE_T} *handle
 * @retval: {uint16_t} data
 */
static uint16_t read(void *handle)
{
    USART_HANDLE_T *uh = (USART_HANDLE_T *)handle;
    /*
    uint16_t str[MAX_USART_RECEIVE_LEN];
    */
    return USART_ReceiveData(uh->usart_info.usartx);
}

/**
 * @brief: close the device
 * @param {USART_HANDLE_T} *handle
 */
static void close(void *handle)
{
    USART_HANDLE_T *uh = (USART_HANDLE_T *)handle;

    USART_DeInit(uh->usart_info.usartx);
}

extern void uart_send(char *string)
{
    u32 i = 0;
    //USART_ClearFlag(USART1, USART_FLAG_TC);
    while(string[i])
    {
        //确定reset再发送数据
        while(RESET == USART_GetFlagStatus(USART1, USART_FLAG_TC));
        USART_SendData(USART1, string[i]);
        i++;
    }

    return ;
}
