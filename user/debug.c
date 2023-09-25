/**
 * debug log :(whose problem still remain)
 * 1. PA2 in exti_line2 can't work, currently use PA0 in exti_line0 as a substitute
 * 2. SNAP S5&S6&S7 always touch off other exti IQRHANDLER
 * 
 */

#include "debug.h"
#include "stdlib.h"

static PORT_HANDLE_T *prt_pter;

extern void DebugInit(PORT_HANDLE_T *ph)
{
    port_opr_init(&(ph->port_opr));
    ph->port_opr.open(ph, port1);
    prt_pter = ph;
}

extern void bug_check(void)
{
    prt_pter->port_opr.print(prt_pter, "[DEBUG LOG] : nothing worry here!\r\n");
}

extern void bug_check_num(uint16_t num, uint16_t real_num)
{
    prt_pter->port_opr.print(prt_pter, "[DEBUG LOG] : %d supposed to be %d\r\n", num, real_num);
}

extern void bug_check_loc(char *str)
{
    prt_pter->port_opr.print(prt_pter, "[DEBUG LOG] : %s\r\n", str);
}

