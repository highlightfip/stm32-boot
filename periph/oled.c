/*
 * @Author: highlightfip
 * @Date: 2023-08-19 09:59:44
 * @LastEditTime: 2023-09-24 21:53:45
 * @LastEditors: highlightfip 2793393724@qq.com
 * @Description: oled opr
 * @FilePath: \stm32-boot\periph\oled.c
 */

#include "oled.h"
#include "oledmap.h"
#include "debug.h"
#include "stdlib.h"

extern OLED_PRINT_T OLED_PRINT_GROUP[4] =
{
    {
        OLED_PRINT_CH,
        {
            "hello world!",
            FONT_DEFAULT,
            0,
            24,
        }
    },
    {
        OLED_PRINT_BMP,
        {
            "0",
            BMP_EX,
            0,
            0,
            128,
            64
        }
    },
    {
        OLED_PRINT_CLEAR,
        {
            "0",NULL,
            0,0,128,64
        }
    },
    {
        OLED_PRINT_FILL,
        {
            "0",NULL,
            0,0,128,64
        }
    }
};

static void open(void *handle, void *dev_obj);
static int8_t print(void *handle, void *data);
static uint8_t LocateDateptr(const uint8_t *data, uint8_t *font_width, uint8_t *font_offset, uint8_t *font_height);
static const uint8_t *LocateDateptr1(uint8_t *data);

/**
 * @brief: int the operator
 * @param {GPIO_OPR_T} *dev_obj_opr
 * @retval: None
 */
void oled_opr_init(void *dev_obj_opr)
{
    ((OLED_OPR_T *)dev_obj_opr)->open = open;
    ((OLED_OPR_T *)dev_obj_opr)->print = print;
}

void open(void *handle, void *dev_obj)
{
    int16_t i;
    OLED_HANDLE_T *oh = (OLED_HANDLE_T *)handle;

    i2c_opr_init(&oh->i2c_handle.i2c_opr);
    oh->i2c_handle.i2c_opr.open(&oh->i2c_handle, dev_obj);

    for(i = 0; i < OLED_INITCMD_LEN; i++)
    {
        oh->i2c_handle.i2c_opr.write(&(oh->i2c_handle), I2C_ADDR_CMD, Oled_InitCmd[i]);
    }
}

static void OLED_SetPos(OLED_HANDLE_T *oh, uint16_t x, uint16_t y)
{
    oh->i2c_handle.i2c_opr.write(&oh->i2c_handle, I2C_ADDR_CMD, 0xb0+y);
    oh->i2c_handle.i2c_opr.write(&oh->i2c_handle, I2C_ADDR_CMD, ((x&0xf0)>>4)|0x10);
    oh->i2c_handle.i2c_opr.write(&oh->i2c_handle, I2C_ADDR_CMD, (x&0x0f)|0x01);
}

/**
 * @brief: oled printf
 * @param {void} *handle
 * @param {void} *data
 * @retval: 
 */
