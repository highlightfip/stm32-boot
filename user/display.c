/*
 * @Author: highlightfip
 * @Date: 2023-08-21 17:40:13
 * @LastEditTime: 2023-09-05 21:04:17
 * @LastEditors: highlightfip 2793393724@qq.com
 * @Description: display operation interface
 * @FilePath: \stm32-boot\user\display.c
 */

#include "display.h"

static void *display_handleptr;
static void opr_MainFunc(void *handle);
static void opr_SubFunc_timer(void *handle);
static void opr_SubFunc_BS8bit(void *handle);
static void opr_SubFunc_SpaceImpact(void *handle);
static void Display_Init(void *handle);
static void Display_Start(void *handle);
static void Display_End(void *handle);

/**
 * @brief: record the first appearance of operate interface
 */
static OPRINF_HANDLE_T interface_GROUP[INF_GROUP_NUM] =
{
    {
        NULL,
        opr_SubFunc_timer,
        0,5,
        {
#define TIMER_FONT_TYPE   FONT_DEFAULT
#define TIMER_FONT_WIDTH  6
#define TIMER_FONT_YLOC   28
            {
                OLED_PRINT_CH,
                {"00",TIMER_FONT_TYPE,0*TIMER_FONT_WIDTH,TIMER_FONT_YLOC,} //id:0x2
            },
            {
                OLED_PRINT_CH,
                {":", TIMER_FONT_TYPE,2*TIMER_FONT_WIDTH,TIMER_FONT_YLOC,} //id:0x2<<2
            },
            {
                OLED_PRINT_CH,
                {"00",TIMER_FONT_TYPE,3*TIMER_FONT_WIDTH,TIMER_FONT_YLOC,} //id:0x2<<4
            },
            {
                OLED_PRINT_CH,
                {":", TIMER_FONT_TYPE,5*TIMER_FONT_WIDTH,TIMER_FONT_YLOC,} //id:0x2<<6
            },
            {
                OLED_PRINT_CH,
                {"00",TIMER_FONT_TYPE,6*TIMER_FONT_WIDTH,TIMER_FONT_YLOC,} //id:0x3<<8
            },
        },
        (((0x2)+(0x2<<2)+(0x2<<4)+(0x2<<6)+(0x3<<8))<<4)+0x0,
        NULL
    },
    {
        NULL,
        opr_SubFunc_BS8bit,
        0,2,
        {
            {
                OLED_PRINT_BMP,
                {
                    "1",NULL,
                    0,4,64,68
                }
            },
            {
                OLED_PRINT_BMP,
                {
                    "2",NULL,
                    64,4,128,68
                }
            }
        },
        (((0x2)+(0x2<<2))<<4)+0x1,
        NULL
    },
    {
        NULL,
        opr_SubFunc_SpaceImpact,
        0, 4,
        {
            {
                OLED_PRINT_BMP,
                {
                    "3",NULL,//health
                    0,4,6,8
                }
            },
            {
                OLED_PRINT_CH,
                {
                    "114514",FONT_DEFAULT,//score
                    80,0
                }
            },
            {
                OLED_PRINT_CLEAR,
                {
                    "custom",NULL,
                    0,8,128,64
                }
            },
            {
                OLED_PRINT_BMP,
                {
                    "4",NULL,//spaceship
                    0,57,12,64
                }
            }
        },
        ((0x2+(0x2<<2)+(0x00<<4)+(0x02<<6))<<4)+0x2,
        NULL
    }
};

static OPERATE_INFO_Timer Oprate_Info_Timer =
{
    0,0,0
};

static OPERATE_INFO_SpaceImpact Oprate_Info_Space =
{
    {
        0,57,0,0,NULL
    },
    0,
    1
};

/**
 * @brief: int the operator
 * @param {DISPLAY_OPR_T} *dev_obj_opr
 * @retval: None
 */
extern void display_opr_init(void *dev_obj_opr)
{
    ((DISPLAY_OPR_T *)dev_obj_opr)->init = Display_Init;
    ((DISPLAY_OPR_T *)dev_obj_opr)->start = Display_Start;
    ((DISPLAY_OPR_T *)dev_obj_opr)->end = Display_End;
}

/**
 * @brief: init display setting
 * @param {DISPLAY_HANDLE_T} *handle
 * @retval: None
 */
static void Display_Init(void *handle)
{
    int8_t temp = 0;
    void *last_func_ptr;
    DISPLAY_HANDLE_T *disp_handle = (DISPLAY_HANDLE_T *)handle;
    

    disp_handle->opr_MainFunc = opr_MainFunc;
    disp_handle->interface_index = &disp_handle->interface[INF_FIRST_INDEX];
    //snap keyboard init
    snap_opr_init(&disp_handle->snapkb_handle.snap_opr);
    disp_handle->snapkb_handle.snap_opr.open(&disp_handle->snapkb_handle, snap0);

    //oled init
    oled_opr_init(&disp_handle->oled_handle.oled_opr);
    disp_handle->oled_handle.oled_opr.open(&disp_handle->oled_handle, oled1);
    disp_handle->oled_handle.oled_opr.print(&disp_handle->oled_handle, CLEAR_OLED);

    //operate interface init&define memory place
    temp = INF_GROUP_NUM;
    last_func_ptr = &(disp_handle->interface[0]);
    while(temp)
    {
        --temp;
        disp_handle->interface[temp] = interface_GROUP[temp];
        disp_handle->interface[temp].next_inf = last_func_ptr;
        last_func_ptr = &(disp_handle->interface[temp]);
    }
    //operate memory section load
    disp_handle->display_info.timer = Oprate_Info_Timer;
    disp_handle->display_info.space_impact = Oprate_Info_Space;

    //operate info load
    disp_handle->interface[0].opr_info = &(disp_handle->display_info.timer);
    disp_handle->interface[2].opr_info = &(disp_handle->display_info.space_impact);
bug_check_num(disp_handle->display_info.space_impact.health, 1);
}

