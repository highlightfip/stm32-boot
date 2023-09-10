/*
 * @Author: highlightfip
 * @Date: 2023-08-18 09:19:06
 * @LastEditTime: 2023-09-04 23:05:40
 * @LastEditors: highlightfip 2793393724@qq.com
 * @Description: control S2 & 4X4keyboard
 * @FilePath: \stm32-boot\periph\snap.c
 */

#include "snap.h"
#include "delay.h"

static SNAP_INFO_T SNAP_INFO_GROUP[SNAPKB_GROUP_NUM] =
{
    {
        snap0,
        {
            exti1,
            exti2,
            exti3,
            exti4
        }
    }
};

static BSP_INFO_T VCC_44KB[4] =
{
    {
        PB1,
        GPIO_Mode_Out_PP
    },
    {
        PB2,
        GPIO_Mode_Out_PP
    },
    {
        PB10,
        GPIO_Mode_Out_PP
    },
    {
        PB11,
        GPIO_Mode_Out_PP
    }
};

static void open(void *handle, void *dev_obj);
static void close(void);

/**
 * @brief: int the operator
 * @param dev_obj_opr pointer of snap_opr
 * @retval: None
 */
extern void  snap_opr_init(void *dev_obj_opr)
{
    ((SNAP_OPR_T *)dev_obj_opr)->open = open;
    ((SNAP_OPR_T *)dev_obj_opr)->close = close;
}

/**
 * @brief: open the device
 * @param {SNAP_HANDLE_T} *handle
 * @param {void} *dev_obj select the exti device
 * @retval: None
 */
static uint8_t w, m;
SNAPKB_HANDLE_T *Snap_IPQ_Handle;
static void open(void *handle, void *dev_obj)
{
    SNAPKB_HANDLE_T *sh = (SNAPKB_HANDLE_T *)handle;

    exti_opr_init(&(sh->exti_handle[0].exti_opr));
    gpio_opr_init(&(sh->vcc_gh[0].gpio_opr));
    memcpy(&sh->snap_info, &SNAP_INFO_GROUP[(uint8_t)dev_obj], sizeof(SNAP_INFO_T));
    
    for (w = 0; w < 4; w++)
    {
        sh->exti_handle[0].exti_opr.open(&(sh->exti_handle[w]), SNAP_INFO_GROUP[(uint8_t)dev_obj].exti_x[w]);
        sh->vcc_gh[0].gpio_opr.open(&sh->vcc_gh[w], &(VCC_44KB[w]));
        sh->vcc_gh[0].gpio_opr.write(&sh->vcc_gh[w], (void *)0);
    }
    Snap_IPQ_Handle = sh;
}

/**
 * @brief: close the device
 */
static void close(void)
{
    EXTI_OPR_T exti_opr;
    exti_opr_init(&exti_opr);
    exti_opr.close();
}

static uint8_t detect_snapKB(EXTI_NAME_T extix)
{
    int8_t dat = 0xffff;
    uint8_t check_ptr = 4;      //species one of the snap<0-3> which then wound be the most possible one
    uint8_t C1_4 = 0;           //species the impossible snap<1>
    uint8_t result_state = 0;   //if C1_4 == 0 after one loop<w>, return 1 while means detected false
    DelayUs(200);
    
    for(m = 0; m < 2; m++)
    {
        for (w = 0; w < 4 && !(C1_4 & (1<<w)); w++)
        {
            //turn on Push-Pull
            Snap_IPQ_Handle->vcc_gh[0].gpio_opr.write(&(Snap_IPQ_Handle->vcc_gh[w]), (void *)1);    

            //recording
            Snap_IPQ_Handle->exti_handle[(uint16_t)extix-1].gpio_handle.gpio_opr.read(&(Snap_IPQ_Handle->exti_handle[(uint16_t)extix-1].gpio_handle), &dat);
            C1_4 |= ((!dat)<<w);
            check_ptr -= !dat;
            //restore
            Snap_IPQ_Handle->vcc_gh[0].gpio_opr.write(&(Snap_IPQ_Handle->vcc_gh[w]), (void *)0);
            if (!(check_ptr-1)) break;
            DelayUs(70);
#if PORT_OUTPUT_EXTI
bug_check_num(m+1,dat);
#endif
        }
        result_state = !(C1_4);
        if (!(check_ptr-1) || result_state) break;
    }
    if (!result_state)
    {
        check_ptr=0;
        m = 15;
        while(C1_4 != m)
        {
            C1_4 >>= 1;
            m >>= 1;
            check_ptr++;
        }
        DelayMs(21);
        return check_ptr-1;// +(((uint8_t)extix-1)<<2)
#if PORT_OUTPUT_EXTI
bug_check_num((uint16_t)extix, check_ptr);
#endif
    }
#if PORT_OUTPUT_EXTI
    else 
    {
bug_check_loc("detect snap FALSE!!");
    }
// bug_check_num((uint16_t)extix-1, check_ptr-1+(((uint16_t)extix-1)<<2));
bug_check_loc("-----------------------");
#endif
}

void EXTI1_IRQHandler(void)
{
	if(SET == EXTI_GetITStatus(EXTI_Line1))
	{
        SNAP1_IRQ(detect_snapKB(exti1));
    }
	EXTI_ClearITPendingBit(EXTI_Line1);
}

void EXTI2_IRQHandler(void)
{
    if(SET == EXTI_GetITStatus(EXTI_Line2))
    {
        SNAP2_IRQ(detect_snapKB(exti2));
    }
    EXTI_ClearITPendingBit(EXTI_Line2);
}

void EXTI3_IRQHandler(void)
{
    if(SET == EXTI_GetITStatus(EXTI_Line3))
    {
        SNAP3_IRQ(detect_snapKB(exti3));
    }
    EXTI_ClearITPendingBit(EXTI_Line3);
}

void EXTI4_IRQHandler(void)
{
    if(SET == EXTI_GetITStatus(EXTI_Line4))
    {
        SNAP4_IRQ(detect_snapKB(exti4));
    }
    EXTI_ClearITPendingBit(EXTI_Line4);
}

void EXTI15_10_IRQHandler(void)
{
	if(SET == EXTI_GetITStatus(EXTI_Line14))
	{
        detect_snapKB(exti2);
    }
	EXTI_ClearITPendingBit(EXTI_Line14);
}