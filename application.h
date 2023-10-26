/* 
 * File:   application.h
 * Author: Marwan Mohamed
 *
 * Created on August 21, 2023, 1:53 AM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H
/*Section: includes */

#include"ECU_Layer/ecu_init.h"
/*Section: Macros Declarations */
#define limit_repeat   3
/*Section: Data Types Declarations */
extern ch_lcd_4bits_t lcd_4b;
extern keypad_t keypad;

/*Section: Function Declarations */
void application_intialize(void);
void Welcome_massage(void);
void loading(void);
#endif	/* APPLICATION_H */

