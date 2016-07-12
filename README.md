# TinyRTC

Simple program to interface DS1307 RTC (Real Time Clock) with Arduino.

## Functions
  - bool __setDate__( secs, mins, hours, day, month, year, weekday )
  - bool __getDate__( secs, mins, hours, day, month, year, weekday )
 
 Both functions returns if the operation was done succesfully or not.

## Usage
  You only have to call the *__setDate( params )__* function when you need to update the date,
  and *__getDate( params )__*, to get the current date from the IC.
  
  The *__getDate( params )__* function returns the data throught the paramaters (they are passed by reference).

  __Take a look at the code to see how it works!__

## External usage
  If you want to use this code in your program, you only have to copy the functions ( *__setDate()__*, *__getDate()__*,
  *__int_to_bcd()__*, *__bcd_to_int()__* ) to your program. Also, you have to copy the "__RTC_ADDRESS__" constant.
  
  Finally, you'll need to include '*__Wire.h__*' and initialize it ( *__Wire.begin()__* ), in the '*__setup()__*' function.
  
  __Easy!__

## Connecting it  with Arduino

  Soon...
