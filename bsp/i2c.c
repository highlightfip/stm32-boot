/*
 * @Author       : highlight
 * @Date         : 2023-08-08 19:47:28
 * @LastEditTime: 2023-09-24 21:45:10
 * @LastEditors: highlightfip 2793393724@qq.com
 * @Description  : i2c opr
 * @FilePath: \stm32-boot\bsp\i2c.c
 */

#include "i2c.h"
#include "debug.h"

static I2C_INFO_T I2C_INFO_GROUP[1] =
{
	{
		{
			{/*SCL*/
				PB6,
				GPIO_Mode_AF_OD
			},
			{/*SDA*/
				PB7,
				GPIO_Mode_AF_OD
			}
		},
		RCC_APB1Periph_I2C1,
		I2C1,
		{
			400000,
			I2C_Mode_I2C,
			I2C_DutyCycle_2,
			0x30,
			I2C_Ack_Enable,
			I2C_AcknowledgedAddress_7bit
		}
	}
};

static void open(void *handle, void *dev_obj);
static void write(void *handle, uint8_t addr, uint8_t data);

/**
 * @brief: int the operator
 * @param {GPIO_OPR_T} *dev_obj_opr
 * @retval: None
 */
extern void i2c_opr_init(void *dev_obj_opr)
{
    ((I2C_OPR_T *)dev_obj_opr)->open = open;
    ((I2C_OPR_T *)dev_obj_opr)->write = write;
}

static void open(void *handle, void *dev_obj)
{
    I2C_HANDLE_T *ih = (I2C_HANDLE_T *)handle;

	memcpy(&(ih->i2c_info), &I2C_INFO_GROUP+((uint32_t)dev_obj), sizeof(I2C_INFO_T));

	RCC_APB1PeriphClockCmd(ih->i2c_info.rcc_clock,ENABLE);

	gpio_opr_init(&(ih->gpio_handle.gpio_opr));
	ih->gpio_handle.gpio_opr.open(&(ih->gpio_handle), &(ih->i2c_info.bsp_info[0]));
	ih->gpio_handle.gpio_opr.open(&(ih->gpio_handle), &(ih->i2c_info.bsp_info[1]));

	I2C_Cmd(ih->i2c_info.i2cx, ENABLE);
	I2C_Init(ih->i2c_info.i2cx, &(ih->i2c_info.i2c_arg));
}

static void write(void *handle, uint8_t addr, uint8_t data)
{
    I2C_HANDLE_T *ih = (I2C_HANDLE_T *)handle;

    while(I2C_GetFlagStatus(ih->i2c_info.i2cx, I2C_FLAG_BUSY));
	
	I2C_GenerateSTART(ih->i2c_info.i2cx, ENABLE);//开启I2C1
	while(!I2C_CheckEvent(ih->i2c_info.i2cx, I2C_EVENT_MASTER_MODE_SELECT));/*EV5,主模式*/

	I2C_Send7bitAddress(ih->i2c_info.i2cx, 0x78, I2C_Direction_Transmitter);//器件地址 -- 默认0x78
	while(!I2C_CheckEvent(ih->i2c_info.i2cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	I2C_SendData(ih->i2c_info.i2cx, addr);//寄存器地址
	while (!I2C_CheckEvent(ih->i2c_info.i2cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_SendData(ih->i2c_info.i2cx, data);//发送数据
	while (!I2C_CheckEvent(ih->i2c_info.i2cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
	I2C_GenerateSTOP(ih->i2c_info.i2cx, ENABLE);//关闭I2C1总线

}
