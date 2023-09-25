/*
 * @Author       : highlight
 * @Date         : 2023-08-04 18:25:20
 * @LastEditTime: 2023-09-25 16:26:32
 * @LastEditors: highlightfip 2793393724@qq.com
 * @Description  : main program
 * @FilePath: \stm32-boot\user\main.c
 */

#include "led.h"
#include "delay.h"
#include "debug.h"
#include "display.h"
// #include "tim.h"
#include "stdlib.h"

static void delay(void)
{
	uint32_t temp = 0x3fffff;
	while(temp--);
}

int main()
{
	PORT_HANDLE_T ph;

#if 0
	DISPLAY_HANDLE_T dh;
	SNAPKB_HANDLE_T sh;
	
	DebugInit(&ph);
	DelayInit();

	display_opr_init(&dh.display_opr);
	dh.display_opr.init(&dh);
	dh.display_opr.start(&dh);

	// snap_opr_init(&(dh.snapkb_handle.snap_opr));
	// dh.snapkb_handle.snap_opr.open(&(dh.snapkb_handle), snapKB);

	// snap_opr_init(&sh.snap_opr);
	// sh.snap_opr.open(&sh, snapKB);
	while(1);
#endif

#if 1
	DISPLAY_HANDLE_T dh;
	// TIM_HANDLE_T th;

	DebugInit(&ph);
	DelayInit();

	//timer test
	// tim_opr_init(&th.tim_opr);
	// th.tim_opr.open(&th, tim1);

	//display on
	display_opr_init(&dh.display_opr);
	dh.display_opr.init(&dh);
	dh.display_opr.start(&dh);
	while(1);
#endif
}
