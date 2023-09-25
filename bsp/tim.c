/*
 * @Author: 2793393724@qq.com
 * @Date: 2023-09-20 21:37:36
 * @LastEditTime: 2023-09-23 18:47:44
 * @LastEditors: highlightfip 2793393724@qq.com
 * @Description: timer opr
 * @FilePath: \stm32-boot\bsp\tim.c
 */

#include "tim.h"
#include "debug.h"

static TIM_INFO_T TIM_INFO_GROUP[TIM_GROUP_NUM] =
{
	{
        tim1,
        {//TIM2_CH1
            PA0,
            GPIO_Mode_AF_PP
        },
        RCC_APB1Periph_TIM2,
        TIM2,
        TIM_BASE,
        {
            7199, // 设置预分频器值
            TIM_CounterMode_Up, // 设置计数器方向为向上计数
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

static TIM_INFO_T* Tim_NvicInfo[TIM_GROUP_NUM];

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
    ((TIM_OPR_T *)dev_obj_opr)->close = close;
}

/**
 * @brief: open the timer
 * @param {TIM_HANDLE_T} *handle
 * @param {void} *dev_obj
 * @retval: none
 */
static void open(void *handle, void *dev_obj)
{
    TIM_HANDLE_T *th = (TIM_HANDLE_T *)handle;

	memcpy(&(th->tim_info), &TIM_INFO_GROUP+((uint32_t)dev_obj), sizeof(TIM_INFO_T));

	RCC_APB1PeriphClockCmd(th->tim_info.rcc_clock,ENABLE);

	gpio_opr_init(&(th->gpio_handle.gpio_opr));
	th->gpio_handle.gpio_opr.open(&(th->gpio_handle), &th->tim_info.bsp_info);

    //初始化定时器
    switch(th->tim_info.tim_mode & 0xf0)
    {
        case TIM_BASE: 
	        TIM_TimeBaseInit(th->tim_info.timx, (TIM_TimeBaseInitTypeDef *)(&th->tim_info.tim_arg));
            break;
        case TIM_OC:
            switch(th->tim_info.tim_mode & 0x1f)
            {
                case TIM_OC1:
	                TIM_OC1Init(th->tim_info.timx, (TIM_OCInitTypeDef *)(&th->tim_info.tim_arg));
                    break;
                case TIM_OC2:
	                TIM_OC2Init(th->tim_info.timx, (TIM_OCInitTypeDef *)(&th->tim_info.tim_arg));
                    break;
                case TIM_OC3:
	                TIM_OC2Init(th->tim_info.timx, (TIM_OCInitTypeDef *)(&th->tim_info.tim_arg));
                    break;
                case TIM_OC4:
	                TIM_OC2Init(th->tim_info.timx, (TIM_OCInitTypeDef *)(&th->tim_info.tim_arg));
                    break;
                default :
                    break;
            }
            break;
        case TIM_IC:
	        TIM_ICInit(th->tim_info.timx, (TIM_ICInitTypeDef *)(&th->tim_info.tim_arg));
            break;
        default:
            bug_check_loc("timer init fault!");
            break;
    }

    // 启动定时器
	TIM_Cmd(th->tim_info.timx, ENABLE);

    // 配置定时器系统中断
    NVIC_Init(&th->tim_info.nvic_arg);

    // 用于中断完成
    Tim_NvicInfo[(uint32_t)dev_obj] = &th->tim_info;
}

static void close(void *handle)
{
	TIM_HANDLE_T *th = (TIM_HANDLE_T *)handle;
}

void TIM2_IRQHandler(void)
{
    // 处理定时器达到预设值事件
	if(SET == TIM_GetITStatus(TIM2, TIM_IT_Trigger))
	{
        // 在这里更新计数器值
        ((TIM_TimeBaseInitTypeDef *)(&Tim_NvicInfo[0]->tim_arg))->TIM_Period = 999 - TIM_GetCounter(TIM2); // 计算新的计数器值
        TIM_TimeBaseInit(TIM2, (TIM_TimeBaseInitTypeDef *)(&Tim_NvicInfo[0]->tim_arg));

        bug_check_loc("TIM2_IRQHandler response");
    }
    TIM_ClearITPendingBit(TIM2, TIM_IT_Trigger);
}