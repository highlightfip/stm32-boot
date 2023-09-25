/*
 * @Author: highlightfip
 * @Date: 2023-08-19 11:48:26
 * @LastEditTime: 2023-09-25 18:05:50
 * @LastEditors: highlightfip 2793393724@qq.com
 * @Description: 
 * @FilePath: \stm32-boot\periph\oledmap.h
 */

#ifndef _OLEDMAP_H
#define _OLEDMAP_H

#define OLED_INITCMD_LEN 28
const uint8_t Oled_InitCmd[] =
{
	0xAE,0x20,0x10,0xb0,0xc8,0x00,0x10,0x40,0x81,0xff,
	0xa1,0xa6,0xa8,0x3F,0xa4,0xd3,0x00,0xd5,0xf0,0xd9,
	0x22,0xda,0x12,0xdb,0x20,0x8d,0x14,0xaf
};

#define F16x24_WIDTH 6
const uint8_t F6x8[][6] =
{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,// sp
	0x00, 0x00, 0x00, 0x2f, 0x00, 0x00,// !
	0x00, 0x00, 0x07, 0x00, 0x07, 0x00,// "
	0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14,// #
	0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12,// $
	0x00, 0x62, 0x64, 0x08, 0x13, 0x23,// %
	0x00, 0x36, 0x49, 0x55, 0x22, 0x50,// &
	0x00, 0x00, 0x05, 0x03, 0x00, 0x00,// '
	0x00, 0x00, 0x1c, 0x22, 0x41, 0x00,// (
	0x00, 0x00, 0x41, 0x22, 0x1c, 0x00,// )
	0x00, 0x14, 0x08, 0x3E, 0x08, 0x14,// *
	0x00, 0x08, 0x08, 0x3E, 0x08, 0x08,// +
	0x00, 0x00, 0x00, 0xA0, 0x60, 0x00,// ,
	0x00, 0x08, 0x08, 0x08, 0x08, 0x08,// -
	0x00, 0x00, 0x60, 0x60, 0x00, 0x00,// .
	0x00, 0x20, 0x10, 0x08, 0x04, 0x02,// /
	0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E,// 0
	0x00, 0x00, 0x42, 0x7F, 0x40, 0x00,// 1
	0x00, 0x42, 0x61, 0x51, 0x49, 0x46,// 2
	0x00, 0x21, 0x41, 0x45, 0x4B, 0x31,// 3
	0x00, 0x18, 0x14, 0x12, 0x7F, 0x10,// 4
	0x00, 0x27, 0x45, 0x45, 0x45, 0x39,// 5
	0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30,// 6
	0x00, 0x01, 0x71, 0x09, 0x05, 0x03,// 7
	0x00, 0x36, 0x49, 0x49, 0x49, 0x36,// 8
	0x00, 0x06, 0x49, 0x49, 0x29, 0x1E,// 9
	0x00, 0x00, 0x36, 0x36, 0x00, 0x00,// :
	0x00, 0x00, 0x56, 0x36, 0x00, 0x00,// ;
	0x00, 0x08, 0x14, 0x22, 0x41, 0x00,// <
	0x00, 0x14, 0x14, 0x14, 0x14, 0x14,// =
	0x00, 0x00, 0x41, 0x22, 0x14, 0x08,// >
	0x00, 0x02, 0x01, 0x51, 0x09, 0x06,// ?
	0x00, 0x32, 0x49, 0x59, 0x51, 0x3E,// @
	0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C,// A
	0x00, 0x7F, 0x49, 0x49, 0x49, 0x36,// B
	0x00, 0x3E, 0x41, 0x41, 0x41, 0x22,// C
	0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C,// D
	0x00, 0x7F, 0x49, 0x49, 0x49, 0x41,// E
	0x00, 0x7F, 0x09, 0x09, 0x09, 0x01,// F
	0x00, 0x3E, 0x41, 0x49, 0x49, 0x7A,// G
	0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F,// H
	0x00, 0x00, 0x41, 0x7F, 0x41, 0x00,// I
	0x00, 0x20, 0x40, 0x41, 0x3F, 0x01,// J
	0x00, 0x7F, 0x08, 0x14, 0x22, 0x41,// K
	0x00, 0x7F, 0x40, 0x40, 0x40, 0x40,// L
	0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F,// M
	0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F,// N
	0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E,// O
	0x00, 0x7F, 0x09, 0x09, 0x09, 0x06,// P
	0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E,// Q
	0x00, 0x7F, 0x09, 0x19, 0x29, 0x46,// R
	0x00, 0x46, 0x49, 0x49, 0x49, 0x31,// S
	0x00, 0x01, 0x01, 0x7F, 0x01, 0x01,// T
	0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F,// U
	0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F,// V
	0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F,// W
	0x00, 0x63, 0x14, 0x08, 0x14, 0x63,// X
	0x00, 0x07, 0x08, 0x70, 0x08, 0x07,// Y
	0x00, 0x61, 0x51, 0x49, 0x45, 0x43,// Z
	0x00, 0x00, 0x7F, 0x41, 0x41, 0x00,// [
	0x00, 0x55, 0x2A, 0x55, 0x2A, 0x55,// 55
	0x00, 0x00, 0x41, 0x41, 0x7F, 0x00,// ]
	0x00, 0x04, 0x02, 0x01, 0x02, 0x04,// ^
	0x00, 0x40, 0x40, 0x40, 0x40, 0x40,// _
	0x00, 0x00, 0x01, 0x02, 0x04, 0x00,// '
	0x00, 0x20, 0x54, 0x54, 0x54, 0x78,// a
	0x00, 0x7F, 0x48, 0x44, 0x44, 0x38,// b
	0x00, 0x38, 0x44, 0x44, 0x44, 0x20,// c
	0x00, 0x38, 0x44, 0x44, 0x48, 0x7F,// d
	0x00, 0x38, 0x54, 0x54, 0x54, 0x18,// e
	0x00, 0x08, 0x7E, 0x09, 0x01, 0x02,// f
	0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C,// g
	0x00, 0x7F, 0x08, 0x04, 0x04, 0x78,// h
	0x00, 0x00, 0x44, 0x7D, 0x40, 0x00,// i
	0x00, 0x40, 0x80, 0x84, 0x7D, 0x00,// j
	0x00, 0x7F, 0x10, 0x28, 0x44, 0x00,// k
	0x00, 0x00, 0x41, 0x7F, 0x40, 0x00,// l
	0x00, 0x7C, 0x04, 0x18, 0x04, 0x78,// m
	0x00, 0x7C, 0x08, 0x04, 0x04, 0x78,// n
	0x00, 0x38, 0x44, 0x44, 0x44, 0x38,// o
	0x00, 0xFC, 0x24, 0x24, 0x24, 0x18,// p
	0x00, 0x18, 0x24, 0x24, 0x18, 0xFC,// q
	0x00, 0x7C, 0x08, 0x04, 0x04, 0x08,// r
	0x00, 0x48, 0x54, 0x54, 0x54, 0x20,// s
	0x00, 0x04, 0x3F, 0x44, 0x40, 0x20,// t
	0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C,// u
	0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C,// v
	0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C,// w
	0x00, 0x44, 0x28, 0x10, 0x28, 0x44,// x
	0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C,// y
	0x00, 0x44, 0x64, 0x54, 0x4C, 0x44,// z
	0x14, 0x14, 0x14, 0x14, 0x14, 0x14,// horiz lines
};