static void delay(void)
{
	uint32_t temp = 0x1fffff;
	while(temp--);
}

/**
 * @brief: start the display loop
 * @param  handle {DISPLAY_HANDLE_T *}ptr
 * @retval: None
 */
static void Display_Start(void *handle)
{
    uint8_t cnt = 0, temp = 0;
    DISPLAY_HANDLE_T *disp_handle = (DISPLAY_HANDLE_T *)handle;

    while(1)
    {
        for (temp = 0; temp < disp_handle->interface_index->element_endnum; temp++)
        {
            if(!IS_OPRINF_CHANGE_NOW(disp_handle->interface_index->oprinf_id, temp)) continue;
            disp_handle->oled_handle.oled_opr.print(&disp_handle->oled_handle, &disp_handle->interface_index->display_info[temp]);
            ID_FLAT_CLEAR(disp_handle->interface_index->oprinf_id, temp);
            bug_check_loc("DISPLAY REFRESH");
        }
        //disp_handle->opr_MainFunc(disp_handle);
        disp_handle->interface_index->opr_SubFunc(disp_handle->interface_index);

    }
}

static void Display_End(void *handle)
{
    
}

static void opr_MainFunc(void *handle)
{
    DISPLAY_HANDLE_T *disp_handle = (DISPLAY_HANDLE_T *)handle;


}

static void opr_SubFunc_timer(void *handle)
{
    OPRINF_HANDLE_T *oh = (OPRINF_HANDLE_T *)handle;
    OPERATE_INFO_Timer *dev_obj = (OPERATE_INFO_Timer *)(oh->opr_info);

    //time counter 
    delay();

    //refresh data
#define TIME_PER_T 60
    dev_obj->Time_Second++;
    dev_obj->Time_Minute += dev_obj->Time_Second/TIME_PER_T;
    dev_obj->Time_Second %= TIME_PER_T;
    dev_obj->Time_Hour   += dev_obj->Time_Minute/TIME_PER_T;
    dev_obj->Time_Minute %= TIME_PER_T;
#undef TIME_PER_T

    //display info update
    oh->display_info[0].data.data_ptr[0] = dev_obj->Time_Hour/10 + '0';
    oh->display_info[0].data.data_ptr[1] = dev_obj->Time_Hour%10 + '0';

    oh->display_info[2].data.data_ptr[0] = dev_obj->Time_Minute/10 + '0';
    oh->display_info[2].data.data_ptr[1] = dev_obj->Time_Minute%10 + '0';

    oh->display_info[4].data.data_ptr[0] = dev_obj->Time_Second/10 + '0';
    oh->display_info[4].data.data_ptr[1] = dev_obj->Time_Second%10 + '0';
    
    //oprinf_id update
    ID_FLAT_UPDATE(oh->oprinf_id, 0, (!(dev_obj->Time_Second))&&(!(dev_obj->Time_Minute)))
    ID_FLAT_UPDATE(oh->oprinf_id, 2,  !(dev_obj->Time_Second))
}

static void opr_SubFunc_BS8bit(void *handle)
{
    OPRINF_HANDLE_T *oh = (OPRINF_HANDLE_T *)handle;

}
static OPERATE_INFO_SpaceImpact *SI_info;
static void opr_SubFunc_SpaceImpact(void *handle)
{
    OPRINF_HANDLE_T *oh = (OPRINF_HANDLE_T *)handle;
    OPERATE_INFO_SpaceImpact *dev_obj = (OPERATE_INFO_SpaceImpact *)(oh->opr_info);

    //oprinf_id update
    ID_FLAT_UPDATE(oh->oprinf_id, 3, !(oh->display_info[2].data.x==dev_obj->spaceship.position_x))
    ID_FLAT_UPDATE(oh->oprinf_id, 2, (IS_OPRINF_CHANGE_NOW(oh->oprinf_id, 3)));

    //display info update
    oh->display_info[2].data.x = dev_obj->spaceship.position_x;
    oh->display_info[2].data.x1 = dev_obj->spaceship.position_x + 12;
    oh->display_info[2].data.y = dev_obj->spaceship.position_y;
    SI_info = dev_obj;
}


void SNAP1_IRQ(uint8_t index)
{
    switch(index)
    {
        case 1 : SI_info->spaceship.position_x += 3; break;
        case 2 : break;
        case 3 : break;
        case 4 : break;
        default: break;
    }
}

void SNAP2_IRQ(uint8_t index)
{
    switch(index)
    {
        case 1 : SI_info->spaceship.position_x -= 3; break;
        case 2 : break;
        case 3 : break;
        case 4 : break;
        default: break;
    }
}

void SNAP3_IRQ(uint8_t index)
{
    switch(index)
    {
        case 1 : SI_info->spaceship.position_x -= 3; break;
        case 2 : break;
        case 3 : break;
        case 4 : break;
        default: break;
    }
}

void SNAP4_IRQ(uint8_t index)
{
    switch(index)
    {
        case 1 : SI_info->spaceship.position_x -= 3; break;
        case 2 : break;
        case 3 : break;
        case 4 : break;
        default: break;
    }
}