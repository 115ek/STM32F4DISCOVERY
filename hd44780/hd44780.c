/*************************************************************/
/**
 *  @file hd44780.c
 *  @brief hd44780 function definitions
 *  @author 115ek 115ek@users.noreply.github.com
 *
 *  @date 05.04.2016 – initial release
 *
 *  @version 1.0
 *************************************************************/

#include "hd44780.h"

void lcd_clear()
{
	GPIOD->ODR = 0x800;
	GPIOE->ODR = 0x100;
	GPIOD->ODR = 0x0;
	HAL_Delay(1);
}

void lcd_goto(unsigned char line, unsigned char row)
{

	GPIOD->ODR = 0x800;
	switch (line)
	{
		case 0:
			GPIOE->ODR = (uint32_t)(0x8000 + (row << 8)) ;
			break;
		case 1:
			GPIOE->ODR = (uint32_t)(0xC000 + (row << 8)) ;
			break;
		default:
			lcd_home();
			break;
	}
	GPIOD->ODR = 0x0;
	HAL_Delay(1);
}

void lcd_home()
{
	GPIOD->ODR = 0x800;
	GPIOE->ODR = 0x200;
	GPIOD->ODR = 0x0;
	HAL_Delay(1);
}

void lcd_init()
{
	GPIO_InitTypeDef ControlStruct;
	GPIO_InitTypeDef DisplayStruct;

	ControlStruct.Pin = RS | RW | E;
	ControlStruct.Mode = GPIO_MODE_OUTPUT_PP;
	ControlStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	ControlStruct.Pull = GPIO_NOPULL;

	DisplayStruct.Pin = DB0 | DB1 | DB2 | DB3 | DB4 | DB5 | DB6 | DB7; //all Pins needed
	DisplayStruct.Mode = GPIO_MODE_OUTPUT_PP;
	DisplayStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	DisplayStruct.Pull = GPIO_NOPULL;

	__HAL_RCC_GPIOE_CLK_ENABLE();			//enable the GPIO AHB clock
	__HAL_RCC_GPIOD_CLK_ENABLE();
	HAL_GPIO_Init(GPIOE, &DisplayStruct);
	HAL_GPIO_Init(GPIOD, &ControlStruct);

	/*  SETUP
	 *
	 *  RS RW E			DB	7 6 5 4 3 2 1 0			input read by falling edge of E
	 *	0  0  1				0 0 1 ? ? ? 0 0
	 *	SETTINGS:									D4[0==4bit     1==8bit]
	 *												D3[0==1zeilig  1==2zeilig]
	 *												D2[0==5x7Font  1==5x10Font]
	 */
	GPIOD->ODR = 0x800;
	GPIOE->ODR = 0x3800;
	GPIOD->ODR = 0x0;
	HAL_Delay(1);

	/*  MODES
	 *
	 *  RS RW E			DB	7 6 5 4 3 2 1 0			input read by falling edge of E
	 *	0  0  1	 			0 0 0 0 0 1 ? ?
	 *
	 *	SETIINGS									D1[0==incr. cursorpos.     1==decrem. cursorpos.]
	 *												D0[0==Anzeige fest     1==Anzeige weiterschieben]
	 */
	GPIOD->ODR = 0x800;
	GPIOE->ODR = 0x600;
	GPIOD->ODR = 0x0;
	HAL_Delay(1);

	/*	CURSORSETUP
	 *
	 * 	RS RW E			DB	7 6 5 4 3 2 1 0			input read by falling edge of E
	 *	0  0  1				0 0 0 0 1 ? ? ?
	 *
	 *	SETTINGS									D2[0==display OFF     1==display ON]
	 *												D1[0==cursor OFF      1==cursor ON]
	 *												D1[0==cursor blink OFF      1==cursor blink ON]
	 */
	GPIOD->ODR = 0x800;
	GPIOE->ODR = 0xC00;
	GPIOD->ODR = 0x0;
	HAL_Delay(1);

	/*	CURSOR TO START
	 *
	 *  RS RW E			DB	7 6 5 4 3 2 1 0			input gets read by falling edge of E
	 *	0  0  1				0 0 0 0 0 0 1 0
	 */
	GPIOD->ODR = 0x800;
	GPIOE->ODR = 0x200;
	GPIOD->ODR = 0x0;
}

void lcd_printc(char c)
{
	GPIOD->ODR = 0xA00;
	GPIOE->ODR = (uint32_t)(c << 8);
	GPIOD->ODR = 0x200;
	GPIOD->ODR = 0x0;
	HAL_Delay(1);
}

void lcd_prints(const char *s)
{
    register char c;
    while ((c=*s++))
    	lcd_printc(c);
}
