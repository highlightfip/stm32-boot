/*
 * @Author       : highlight
 * @Date         : 2023-08-09 22:37:46
 * @LastEditTime: 2023-09-24 15:32:07
 * @LastEditors: highlightfip 2793393724@qq.com
 * @Description  : exti
 * @FilePath: \stm32-boot\bsp\exti.c
 */

#include "exti.h"
#include "debug.h"
// #include "string.h"

static EXTI_INFO_T EXTI_INFO_GROUP[EXTI_GROUP_NUM] =
{
    {
        exti0,
        {
            PC14,
            GPIO_Mode_IPU
        },
        {
            EXTI_Line1,
            EXTI_Mode_Interrupt,
            EXTI_Trigger_Falling,
            ENABLE
        },
        {
            EXTI15_10_IRQn,
            1,
            0,
            ENABLE
        }
    },
    {
        exti1,
        {
            PA1,
            GPIO_Mode_IPU
        },
        {
            EXTI_Line1,
            EXTI_Mode_Interrupt,
            EXTI_Trigger_Falling,
            ENABLE
        },
        {
            EXTI1_IRQn,
            1,
            0,
            ENABLE
        }
    },
    {
        exti2,
        {
            PA0,
            GPIO_Mode_IPU
        },
        {
            EXTI_Line0,
            EXTI_Mode_Interrupt,
            EXTI_Trigger_Falling,
            ENABLE
        },
        {
            EXTI0_IRQn,
            1,
            0,
            ENABLE
        }
    },
    {
        exti3,
        {
            PA3,
            GPIO_Mode_IPU
        },
        {
            EXTI_Line3,
            EXTI_Mode_Interrupt,
            EXTI_Trigger_Falling,
            ENABLE
        },
        {
            EXTI3_IRQn,
            1,
            0,
            ENABLE
        }
    },
    {
        exti4,
        {
            PA4,
            GPIO_Mode_IPU
        },
        {
            EXTI_Line4,
            EXTI_Mode_Interrupt,
            EXTI_Trigger_Falling,
            ENABLE
        },
        {
            EXTI4_IRQn,
            1,
            0,
            ENABLE
        }
    }
};

static void open(void *handle, void *dev_obj);
static void close(void);

/**
 * @brief: int the operator
 * @param dev_obj_opr pointer of exti_opr
 * @retval: None
 */
extern void exti_opr_init(void *dev_obj_opr)
{
    ((EXTI_OPR_T *)dev_obj_opr)->open = open;
    ((EXTI_OPR_T *)dev_obj_opr)->close = close;
}


/**
 * @brief: function<memcpy> seen not work, here is the another 'memcpy'
 * @param han exti_handle
 * @param dev dev_obj such as 0, 1, 2...
 * @retval: 
 */
static void MemoryCopy(void *han, void *dev)
{
	((EXTI_HANDLE_T *)han)->exti_info = EXTI_INFO_GROUP[(uint16_t)dev];
}


/**
 * @brief: open the device
 * @param {EXTI_HANDLE_T} *handle
 * @param {void} *dev_obj select the device
 * @retval: None
 */
void open(void *handle, void *dev_obj)
{
    EXTI_HANDLE_T *eh = (EXTI_HANDLE_T *)handle;
    
    MemoryCopy(eh, dev_obj);
    
    gpio_opr_init(&(eh->gpio_handle.gpio_opr));
    eh->gpio_handle.gpio_opr.open(&eh->gpio_handle, &(eh->exti_info.exti_io));
    
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_EXTILineConfig(PortSource_GROUP(eh->exti_info.exti_io.pin), PinSource_GROUP(eh->exti_info.exti_io.pin));
    EXTI_Init(&(eh->exti_info.exti_arg));

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_Init(&(eh->exti_info.nvic_arg));
}

/**
 * @brief: close the device
 */
static void close(void)
{
    EXTI_DeInit();
}