#define F16x24_WIDTH 16
const uint8_t F16x24[][48] =
{
	0x00,0x80,0xE0,0xF0,0x78,0x1C,0x0C,0x0C,0x0C,0x0C,0x1C,0x78,0xF0,0xE0,0x80,0x00,
	0x00,0x3F,0xFF,0xFF,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xFF,0xFF,0x3F,0x00,
	0x00,0x00,0x00,0x01,0x03,0x07,0x06,0x06,0x06,0x06,0x07,0x03,0x01,0x00,0x00,0x00,//0

	0x00,0x00,0x00,0x10,0x10,0x18,0x18,0x18,0xF8,0xFC,0xFC,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x06,0x06,0x06,0x06,0x06,0x07,0x07,0x07,0x06,0x06,0x06,0x06,0x06,//1

	0x00,0x00,0x18,0x18,0x0C,0x0C,0x0C,0x0C,0x0C,0x1C,0xF8,0xF8,0xE0,0x00,0x00,0x00,
	0x00,0x00,0x00,0x80,0xC0,0xE0,0x30,0x18,0x1C,0x0E,0x07,0x03,0x01,0x00,0x00,0x00,
	0x00,0x00,0x07,0x07,0x07,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x00,0x00,0x00,//2

	0x00,0x00,0x00,0x18,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x1C,0xF8,0xF8,0x70,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x06,0x06,0x06,0x06,0x0F,0x0F,0xFD,0xF8,0xF0,0x00,0x00,
	0x00,0x00,0x00,0x07,0x06,0x06,0x06,0x06,0x06,0x07,0x07,0x03,0x01,0x00,0x00,0x00,//3

	0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xE0,0x70,0x38,0xFC,0xFC,0xFC,0x00,0x00,0x00,
	0x00,0x00,0x30,0x3C,0x3E,0x33,0x31,0x30,0x30,0x30,0xFF,0xFF,0xFF,0x30,0x30,0x30,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x07,0x07,0x00,0x00,0x00,//4

	0x00,0x00,0x00,0x00,0xFC,0xFC,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x03,0x03,0x03,0x03,0x03,0x07,0x8E,0xFE,0xFC,0xF8,0x00,0x00,
	0x00,0x00,0x00,0x00,0x07,0x06,0x06,0x06,0x06,0x07,0x03,0x03,0x01,0x00,0x00,0x00,//5

	0x00,0x00,0x80,0xE0,0xF0,0x78,0x38,0x1C,0x0C,0x0C,0x0C,0x0C,0x0C,0x18,0x00,0x00,
	0x00,0x00,0x7F,0xFF,0xFF,0x8C,0x06,0x03,0x03,0x03,0x07,0x0F,0xFE,0xFC,0xF8,0x00,
	0x00,0x00,0x00,0x01,0x03,0x03,0x07,0x06,0x06,0x06,0x06,0x03,0x03,0x01,0x00,0x00,//6

	0x00,0x00,0x00,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x8C,0xCC,0x7C,0x3C,0x0C,0x00,
	0x00,0x00,0x00,0x00,0x00,0x80,0xE0,0xF0,0x3C,0x0E,0x07,0x01,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x06,0x07,0x07,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//7

	0x00,0x00,0x00,0xF0,0xF8,0xF8,0x9C,0x0C,0x0C,0x0C,0x1C,0xFC,0xF8,0x70,0x00,0x00,
	0x00,0x00,0xE0,0xF8,0xFD,0x0F,0x07,0x07,0x06,0x0E,0x0F,0x1D,0xF9,0xF8,0xF0,0x00,
	0x00,0x00,0x00,0x03,0x03,0x07,0x06,0x06,0x06,0x06,0x06,0x07,0x03,0x01,0x00,0x00,//8

	0x00,0x00,0xE0,0xF0,0xF8,0x18,0x0C,0x0C,0x0C,0x0C,0x1C,0x38,0xF8,0xF0,0xC0,0x00,
	0x00,0x00,0x03,0x07,0x0F,0x1E,0x1C,0x18,0x18,0x18,0x8C,0xC6,0xFF,0xFF,0x3F,0x00,
	0x00,0x00,0x00,0x03,0x06,0x06,0x06,0x06,0x06,0x07,0x03,0x03,0x01,0x00,0x00,0x00,//9

	
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0xC7,0xC7,0xC7,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//:



};

