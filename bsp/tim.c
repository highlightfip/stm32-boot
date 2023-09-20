/*
 * @Author: 2793393724@qq.com
 * @Date: 2023-09-20 21:37:36
 * @LastEditTime: 2023-09-20 23:34:16
 * @LastEditors: 2793393724@qq.com 2793393724@qq.com
 * @Description: timer opr
 * @FilePath: \stm32-boot\bsp\tim.c
 */

#include "tim.h"

static TIM_INFO_T TIM_INFO_GROUP[1] =
{
	{
        tim1,
        PD0,
        TIM2,
        Base,
        {
            7199, // 设置预分频器值
            TIM_CounterDIR_Up, // 设置计数器方向为向上计数
            999, // 设置计数器周期值
            TIM_CKD_DIV1, // 设置时钟分频器
        },
        {
            TIM2_IRQn,
            0,
            0,
            ENABLE
        }
	}
};

static void open(void *handle, void *dev_obj);
static void write(void *handle, uint8_t addr, uint8_t data);
static void close(void *handle);

/**
 * @brief: int the operator
 * @param {GPIO_OPR_T} *dev_obj_opr
 * @retval: None
 */
extern void tim_opr_init(void *dev_obj_opr)
{
    ((TIM_OPR_T *)dev_obj_opr)->open = open;
    ((TIM_OPR_T *)dev_obj_opr)->write = write;
    ((TIM_OPR_T *)dev_obj_opr)->close = close;
}

static void open(void *handle, void *dev_obj)
{

    // 配置定时器中断
    TIM_INTConfig(TIM2, TIM_INT_Update, ENABLE);
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;


    TIM_HANDLE_T *th = (TIM_HANDLE_T *)handle;

	memcpy(&(th->tim_info), &TIM_INFO_GROUP+((uint32_t)dev_obj), sizeof(TIM_INFO_T));

	RCC_APB1PeriphClockCmd(th->tim_info.rcc_clock,ENABLE);

	gpio_opr_init(&(th->gpio_handle.gpio_opr));
	th->gpio_handle.gpio_opr.open(&(th->gpio_handle), &th->tim_info.bsp_info);

    // 启动定时器
	TIM_Cmd(th->tim_info.timx, ENABLE);

    //初始化定时器
    switch(th->tim_info.tim_mode)
    {
        case Base: 
	        TIM_TimeBaseInit(th->tim_info.timx, &((TIM_TimeBaseInitTypeDef)th->tim_info.tim_arg));
            break;
        case InputComp:
	        TIM_OC1Init(th->tim_info.timx, &((TIM_OCInitTypeDef)th->tim_info.tim_arg));
            break;
        case OutputComp:
	        TIM_ICInit(th->tim_info.timx, &((TIM_ICInitTypeDef)th->tim_info.tim_arg));
            break;
        default:
            bug_check_loc("timer init fault!");
            break;
    }

    // 配置定时器系统中断
    NVIC_Init(&th->tim_info.nvic_arg);
}

static void write(void *handle, uint8_t data)
{
    TIM_HANDLE_T *th = (TIM_HANDLE_T *)handle;


}

static void close(void *handle)
{
	TIM_HANDLE_T *th = (TIM_HANDLE_T *)handle;
	bug_check();
}

void TimerInterruptHandler(void)
{
  // 处理定时器中断事件
  TIM_ClearINTPendingBit(TIM2, TIM_INT_Update);

  // 在这里更新计数器值
  TIM_TimeBaseInitType timer_init_structure;
  TIM_TimeBaseGetConfig(TIM2, &timer_init_structure);
  timer_init_structure.TIM_Period = 999 - TIM_GetCounter(TIM2); // 计算新的计数器值
  TIM_TimeBaseInit(TIM2, &timer_init_structure);
}