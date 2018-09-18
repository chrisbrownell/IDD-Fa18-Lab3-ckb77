/*
  Modified state machine to measure and store softpot readings in EEPROM and play
  back via speaker when invoked by user.
 
  Modified from State Machine 2 by Wendy Ju
 
  Simplified to 2 states - one to read and store softpot measurements every 50 ms
  and transform to a value that corresponds with the three tones of Hot Crossed Buns and 
  the other to play back the notes registered on the softpot, when the user
  presses a button that is connected into switchPin.

  
 */

#include <EEPROM.h>
#include <LiquidCrystal.h>

const int sensorMin =0;
const int sensorMax = 1024;
const int EEPROMSIZE=1024;
byte value;

int sensorPin = A0;    // select the input pin for the potentiometer
int switchPin = A1;
int ledPin = LED_BUILTIN;    
int state,lastState = -1;
int playedNote = 0;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // initialize serial communication:
  Serial.begin(9600);  
  lcd.begin(16, 2);
}

void loop() {
  // map the pot range to 2 states :
  if(analogRead(switchPin) < 1000) {
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
  lcd.clear();
  lcd.print("Play that funky");
  lcd.setCursor(0,1);
  lcd.print("music!");
  // store up to EEPROMSIZE values
  for(int i=0; i < EEPROMSIZE; i++){
    if(analogRead(switchPin)>=1000) {break;}
  playedNote = map(analogRead(sensorPin),0,1023,0,4);
  Serial.println(playedNote);
  if(playedNote == 1) {
    playedNote = 175;
  } else if (playedNote == 2) {
    playedNote = 196;
  } else if (playedNote == 3) {
    playedNote = 220;
  }
  EEPROM.write(i,playedNote);
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
  lcd.clear();
  lcd.print("Now playing...");
  lcd.setCursor(0,1);
  lcd.print("your funky jamz!");

  for (int i = 0; i < EEPROMSIZE; i++) {
    value = EEPROM.read(i);
    Serial.println(value);
    tone(9, value, 60);
    delay(50);
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
