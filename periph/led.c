/*
 * @Author       : highlight
 * @Date         : 2023-08-04 21:55:27
 * @LastEditTime : 2023-08-08 15:08:18
 * @LastEditors  : highlight
 * @Description  : led control
 * @FilePath     : \stm32-boot\periph\led.c
 */

#include "led.h"
#include "string.h"

static LED_INFO_T LED_INFO_GROUP[LED_GROUP_NUM] =
{
    {
        led1,
        {
            PC13,
            GPIO_Mode_Out_OD
        },
        LV1
    }
};

static void open(void *handle, void *dev_obj);
static int8_t write(void *handle, void *data);
static int8_t read(void *handle, void *data);
static void close(void *handle);

/**
 * @brief: init the led controller
 * @param {LED_OPR_T} *dev_obj_opr
 * @retval: None
 */
void led_opr_init(void *dev_obj_opr)
{
    ((LED_OPR_T *)dev_obj_opr)->open = open;
    ((LED_OPR_T *)dev_obj_opr)->write = write;
    ((LED_OPR_T *)dev_obj_opr)->read = read;
    ((LED_OPR_T *)dev_obj_opr)->close = close;
}

/**
 * @brief: 
 * @param {LED_HANDLE_T} *handle
 * @param {void} *dev_obj
 * @retval: 
 */
static void open(void *handle, void *dev_obj)
{
    LED_HANDLE_T *lh = (LED_HANDLE_T *)handle;

    gpio_opr_init(&(lh->gh.gpio_opr));
    memcpy(&lh->led_info, &LED_INFO_GROUP+((uint32_t)dev_obj), sizeof(LED_INFO_T));
    
    lh->gh.gpio_opr.open(&(lh->gh), &(lh->led_info.bsp_info));
}

/**
 * @brief: 
 * @param {LED_HANDLE_T} *handle
 * @param {void} *data
 * @retval: 
 */
static int8_t write(void *handle, void *data)
{
    uint8_t result_state = 0;
    uint8_t led_state = ((LED_HANDLE_T *)handle)->led_info.LVx;
    LED_HANDLE_T *lh = (LED_HANDLE_T *)handle;

    if (data == OFF)
    {
        lh->gh.gpio_opr.write(&(lh->gh), (uint32_t *)(data));
        return result_state;
    }

    switch(led_state)
    {
        case LV0: 
            lh->gh.gpio_opr.write(&(lh->gh), OFF);
        break;
        case LV1: 
            lh->gh.gpio_opr.write(&(lh->gh), (uint32_t *)(data));
        break;
        case LV2: break;
        case LV3: break;
        case LV4: break;
    }
    
    return result_state;
}

/**
 * @brief: read the device
 * @param {LED_HANDLE_T} *handle
 * @param {uint8_t} *data
 * @retval: 
 */
static int8_t read(void *handle, void *data)
{
    int8_t result_state = 0;
    LED_HANDLE_T *lh = (LED_HANDLE_T *)handle;

    data = &lh->led_info.LVx;

    return result_state;
}

/**
 * @brief: close the device
 * @param {void} *handle
 * @retval: 
 */
static void close(void *handle)
{
    
    return ;
}
