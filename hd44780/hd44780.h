/*************************************************************/
/**
 *  @file hd44780.h
 *  @brief hd44780 function declarations
 *  @author 115ek 115ek@users.noreply.github.com
 *
 *  @date 05.04.2016 – initial release
 *
 *  @version 1.0
 *************************************************************/

#ifndef HD44780_H_
#define HD44780_H_

#include "stm32f4xx.h"

//pin-setup
#define DB0      GPIO_PIN_8
#define DB1      GPIO_PIN_9
#define DB2      GPIO_PIN_10
#define DB3      GPIO_PIN_11
#define DB4      GPIO_PIN_12
#define DB5      GPIO_PIN_13
#define DB6      GPIO_PIN_14
#define DB7      GPIO_PIN_15
#define V0       GPIO_PIN_8
#define RS       GPIO_PIN_9
#define RW       GPIO_PIN_10
#define E     	 GPIO_PIN_11

//functions

/**clears the screen
 */
void lcd_clear(void);

/**sets the cursor position
 * @param line char between 0 to 1
 * @param row char between 0 to 15
 */
void lcd_goto(unsigned char line, unsigned char row);

/**sets the cursor position to (0,0)
 */
void lcd_home(void);

/**initializes the lcd, needed before first functions concerning lcd are used
 */
void lcd_init(void);

/**prints a char at the current cursor position
 * @param c char to be printed
 */
void lcd_printc(char c);

/**prints a string at the current cursor position
 * @param *s string to be printed
 */
void lcd_prints(const char *s);

#endif /* HD44780_H_ */
