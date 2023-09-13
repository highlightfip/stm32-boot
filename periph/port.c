/*
 * @Author       : highlight
 * @Date         : 2023-08-07 20:48:07
 * @LastEditTime: 2023-08-30 07:47:14
 * @LastEditors: highlightfip 2793393724@qq.com
 * @Description  : port for interaction
 * @FilePath: \stm32-boot\periph\port.c
 */

#include "port.h"

static PORT_INFO_T PORT_INFO_GROUP[1] =
{
    {
        port1,
        usart1
    }
};

static void open(void *handle, void *dev_obj);
static int32_t stm32_print(void *handle, const char *frm , ...);
static void close(void *handle);
static uint16_t num_rev(int *num);

extern void port_opr_init(void *dev_obj_opr)
{
    ((PORT_OPR_T *)dev_obj_opr)->open  = open;
    ((PORT_OPR_T *)dev_obj_opr)->print = stm32_print;
    ((PORT_OPR_T *)dev_obj_opr)->close = close;
}

/**
 * @brief: device-->terminal {simlar to printf("...", &..)}
 * @param {void} *dev_obj
 * @param {char} *frm
 * @retval: Nonde
 */
static int32_t stm32_print(void *handle, const char *frm , ...)
{
    PORT_HANDLE_T *ph = (PORT_HANDLE_T *)handle;
    uint16_t i, len, cnt_num = 0;
    va_list arg;

#define PUTC(single_stuff) {\
    ph->usart_handle.usart_opr.write(&ph->usart_handle, (void *)((uint16_t)(single_stuff)));\
}

    va_start(arg, frm);
    for (i = 0; frm[i]; i++)
	{
        switch (frm[i])
		{
            case '%':
			{
                switch (frm[++i])
				{
                    case '%':
					{
						PUTC(frm[i]);
                        cnt_num++;
						break;
					}
                    case 'd': /*max = 2,147,483,648*/
					{
                        int digit = va_arg(arg, int32_t);
                        if (!digit) 
                        {
                            PUTC('0');
                            cnt_num++;
                            break;
                        }
                        if (digit < 0)
                        {
                            PUTC('-');
                            digit = -digit;
                        }
                        len = num_rev(&digit);
                        while (len--) {
                            PUTC(digit % 10 + '0');
                            digit /= 10;
                        }
                        cnt_num += len;
						break;
                    }
                    case 's':
					{
                        char *str = va_arg(arg, char *);
                        uint32_t i = 0;
                        while(str[i]) {
                            PUTC(str[i]);
                            i++;
                        }
                        cnt_num += i;
						break;
                    }
                    case 'c':
					{
                        char str = va_arg(arg, char);
    					PUTC(str);
                        ++cnt_num;
						break;
                    } 
                }
				break;
            }
            /*
			case '\\':
			{
				switch (frm[++i])
				{
					case '\\':
					{
						PUTC(frm[i]);
                        ++cnt_num;
						break;
					}
                    case 'n':
                    {
                        PUTC('\r');
                        break;
                    }
				}
			}*/
            default: 
			{
				PUTC(frm[i]);
                ++cnt_num;
				break;
			}
        }
    }
    va_end(arg);
    
#undef PUTC

    return cnt_num;
}


/**
 * @description: open the device
 * @param {PORT_HANDLE_T} *handle
 * @param {void} *dev_obj
 * @return Node
 */
static void open(void *handle, void *dev_obj)
{
    PORT_HANDLE_T *ph = (PORT_HANDLE_T *)handle;
    
    memcpy(&(ph->port_info), &PORT_INFO_GROUP+((uint32_t)dev_obj), sizeof(PORT_INFO_T));

    usart_opr_init(&ph->usart_handle.usart_opr);
    ph->usart_handle.usart_opr.open(&ph->usart_handle, &ph->port_info.usartx);
}

/**
 * @description: close the device
 * @param {PORT_HANDLE_T} *handle
 * @return Node
 */
static void close(void *handle)
{
    PORT_HANDLE_T *ph = (PORT_HANDLE_T *)handle;
    ph->usart_handle.usart_opr.close(&ph->usart_handle);

}

static uint16_t num_rev(int *num)
{
    int i = *num, j = 0;
    uint16_t k = 0;
    while(i)
    {
        j = j * 10 + i % 10;
        i /= 10;
        k++;
    }
    *num = j;
    return k;
}