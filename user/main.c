/*
 * @Author       : highlight
 * @Date         : 2023-08-04 18:25:20
 * @LastEditTime: 2023-08-27 11:21:07
 * @LastEditors: highlightfip 2793393724@qq.com
 * @Description  : main program
 * @FilePath: \stm32-boot\user\main.c
 */

#include "led.h"
#include "delay.h"
#include "debug.h"
#include "display.h"

static void delay(void)
{
	uint32_t temp = 0x3fffff;
	while(temp--);
}

int main()
{
	DISPLAY_HANDLE_T dh;

	DelayInit();

	display_opr_init(&dh.display_opr);
	dh.display_opr.init(&dh);
	dh.display_opr.start(&dh);
#if 0
	// LED_HANDLE_T lh1;
	// PORT_HANDLE_T ph1;
	OLED_HANDLE_T oh;
	OLED_PRINT_T op;
	SNAPKB_HANDLE_T sh;

	DelayInit();
	// led_opr_init(&lh1.led_opr);
	// lh1.led_opr.open(&lh1, led1);
	// lh1.led_opr.write(&lh1, ON);
	// lh1.led_opr.write(&lh1, OFF);

	oled_opr_init(&oh.oled_opr);
	oh.oled_opr.open(&oh, oled1);

	snap_opr_init(&(sh.snap_opr));
	sh.snap_opr.open(&sh, snapKB);

	
	// ph1.port_opr.print(&ph1, "hello world!\r\n");
	while (1)
	{
		delay();
bug_check_loc("loop in");

		op.mode = OLED_PRINT_FILL;
		oh.oled_opr.print(&oh, &op);
		DelayMs(700);
		
		op.mode = OLED_PRINT_CLEAR;
		oh.oled_opr.print(&oh, &op);
		DelayMs(700);

		oh.oled_opr.print(&oh, &OLED_PRINT_GROUP[0]);
		DelayMs(700);
		
		op.mode = OLED_PRINT_CLEAR;
		oh.oled_opr.print(&oh, &op);
		oh.oled_opr.print(&oh, &OLED_PRINT_GROUP[1]);
		DelayMs(700);
		
	}
#endif
}
