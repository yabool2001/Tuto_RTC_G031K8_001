/*
 * my_conversions.h
 *
 *  Created on: Oct 7, 2023
 *      Author: mzeml
 */

#ifndef MY_CONVERSIONS_H_
#define MY_CONVERSIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "stm32g0xx_hal.h"

double		my_string2double_conv ( const char* ) ;
float		my_string2float_conv ( const char* ) ;
uint8_t		my_find_char_position ( const char* , const char , uint8_t ) ;
uint32_t	my_conv_rtc2timestamp ( RTC_DateTypeDef* , RTC_TimeTypeDef* ) ;
void		my_conv_timestamp2rtc ( uint32_t , RTC_DateTypeDef* , RTC_TimeTypeDef* ) ;
int			my_conv_is_leap_year ( int ) ;

#endif /* MY_CONVERSIONS_H_ */