uint8_t BMP_EX[] =
{
	0x00,0x03,0x05,0x09,0x11,0xFF,0x11,0x89,0x05,0xC3,0x00,0xE0,0x00,0xF0,0x00,0xF8,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x44,0x28,0xFF,0x11,0xAA,0x44,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x83,0x01,0x38,0x44,0x82,0x92,
	0x92,0x74,0x01,0x83,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7C,0x44,0xC7,0x01,0x7D,
	0x7D,0x7D,0x7D,0x01,0x7D,0x7D,0x7D,0x7D,0x01,0x7D,0x7D,0x7D,0x7D,0x01,0xFF,0x00,
	0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x00,0x00,0x00,0x00,
	0x00,0x00,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,
	0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x40,0x40,0x40,0x40,0x00,0x00,
	0x6D,0x6D,0x6D,0x6D,0x6D,0x00,0x00,0x60,0x60,0x60,0x60,0x60,0x00,0x00,0x40,0x40,
	0x40,0x40,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xDB,0xDB,0xDB,0xDB,0xDB,0x00,0x00,
	0xDB,0xDB,0xDB,0xDB,0xDB,0x00,0x00,0xDB,0xDB,0xDB,0xDB,0xDB,0x00,0x00,0xDB,0xDB,
	0xDB,0xDB,0xDB,0x00,0x00,0xDA,0xDA,0xDA,0xDA,0xDA,0x00,0x00,0xD8,0xD8,0xD8,0xD8,
	0xD8,0x00,0x00,0xC0,0xC0,0xC0,0xC0,0xC0,0x00,0x00,0xC0,0xC0,0xC0,0xC0,0xC0,0x00,
	0x00,0xC0,0xC0,0xC0,0xC0,0xC0,0x00,0x00,0xC0,0xC0,0xC0,0xC0,0xC0,0x00,0x00,0x80,
	0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x06,0x06,0x06,0x06,0x00,0x00,
	0x06,0x06,0x06,0x06,0x06,0x00,0x00,0x06,0x06,0x06,0x06,0x06,0x00,0x00,0x06,0x06,
	0x06,0x06,0x06,0x00,0x00,0x06,0x06,0x06,0xE6,0x66,0x20,0x00,0x06,0x06,0x86,0x06,
	0x06,0x00,0x00,0x06,0x06,0x06,0x06,0x86,0x00,0x00,0x06,0x06,0x06,0x06,0x06,0x00,
	0x00,0x86,0x86,0x86,0x86,0x86,0x80,0x80,0x86,0x86,0x06,0x86,0x86,0xC0,0xC0,0x86,
	0x86,0x86,0x06,0x06,0xD0,0x30,0x76,0x06,0x06,0x06,0x06,0x00,0x00,0x06,0x06,0x06,
	0x06,0x06,0x00,0x00,0x06,0x06,0x06,0x06,0x06,0x00,0x00,0x06,0x06,0x06,0x06,0x06,
	0x00,0x00,0x06,0x06,0x06,0x06,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x1C,0x00,0xFE,0x00,0x01,
	0x02,0x00,0xC4,0x18,0x20,0x02,0x9E,0x63,0xB2,0x0E,0x00,0xFF,0x81,0x81,0xFF,0x00,
	0x00,0x80,0x40,0x30,0x0F,0x00,0x00,0x00,0x00,0xFF,0x00,0x23,0xEA,0xAA,0xBF,0xAA,
	0xEA,0x03,0x3F,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0E,0x0C,0x08,0x00,0x00,0x01,0x01,0x01,
	0x01,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x81,0x80,0x80,0x81,0x80,
	0x81,0x80,0x80,0x80,0x80,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,
	0x01,0x00,0x01,0x01,0x09,0x0C,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,
	0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0x00,
	0x00,0x1E,0x21,0x40,0x40,0x50,0x21,0x5E,0x00,0x1E,0x21,0x40,0x40,0x50,0x21,0x5E,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xC1,0xC1,0xFF,
	0xFF,0xC1,0xC1,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x80,0xFC,0xF3,0xEF,0xF3,0xFC,
	0x80,0xFF,0x80,0xEE,0xEE,0xEE,0xF5,0xFB,0xFF,0x9C,0xBE,0xB6,0xB6,0x88,0xFF,0x00,/*"D:\DreamSpark\OLED\MP3_UI.bmp",0*/
};

