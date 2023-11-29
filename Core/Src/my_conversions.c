/*
 * my_conversions.c
 *
 *  Created on: Oct 7, 2023
 *      Author: mzeml
 */

#include "my_conversions.h"

double my_string2double_conv ( const char* s )
{
    double d = strtod ( s , NULL ) ;
    return d ;
}

float my_string2float_conv ( const char* s )
{
    float f = strtof ( s , NULL ) ;
    return f ;
}

//Find position in string of n occurance of the comma
uint8_t my_find_char_position ( const char* m , const char c , uint8_t n )
{
	uint8_t i = 0 ;
	uint8_t p = 0 ;

	while ( m[i] != '\0' )
	{
		if ( m[i] == c )
			p++ ;
		if ( p == n )
			break ;
		i++ ;
	}
	return i ;
}

// Function converting RTC date and time to Unix timestamp (ts): number of seconds after the Epoch (1970.01.01).
uint32_t my_conv_rtc2timestamp ( RTC_DateTypeDef* d , RTC_TimeTypeDef* t )
{
    // Number of days in months (considering leap years).
    static const uint8_t monthDays[12] = { 31 , 28 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31 } ;

    // Conversion of years into days.
    uint32_t years = d->Year + 2000;  // RTC starts from 20
    uint32_t days = ( years - 1970 ) * 365 + ( ( years - 1969 ) / 4 ) ;  // Days for years and leap years.
    // Conversion of months into days.
    for ( int i = 0 ; i < d->Month - 1 ; i++ )
    {
        days += monthDays[i] ;
    }
    if ( d->Month > 2 && my_conv_is_leap_year ( years ) )
    {
        days++ ;  // Add one day in a leap year.
    }
    // add the days of the month
    days += d->Date - 1 ;
    // Convert days into seconds and add hours, minutes, seconds.
    uint32_t ts = days * 86400 + t->Hours * 3600 + t->Minutes * 60 + t->Seconds ;

    return ts ;
}

// Function converting Unix timestamp (ts) to RTC date and time
void my_conv_timestamp2rtc ( uint32_t ts , RTC_DateTypeDef* d , RTC_TimeTypeDef* t )
{
	static const uint16_t daysInMonth[12] = { 31 , 28 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31 } ;
	uint32_t seconds = ts % 60 ;
	uint32_t minutes = ( ts / 60 ) % 60 ;
	uint32_t hours = ( ts / 3600 ) % 24 ;

	// Counting days since Epoch
	uint32_t days = ts / 86400 ;

	// Calculating the year
	uint32_t year = 1970 ;
	while ( days >= 365 + my_conv_is_leap_year ( year ) )
	{
		days -= 365 + my_conv_is_leap_year ( year ) ;
		year++ ;
	}

	// Calculating the month
	uint32_t month = 0 ;
	while ( days >= daysInMonth[month] + ( month == 1 && my_conv_is_leap_year ( year ) ) ) {
		days -= daysInMonth[month] + ( month == 1 && my_conv_is_leap_year ( year ) ) ;
		month++ ;
	}

	// Setting date and time in RTC structures
	d->Year = year - 2000 ; // RTC_DateTypeDef.Year expects years since 2000
	d->Month = month + 1 ;  // +1 because month is counted from 0
	d->Date = days + 1 ;    // +1 because days are counted from 0
	t->Hours = hours ;
	t->Minutes = minutes ;
	t->Seconds = seconds ;
}

// Function checking for leap years
int my_conv_is_leap_year ( int yyyy )
{
    return ( ( yyyy % 4 == 0 ) && ( yyyy % 100 != 0 ) ) || ( yyyy % 400 == 0 ) ;
}

