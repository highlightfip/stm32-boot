/*
 * @Author: highlightfip
 * @Date: 2023-08-18 09:19:06
 * @LastEditTime: 2023-09-25 07:59:03
 * @LastEditors: highlightfip 2793393724@qq.com
 * @Description: control S2 & 4X4keyboard
 * @FilePath: \stm32-boot\periph\snap.c
 */

#include "snap.h"
#include "delay.h"

const static SNAP_INFO_T SNAP_INFO_GROUP[SNAPKB_GROUP_NUM] =
{
    {
        snapKB,
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

SNAPKB_HANDLE_T *Snap_IPQ_Handle;
static SNAPKB_FEEDBACK_T exti_receiver;

static void open(void *handle, void *dev_obj);
static int8_t read(void *handle, void *data);
static void close(void *handle);

/**
 * @brief: int the operator
 * @param dev_obj_opr pointer of snap_opr
 * @retval: None
 */
extern void  snap_opr_init(void *dev_obj_opr)
{
    ((SNAP_OPR_T *)dev_obj_opr)->open = open;
    ((SNAP_OPR_T *)dev_obj_opr)->read = read;
    ((SNAP_OPR_T *)dev_obj_opr)->close = close;
}

/**
 * @brief: open the device
 * @param {SNAPKB_HANDLE_T} *handle
 * @param {void} *dev_obj select the exti device
 * @retval: None
 */
static void open(void *handle, void *dev_obj)
{
    uint8_t w;
    SNAPKB_HANDLE_T *sh = (SNAPKB_HANDLE_T *)handle;
bug_check_loc("snap.open");
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

    memset(&exti_receiver, 0, sizeof(SNAPKB_FEEDBACK_T));

}

/**
 * @brief: 
 * @param {SNAPKB_HANDLE_T} *handle
 * @param {SNAPKB_FEEDBACK_T} *data 
 * @retval: 
 */
static int8_t read(void *handle, void *data)
{
    int8_t result_state = 0;
    SNAPKB_HANDLE_T *sh = (SNAPKB_HANDLE_T *)handle;
    SNAPKB_FEEDBACK_T *receive_data = (SNAPKB_FEEDBACK_T *)data;

    //copy the receive data
    *receive_data = exti_receiver;

    //reset receiver
    memset(&exti_receiver, 0, sizeof(SNAPKB_FEEDBACK_T));

    return result_state;
}

/**
 * @brief: close the device
 */
static void close(void *handle)
{
    SNAPKB_HANDLE_T *sh = (SNAPKB_HANDLE_T *)handle;
    sh->exti_handle[0].exti_opr.close();
}

static uint8_t detect_snapKB(EXTI_NAME_T extix)
{
    uint16_t i, w, m;
    int8_t dat = 0xffff;
    uint8_t check_ptr = 4;      //species one of the snap<0-3> which then wound be the most possible one
    uint8_t C1_4 = 0;           //species the impossible snap<1> which was snapped
    uint8_t result_state = 0;   //if C1_4 == 0 after one loop<w>, return 1 which means detected false
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
        // DelayMs(14);
        exti_receiver.act_record[(((uint8_t)extix)<<2)+check_ptr-5] += 1;
        exti_receiver.snapkb_state |= 1;
        for(i = 0; i < 17; i++) {
            if(i==16) bug_check_loc("add false");
            else if(exti_receiver.act_record[i]) 
            {
                bug_check_num(i,i);
                break;
            }
        }
#if PORT_OUTPUT_EXTI
        bug_check_num((uint16_t)extix, check_ptr);
        bug_check_num((((uint8_t)extix)<<2)+check_ptr-5, 0xf);
        bug_check_loc("-----------------------");
#endif
        return check_ptr-1;// +(((uint8_t)extix-1)<<2)
    }
#if PORT_OUTPUT_EXTI
    else 
    {
        bug_check_loc("----detect snap FALSE!!----");
    }
#endif
}

void EXTI0_IRQHandler(void)
{
	if(SET == EXTI_GetITStatus(EXTI_Line0))
	{
        detect_snapKB(exti2);
    }
	EXTI_ClearITPendingBit(EXTI_Line0);
    
}

void EXTI1_IRQHandler(void)
{
	if(SET == EXTI_GetITStatus(EXTI_Line1))
	{
        detect_snapKB(exti1);
    }
	EXTI_ClearITPendingBit(EXTI_Line1);
    
}

void EXTI2_IRQHandler(void)
{
    if(SET == EXTI_GetITStatus(EXTI_Line2))
    {
        detect_snapKB(exti2);
    }
    EXTI_ClearITPendingBit(EXTI_Line2);
}

void EXTI3_IRQHandler(void)
{
    if(SET == EXTI_GetITStatus(EXTI_Line3))
    {
        detect_snapKB(exti3);
    }
    EXTI_ClearITPendingBit(EXTI_Line3);
}

void EXTI4_IRQHandler(void)
{
    if(SET == EXTI_GetITStatus(EXTI_Line4))
    {
        detect_snapKB(exti4);
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