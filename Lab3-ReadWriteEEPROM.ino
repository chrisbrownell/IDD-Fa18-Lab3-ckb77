/*
  Modified state machine to measure and store softpot readings in EEPROM
 
  Modified from State Machine 2 by Wendy Ju
 
  Simplified to 2 states - one to read and store softpot measurements every 50 ms
  as long as the softpot analog read is less than 1023, and one to print back those
  values (scaled from 0 to 255) from EEPROM once the softpot reaches 1023.
  
 */

#include <EEPROM.h>

const int sensorMin =0;
const int sensorMax = 1024;
const int EEPROMSIZE=1024;
byte value;

int sensorPin = A0;    // select the input pin for the potentiometer
int ledPin = LED_BUILTIN;    
int state,lastState = -1;

void setup() {
  // initialize serial communication:
  Serial.begin(9600);  
}

void loop() {
  // map the pot range to 2 states :
  if(analogRead(sensorPin) < 1023) {
  state = 0;
  } else {
  state = 1;
  }
  // do something different depending on the 
  // range value:
  switch (state) {
  case 0:    
    doState0();
    break;
  case 1:    
    doState1();
    break;
  } 
  lastState = state;
}

// State 0 is where we write softpot values to EEPROM
void state0Setup() {
  Serial.println("Storing values");
  // store up to EEPROMSIZE values
  for(int i=0; i < EEPROMSIZE; i++){
    if(analogRead(sensorPin)==1023) {break;}
  EEPROM.write(i,map(analogRead(sensorPin),0,1023,0,255));
 // Serial.println(analogRead(sensorPin));
  delay(50);
  }
}

void state0Loop() {
  
}

void doState0() {
  if (lastState != 0) { state0Setup(); }
  state0Loop();
}

// State 1 is where we read back the sequential softpot values that were stored 
void state1Setup() {
  Serial.println("Reading stored softpot measures");

  for (int i = 0; i < EEPROMSIZE; i++) {
    value = EEPROM.read(i);
    Serial.println(value);
  }
  Serial.println();

  Serial.println("Done reading from EEPROM");
}

void state1Loop() {
}

void doState1() {
  if (lastState != 1) { state1Setup(); }
  state1Loop();
}
