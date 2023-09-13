/*
 * @Author: highlightfip
 * @Date: 2023-08-21 17:41:19
 * @LastEditTime: 2023-09-13 22:17:34
 * @LastEditors: 2793393724@qq.com 2793393724@qq.com
 * @Description: display operation interface
 * @FilePath: \stm32-boot\user\display.h
 */

#ifndef _OPR_INF_H
#define _OPR_INF_H

#include "oled.h"
#include "snap.h"

/*** 
 * @brief: display operater structure definition
 */
typedef struct
{
    void (*init)(void *handle);
    void (*start)(void *handle);
    void (*end)(void *handle);
} DISPLAY_OPR_T;

#define OPERATE_NEXT_T  void *          //point to the next interface
#define OPERATE_INFO_T  void *          //point to info memory section
#define OPERATE_FUNC_T  void 
#define MAX_ELEMENT_NUM 6

/**
 * @brief: use oprinf_id as index, only refresh oled when it need to
 */
#define IS_OPRINF_CHANGE_ALWAYS(index, element)   !!(index&(1<<(2*element+4)))
#define IS_OPRINF_CHANGE_NOW(index, element)      !!(index&(1<<(2*element+5)))
#define ID_FLAT_UPDATE(index, element, dat)       index |= ((!!(dat))<<(2*element+5)); // dat: 1, active
#define ID_FLAT_CLEAR(index, element)             index &= (~(!(IS_OPRINF_CHANGE_ALWAYS(index, element))<<(2*element+5))); //if it always change, this is in vain

/**
 * @brief: operate interface SUB-structure
 */
typedef struct
{
    //display memory&method
    OPERATE_INFO_T      opr_info;
    OPERATE_FUNC_T      (*opr_SubFunc)(void *handle);   //function react witch SNAPKB commed
    //display content
    uint16_t            element_startnum;
    uint16_t            element_endnum;
    OLED_PRINT_T        display_info[MAX_ELEMENT_NUM];
    uint32_t            oprinf_id;                         //0-3: distinguish every oprinf; 4-: highlight info about display change
    OPERATE_NEXT_T      next_inf;                       //point to the next interface in chain
} OPRINF_HANDLE_T;

/**
 * @brief: interface total number fastly control
 *      INF_GROUP_NUM   : 1~8
 *      INF_FIRST_INDEX : 0~(INF_GROUP_NUM-1)
 */
#define INF_GROUP_NUM   3
#define INF_FIRST_INDEX 2

typedef struct
{
    uint16_t             Time_Hour;
    uint16_t             Time_Minute;
    uint16_t             Time_Second;
} TIME_INFO_T;

/**
 * @brief: Timer info structure
 */
typedef struct
{
    TIME_INFO_T          cur_time;
    uint16_t             Is_Timerpause;
    TIME_INFO_T          rec_time[3];
} OPERATE_INFO_Timer;

/**
 * @brief: game info structure
 */
typedef struct 
{
    uint16_t             position_x;
    uint16_t             position_y;
    uint16_t             velocity_x;
    uint16_t             velocity_y;
    void *               moving_logic;
} SI_ANIMAL_T;

typedef struct
{
    SI_ANIMAL_T          spaceship;
    uint16_t             score;
    uint16_t             health;
    //uint16_t             bullet_num;
} OPERATE_INFO_SpaceImpact;

/**
 * @brief: value need to keep oprinf run in order
 */
typedef struct
{
    OPERATE_INFO_Timer timer;
    OPERATE_INFO_SpaceImpact space_impact;
} DISPLAY_INFO_T;

/**
 * @brief: display MAIN-structure
 */
typedef struct
{
    SNAPKB_HANDLE_T     snapkb_handle;
    OLED_HANDLE_T       oled_handle;
    OPRINF_HANDLE_T     interface[INF_GROUP_NUM];
    OPRINF_HANDLE_T*    interface_index;
    DISPLAY_OPR_T       display_opr;
    DISPLAY_INFO_T      display_info;
    OPERATE_FUNC_T      (*opr_MainFunc)(void *handle);
} DISPLAY_HANDLE_T;

extern void display_opr_init(void *dev_obj_opr);

#endif
