# TinyRTC

Simple program to interface __TinyRTC (DS1307 RTC, Real Time Clock)__ with Arduino.

## Functions
  - bool __setDate__( secs, mins, hours, day, month, year, weekday )
  - bool __getDate__( secs, mins, hours, day, month, year, weekday )
 
 Both functions returns if the operation was done succesfully or not.

## Usage
  You only have to call the *__setDate( params )__* function when you need to update the date,
  and *__getDate( params )__*, to get the current date from the IC.
  
  The *__getDate( params )__* function returns the data throught the paramaters (they are passed by reference).

  Take a look at the code to see how it works! :)

## External usage
  If you want to use this code in your program, you only have to copy the functions ( *setDate()*, *getDate()*,
  *int_to_bcd()*, *bcd_to_int()* ) to your program. Also, you have to copy the "__RTC_ADDRESS__" constant.
  
  Finally, you'll need to include '*__Wire.h__*' and initialize it ( *Wire.begin()* ), in the '*__setup()__*' function.
  
  ( Or you can copy everything. )
  
  Easy!

## Wiring

![TinyRTC Wiring](https://github.com/pirobtumen/TinyRTC/blob/master/img/TinyRTC_Wiring.jpg?raw=true)

These pins (SDA,SCL) are used to communicate with Arduino through I2C, with the 'Wire' library. [Read more](https://www.arduino.cc/en/Reference/Wire).
