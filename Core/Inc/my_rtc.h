/*
 * my_rtc.h
 *
 *  Created on: Oct 27, 2023
 *      Author: mzeml
 */

#ifndef MY_RTC_H_
#define MY_RTC_H_

#include <stdint.h>
#include <stdio.h>

#include "main.h"
//#include "my_nmea.h"
#include "my_conversions.h"

extern RTC_HandleTypeDef hrtc ;

extern uint16_t tim_seconds ;

void		my_rtc_get_dt ( RTC_DateTypeDef* d , RTC_TimeTypeDef* t ) ;
uint16_t	my_rtc_get_dt_s ( char* ) ;
bool		my_rtc_set_alarm ( uint32_t ) ;

#endif /* MY_RTC_H_ */