const uint8_t BS_8bit_left[] =
{
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x18,0x1C,0x1C,0x3C,0x3C,0x78,0xF8,0xF0,
	0xF0,0xF0,0xE0,0xE0,0xE0,0xC0,0xC0,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xE0,
	0xF0,0xF8,0xFD,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFE,0xFE,
	0xFE,0xFC,0xFC,0xFC,0xF8,0xF8,0xF0,0xF0,0xE0,0xE0,0xE0,0xC0,0xC0,0x80,0x80,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0xFC,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFE,0xFC,0xFC,0xFC,0x78,0x78,0xF0,0xF0,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x7F,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0x7F,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x0F,
	0x1F,0x3F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x3F,
	0x1F,0x0F,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xE0,0xF0,0x78,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x01,0x03,0x03,0x07,0x07,0x07,0x0F,0x0F,0x0F,0x0F,0x1F,0x1F,
	0x1F,0x1F,0x1F,0x0F,0x0F,0x0F,0x0F,0x07,0x07,0x07,0x03,0x03,0x01,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x3C,0x1E,0x0F,0x07,0x03,0x01,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

/**
 * @brief: represent 2 in data_ptr[0]
 */
const uint8_t BS_8bit_right[] =
{
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xC0,0xC0,0xE0,0xE0,0xE0,0xF0,0xF0,
	0xF0,0xF8,0x78,0x3C,0x3C,0x1C,0x1C,0x18,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x80,0x80,0xC0,0xC0,0xE0,0xE0,0xE0,0xF0,0xF0,0xF8,0xF8,0xFC,0xFC,0xFC,0xFE,
	0xFE,0xFE,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFD,0xF8,0xF0,
	0xE0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0xF0,0xF0,0x78,0x78,0xFC,0xFC,0xFC,0xFE,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFC,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x7F,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0x7F,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x78,0xF0,0xE0,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x0F,0x1F,
	0x3F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x3F,0x1F,
	0x0F,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x01,0x03,0x07,0x0F,0x1E,0x3C,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x01,0x03,0x03,0x07,0x07,0x07,0x0F,0x0F,0x0F,0x0F,0x1F,0x1F,0x1F,
	0x1F,0x1F,0x0F,0x0F,0x0F,0x0F,0x07,0x07,0x07,0x03,0x03,0x01,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

/********************************space impact********************************/

const uint8_t F4x6[][4] = //score num
{
	0x1F,0x11,0x1F,0x00,//0
	0x00,0x1F,0x00,0x00,//1
	0x1D,0x15,0x17,0x00,//2
	0x15,0x15,0x1F,0x00,//3
	0x07,0x04,0x1F,0x00,//4
	0x17,0x15,0x1D,0x00,//5
	0x1F,0x15,0x1D,0x00,//6
	0x01,0x01,0x1F,0x00,//7
	0x1F,0x15,0x1F,0x00,//8
	0x17,0x15,0x1F,0x00,//9
	0x00,0x1B,0x00,0x00,//:
};

#define BMP_HEALTH_WIDTH 5
#define BMP_HEALTH_HEIGHT 4
const uint8_t health[] = //5x4
{
	0x03,0x07,0x0E,0x07,0x03,0x00
};

#define BMP_SPACESHIP_WIDTH 12
#define BMP_SPACESHIP_HEIGHT 7
const uint8_t spaceship[] = //12x7
{
	//0x0C,0x0F,0x0D,0x0D,0x0E,0x04
	0x30,0x58,0x5C,0x5E,0x5F,0x5F,0x59,0x59,0x59,0x5A,0x5C,0x30,

};


#endif
