/**
 * debug log :(whose problem still remain)
 * 1. PA2 in exti_line2 can't work, currently use PC14 in exti_line14 as a substitute
 * 2. SNAP S5&S6&S7 always touch off other exti IQRHANDLER
 * 
 */

#include "debug.h"

extern void bug_check(void)
{
    PORT_HANDLE_T ph;
    port_opr_init(&(ph.port_opr));
    ph.port_opr.open(&ph, port1);
    ph.port_opr.print(&ph, "[DEBUG LOG] : nothing worry here!\r\n");
}

extern void bug_check_num(uint16_t num, uint16_t real_num)
{
    PORT_HANDLE_T ph;
    port_opr_init(&(ph.port_opr));
    ph.port_opr.open(&ph, port1);
    ph.port_opr.print(&ph, "[DEBUG LOG] : %d supposed to be %d\r\n", num, real_num);
}

extern void bug_check_loc(char *str)
{
    PORT_HANDLE_T ph;
    port_opr_init(&(ph.port_opr));
    ph.port_opr.open(&ph, port1);
    ph.port_opr.print(&ph, "[DEBUG LOG] : %s\r\n", str);
}

