/*
mgs::serial library
  Provides a method to enable/disable serial (debug) output

  Usage
    Declare 'serialEnabled' in the application and set to 'true' for normal output or 'false' to disable the serial output.

    Replace all 'serial' statements in the application as follows.
      Serial.begin(x);      SERIAL_BEGIN(x);
      Serial.print(x);      SERIAL_PRINT(x);
      Serial.println(x);    SERIAL_PRINTLN(x);
      Serial.print(x,y);    SERIAL_PRINT2(x,y);
      Serial.println(x,y);  SERIAL_PRINTLN2(x,y);

  Author
    Martin Scott February 2024
*/

#ifndef mgsSerial_H
#define mgsSerial_H

#define SERIAL_BEGIN(x);       if(mgs::serial::serialEnabled) { Serial.begin(x); }
#define SERIAL_PRINT(x);       if(mgs::serial::serialEnabled) { Serial.print(x); }
#define SERIAL_PRINTLN(x);     if(mgs::serial::serialEnabled) { Serial.println(x); }
#define SERIAL_PRINT2(x,y);    if(mgs::serial::serialEnabled) { Serial.print(x,y); }
#define SERIAL_PRINTLN2(x,y);  if(mgs::serial::serialEnabled) { Serial.println(x,y); }


namespace mgs
{
  namespace serial
  {
    extern bool serialEnabled;
  }
}

#endif