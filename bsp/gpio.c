/*
 * @Author       : highlight
 * @Date         : 2023-08-05 16:36:12
 * @LastEditTime : 2023-08-07 11:51:02
 * @LastEditors  : highlight
 * @Description  : gpio operation
 * @FilePath     : \stm32-boot\bsp\gpio.c
 */

#include "gpio.h"

static void open(void *handle, void *dev_obj);
static int8_t write(void *handle, void *data);
static int8_t read(void *handle, void *data);
static void close(void *handle);

/**
 * @brief: int the operator
 * @param {GPIO_OPR_T} *dev_obj_opr
 * @retval: None
 */
void gpio_opr_init(void *dev_obj_opr)
{
    ((GPIO_OPR_T *)dev_obj_opr)->open = open;
    ((GPIO_OPR_T *)dev_obj_opr)->write = write;
    ((GPIO_OPR_T *)dev_obj_opr)->read = read;
    ((GPIO_OPR_T *)dev_obj_opr)->close = close;
}

/**
 * @brief: open the device
 * @param {GPIO_HANDLE_T} *handle
 * @param {BSP_INFO_T} *dev_obj
 * @retval: 
 */
static void open(void *handle, void *dev_obj)
{	
    GPIO_INFO_T *gi = &((GPIO_HANDLE_T *)handle)->gpio_info;
    BSP_INFO_T *bsp_info = (BSP_INFO_T *)dev_obj;

    gi->rcc_clock = GPIO_RCC_CLOCK(bsp_info->pin/GPIO_GROUP_NUM);
    gi->gpiox = GPIO_TYPEDEF_GROUP(bsp_info->pin/GPIO_GROUP_NUM);

    gi->gpio_arg.GPIO_Pin = GPIO_PIN(bsp_info->pin%GPIO_GROUP_NUM);
    gi->gpio_arg.GPIO_Speed = GPIO_Speed_MAX;
    gi->gpio_arg.GPIO_Mode = bsp_info->mode;

    RCC_APB2PeriphClockCmd(gi->rcc_clock, ENABLE);
    GPIO_Init(gi->gpiox, &(gi->gpio_arg));
}

/**
 * @brief: write the device
 * @param {GPIO_HANDLE_T} *handle
 * @param {void} *data
 * @retval: opr result
 */
static int8_t write(void *handle, void *data)
{
    GPIO_INFO_T *gi = &(((GPIO_HANDLE_T *)handle)->gpio_info);
    int8_t result_state = 0;
    if(GPIO_MODE_IS(gi->gpio_arg.GPIO_Mode) == GPIO_OUT)
    {
        GPIO_WriteBit(gi->gpiox, gi->gpio_arg.GPIO_Pin, (BitAction)((uint32_t)(data)));
    }
    else
    {
        result_state = -1;
    }
    return result_state;
}

/**
 * @brief: read the device
 * @param {GPIO_HANDLE_T} *handle
 * @param {void} *data point to read result
 * @retval: opr result
 */
static int8_t read(void *handle, void *data)
{
    GPIO_INFO_T *gi = &(((GPIO_HANDLE_T *)handle)->gpio_info);
    int8_t result_state = 0;

    if(GPIO_MODE_IS(gi->gpio_arg.GPIO_Mode) == GPIO_IN )
	{
		result_state =  GPIO_ReadInputDataBit(gi->gpiox,gi->gpio_arg.GPIO_Pin);
		*(int8_t *)data = result_state;
	}
	else if(GPIO_MODE_IS(gi->gpio_arg.GPIO_Mode) == GPIO_OUT )
	{
		result_state =  GPIO_ReadOutputDataBit(gi->gpiox,gi->gpio_arg.GPIO_Pin);
		*(int8_t *)data = result_state;
	}
	else
	{
		result_state = -1;
	}

	return result_state;
}

/**
 * @brief: close the device
 * @param {GPIO_HANDLE_T} *handle
 */
static void close(void *handle)
{

}
