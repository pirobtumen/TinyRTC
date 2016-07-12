/*
  The MIT License (MIT)
  Copyright (c) 2016 Alberto Sola
  
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
  
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
  
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/*
 * TinyRTC (DS1307) Controller
 * 
 * Simple program to get and modify date.
 * 
 * Functions:
 *  - bool setDate( secs, mins, hours, day, month, year, weekday )
 *  - bool getDate( secs, mins, hours, day, month, year, weekday )
 * 
 *  Both functions returns if the operation was done succesfully or not.
 *  
 * Alberto Sola - 2016
 */

#include <Wire.h>


// -----------------------------------------------------------------------------


// TinyRTC (DS1307) I2C Address
const uint8_t RTC_ADDRESS = 0x68;

// Date variables
uint8_t sec, mins, hour, day, month, year, weekday;


// -----------------------------------------------------------------------------


uint8_t int_to_bcd( uint8_t data ){
  /*
   * Convert integer to BCD.
   */
   return (data / 10 * 16) + (data % 10);
}

// -----------------------------------------------------------------------------

uint8_t bcd_to_int( uint8_t data ){
  /*
   * Convert BCD 
   */
  return (data / 16 * 10) + (data & 0x0F);
}

// -----------------------------------------------------------------------------

bool setDate( uint8_t secs, uint8_t mins, uint8_t hours,
              uint8_t day, uint8_t month, uint8_t year,
              uint8_t weekday ){
  /*
   * Send the new date to the DS1307.
   */
   
  Wire.beginTransmission( RTC_ADDRESS );
  Wire.write(0x00);

  Wire.write( int_to_bcd(secs & 0x7F) );
  Wire.write( int_to_bcd(mins) );
  Wire.write( int_to_bcd(hour) );
  Wire.write( int_to_bcd(weekday) );
  Wire.write( int_to_bcd(day) );
  Wire.write( int_to_bcd(month) );
  Wire.write( int_to_bcd(year) );
  
  return Wire.endTransmission() == 0;
}

// -----------------------------------------------------------------------------

bool getDate( uint8_t & secs, uint8_t & mins, uint8_t & hours,
              uint8_t & day, uint8_t & month, uint8_t & year,
              uint8_t & weekday){
  /*
   * Get the date from the DS1307.
   */

  uint8_t control;
  
  Wire.beginTransmission(0x68);
  Wire.write(0);
  
  // Check if the DS1307 answered
  if(Wire.endTransmission() != 0)
    return false;

  // Read data (8B) request
  Wire.requestFrom(0x68, 8);
  
  secs = bcd_to_int(Wire.read());
  mins = bcd_to_int(Wire.read());
  hour = bcd_to_int(Wire.read());
  weekday = bcd_to_int(Wire.read());
  day = bcd_to_int(Wire.read());
  month = bcd_to_int(Wire.read());
  year = bcd_to_int(Wire.read());
  
  control = Wire.read();

  return true;
}

// -----------------------------------------------------------------------------

void setup(){
  /*
   * Initialize data and update date if necessary.
   */

  // Initialize communications
  Wire.begin();
  Serial.begin(9600);
  
  /*
   * Update date ONLY if it is necessary.
   * 
   * Uncomment the following code, set the time variables, upload the code,
   * and then comment it and upload the script again.
   */

   /*
   // Update time
   sec = 40;
   mins = 11;
   hour = 14;
   day = 12;
   month = 7;
   year = 16;
   
   // WDay is user defined:
   // If Monday = 1, then Tuesday = 2, ..., and so on.
   weekday = 2;
   
   if( setDate(sec,mins,hour,day,month,year,weekday) )
    Serial.println("DATE SET CORRECTLY.");
   else
    Serial.println("ERROR WHILE SETTING THE DATE.");
   */
}

void loop(){
  /*
   * Main loop. Only prints the current date (every second).
   */

  if( getDate(sec,mins,hour,day,month,year,weekday) ){
    Serial.print("Date: ");
    Serial.print(day);
    Serial.print('/');
    Serial.print(month);
    Serial.print('/');
    Serial.print(year);
    Serial.print('\n');
    
    Serial.print("Hour: ");
    Serial.print(hour);
    Serial.print(':');
    Serial.print(mins);
    Serial.print(':');
    if( sec < 10 )
      Serial.print('0');
    Serial.print(sec);
    Serial.print('\n');
    
    Serial.print('\n');

  }
  else
    Serial.println("Error while reading data.");

  delay(1000);
  
}
