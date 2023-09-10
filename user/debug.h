
#ifndef _DEBUG_H
#define _DEBUG_H

#include "port.h"
#include "delay.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_i2c.h"

extern void bug_check(void);
extern void bug_check_num(uint16_t num, uint16_t real_num);
extern void bug_check_loc(char *str);

#endif
