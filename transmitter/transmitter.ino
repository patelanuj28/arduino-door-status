// ask_transmitter.pde
// -*- mode: C++ -*-
// Simple example of how to use RadioHead to transmit messages
// with a simple ASK transmitter in a very simple way.
// Implements a simplex (one-way) transmitter with an TX-C1 module
// Tested on Arduino Mega, Duemilanova, Uno, Due, Teensy, ESP-12

#include <RH_ASK.h>
#ifdef RH_HAVE_HARDWARE_SPI
#include <SPI.h> // Not actually used but needed to compile
#endif

const int switch_sensor = 3;
int state; // 0 close - 1 open wwitch
RH_ASK driver(2000, 5, 4, 0);

void setup()
{
#ifdef RH_HAVE_SERIAL
    Serial.begin(9600);	  // Debugging only
#endif
    if (!driver.init())
#ifdef RH_HAVE_SERIAL
         Serial.println("init failed");
#else
	;
#endif

pinMode(switch_sensor, INPUT_PULLUP);
}

void loop()
{
  
  state = digitalRead(switch_sensor);
  if (state == HIGH){
    const char *door_open = "door open";    
    driver.send((uint8_t *)door_open, strlen(door_open));
  }
  else{
    const char *door_close = "door close";
    driver.send((uint8_t *)door_close, strlen(door_close));
  }  
  driver.waitPacketSent();    
  delay(200);
}