int8_t print(void *handle, void *data)
{
    uint8_t font, y_offset;
    uint8_t m = 0, n, i, j, k;
    uint32_t o = 0;
    OLED_HANDLE_T *oh = (OLED_HANDLE_T *)handle;
    OLED_PRINT_T *op = (OLED_PRINT_T *)data;

    switch(op->mode)
    {
        case OLED_PRINT_CLEAR :
        {
            i = op->data.x1 - op->data.x;
            for(m = op->data.y/8; m < op->data.y1/8; m++)
            {
                OLED_SetPos(oh, op->data.x, m);
                for(n = 0; n < i; n++)
				    oh->i2c_handle.i2c_opr.write(&oh->i2c_handle, I2C_ADDR_DATA, 0x00);
				// oh->i2c_handle.i2c_opr.write(&oh->i2c_handle, I2C_ADDR_CMD, 0xb0+m);//page0-page1
				// oh->i2c_handle.i2c_opr.write(&oh->i2c_handle, I2C_ADDR_CMD, 0x00);//low column start address
				// oh->i2c_handle.i2c_opr.write(&oh->i2c_handle, I2C_ADDR_CMD, 0x10);//high column start address
                // for(n = 0; n < 128; n++)
				//     oh->i2c_handle.i2c_opr.write(&oh->i2c_handle, I2C_ADDR_DATA, 0x00);
	        }
            break;
        }
        case OLED_PRINT_FILL :
        {
            for(m = 0; m < 8; m++)
            {
				oh->i2c_handle.i2c_opr.write(&oh->i2c_handle, I2C_ADDR_CMD, 0xb0+m);//page0-page1
				oh->i2c_handle.i2c_opr.write(&oh->i2c_handle, I2C_ADDR_CMD, 0x00);//low column start address
				oh->i2c_handle.i2c_opr.write(&oh->i2c_handle, I2C_ADDR_CMD, 0x10);//high column start address
                for(n = 0; n < 128; n++)
				    oh->i2c_handle.i2c_opr.write(&oh->i2c_handle, I2C_ADDR_DATA, 0xFF);
	        }
            break;
        }
        case OLED_PRINT_CH :
        {
            o = op->data.x;
            font = LocateDateptr(op->data.data_ptr1, &i, &j, &k);
            y_offset = op->data.y&7;

            while(op->data.data_ptr[m] != '\0')
			{
				if(op->data.x > 127)
				{
					op->data.x = 0;
					op->data.y += k;
				}
                switch(font)
                {
                    case 1://F6x8
                    {
                        OLED_SetPos(oh, op->data.x, op->data.y/8);
                        for(n = 0; n < i; n++)
                            oh->i2c_handle.i2c_opr.write(&oh->i2c_handle, I2C_ADDR_DATA, (F6x8[op->data.data_ptr[m] - j][n])<<y_offset);
                        
                        if(!IS_DATA_SPILL(k-1, y_offset)) break;
                        OLED_SetPos(oh, op->data.x, op->data.y/8+1);
                        for(n = 0; n < i; n++)
                            oh->i2c_handle.i2c_opr.write(&oh->i2c_handle, I2C_ADDR_DATA, (F6x8[op->data.data_ptr[m] - j][n])>>(8-y_offset));
                        break;
                    }
                    case 2://F16x24
                    {
				        OLED_SetPos(oh, op->data.x, op->data.y/8);
                        for(n = 0; n < i; n++)
                            oh->i2c_handle.i2c_opr.write(&oh->i2c_handle, I2C_ADDR_DATA, (F16x24[op->data.data_ptr[m] - j][n])<<y_offset);
				        OLED_SetPos(oh, op->data.x, op->data.y/8+1);
                        for(n = 0; n < i; n++)
                            oh->i2c_handle.i2c_opr.write(&oh->i2c_handle, I2C_ADDR_DATA, ((F16x24[op->data.data_ptr[m] - j][n + 16])<<y_offset)|((F16x24[op->data.data_ptr[m] - j][n])>>(8-y_offset)));
				        OLED_SetPos(oh, op->data.x, op->data.y/8+2);
                        for(n = 0; n < i; n++)
                            oh->i2c_handle.i2c_opr.write(&oh->i2c_handle, I2C_ADDR_DATA, ((F16x24[op->data.data_ptr[m] - j][n + 32])<<y_offset)|((F16x24[op->data.data_ptr[m] - j][n + 16])>>(8-y_offset)));
				        
                        if(!IS_DATA_SPILL(k-1, y_offset)) break;
                        OLED_SetPos(oh, op->data.x, op->data.y/8+3);
                        for(n = 0; n < i; n++)
                            oh->i2c_handle.i2c_opr.write(&oh->i2c_handle, I2C_ADDR_DATA, ((F16x24[op->data.data_ptr[m] - j][n + 32])>>(8-y_offset)));
                        
                        break;
                    }
                    case 3://F4x6
                    {
				        OLED_SetPos(oh, op->data.x, op->data.y/8);
                        for(n = 0; n < i; n++)
                            oh->i2c_handle.i2c_opr.write(&oh->i2c_handle, I2C_ADDR_DATA, (F4x6[op->data.data_ptr[m] - j][n])<<y_offset);
				        
                        if(!IS_DATA_SPILL(k-1, y_offset)) break;
                        OLED_SetPos(oh, op->data.x, op->data.y/8+1);
                        for(n = 0; n < i; n++)
                            oh->i2c_handle.i2c_opr.write(&oh->i2c_handle, I2C_ADDR_DATA, (F4x6[op->data.data_ptr[m] - j][n])>>(8-y_offset));
                        break;
                    }
                }
				op->data.x += i;
				m++;
			}
            op->data.x = o;
            break;
        }
        case OLED_PRINT_BMP:
        {
            y_offset = op->data.y&7;
            op->data.data_ptr1 = LocateDateptr1(op->data.data_ptr);

            
            i = op->data.x1 - op->data.x;
            j = op->data.y1 - op->data.y; //y_entit==entity_height
            m = op->data.y/8;
            y_offset = op->data.y&7;

            OLED_SetPos(oh, op->data.x,m);
            for(n = op->data.x; n < op->data.x1; n++)
            {
                oh->i2c_handle.i2c_opr.write(&oh->i2c_handle, I2C_ADDR_DATA, ((op->data.data_ptr1[o])<<y_offset));
                ++o;
            }

            if(((j+y_offset+7)>>3) == 1) break;
            for(m = op->data.y/8+1; m < (op->data.y1+7)/8-1; m++)
            {
                OLED_SetPos(oh, op->data.x,m);
                for(n = op->data.x; n < op->data.x1; n++)
                {
                    oh->i2c_handle.i2c_opr.write(&oh->i2c_handle, I2C_ADDR_DATA, ((op->data.data_ptr1[o])<<y_offset) | ((op->data.data_ptr1[o-i])>>(8-y_offset)));
                    ++o;
                }
            }
                
            m = op->data.y1/8;
            if(!IS_DATA_SPILL(j, y_offset) || m>7) break;
            OLED_SetPos(oh, op->data.x,m);
            for(n = op->data.x; n < op->data.x1; n++)
            {
                oh->i2c_handle.i2c_opr.write(&oh->i2c_handle, I2C_ADDR_DATA, ((op->data.data_ptr1[(o)-i])>>(8-y_offset)));
                ++o;
            }
            
            break;
        }
        default:
            break;
    }
#undef OLED_SetPos
}

/**
 * @brief: locate font address by data_ptr1
 * @param {uint8_t} *data
 * @retval: font address
 */
static uint8_t LocateDateptr(const uint8_t *data, uint8_t *font_width, uint8_t *font_offset, uint8_t*font_heigth)
{
    switch((uint8_t)data)
    {
        case 0: 
            *font_offset = 32;
            *font_width  = 6;
            *font_heigth = 8;
            return 1; //F6x8;
        case 1: 
            *font_offset = 48;
            *font_width  = 16;
            *font_heigth = 24;
            return 2; //F16x24;
        case 2:
            *font_offset = 48;
            *font_width  = 4;
            *font_heigth = 6;
            return 3; //F4x6
    }
}

/**
 * @brief: locate BMP address by data_ptr
 * @param {uint8_t} *data
 * @retval: BMP address
 */
static const uint8_t *LocateDateptr1(uint8_t *data)
{
    switch(data[0])
    {
        case '0': return BMP_EX;
        case '1': return BS_8bit_left;
        case '2': return BS_8bit_right;
        case '3': return health;
        case '4': return spaceship;
        default: bug_check_loc("loading false"); return NULL;
    }
}