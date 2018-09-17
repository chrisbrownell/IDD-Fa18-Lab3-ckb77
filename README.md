# Data Logger (and using cool sensors!)

*A lab report by Chris Brownell (ckb77).*

## In The Report

In this lab, I experiment with a variety of sensors, sending the data to the Arduino serial monitor, writing data to the EEPROM of the Arduino, and then playing the data back. I also develop a ___ in part D.

## Part A.  Writing to the Serial Monitor
 
**a. Based on the readings from the serial monitor, what is the range of the analog values being read?**

Values range from 0 to 1023.
 
**b. How many bits of resolution does the analog to digital converter (ADC) on the Arduino have?**



## Part B. RGB LED

**How might you use this with only the parts in your kit? Show us your solution.**

I used the 220 ohm resistors to connect each of the cathode pins into Arduino pins 7, 8, and 9. See photo below. I also included the 10K potentiometer between power and the common anode so that I could vary the brightness of the LED:

INSEERT PHOTO

## Part C. Voltage Varying Sensors 
 
### 1. FSR, Flex Sensor, Photo cell, Softpot

**a. What voltage values do you see from your force sensor?**

The voltage values appear to vary between 0V when no pressure is applied, to the close to the full 5V. On a 0 to 1023 scale, 
I am able to get readings between 0 and 1003. A reading of 1003 implies 1003/1023 = 0.98 of the full voltage, or 4.9V.

When I connect the sensor to 3.3V rather than 5V, I only see a range of 0 to 672, which suggests voltage ranges from 0V to 
672/1023 = 3.28V. This makes sense intuitively.

**b. What kind of relationship does the voltage have as a function of the force applied? (e.g., linear?)**

The relationship does not appear to be linear, because I need to apply much more incremental force to go from a reading 
of 1000 to 10003 than I do from 0 to 3. It appears to be more of a logarithmic relationship than a linear one.

**c. Can you change the LED fading code values so that you get the full range of output voltages from the LED when using your FSR?**

See video [here](https://drive.google.com/file/d/1VJvWMkfe41nntwT4KAUbKrI_rIroknbg/view?usp=sharing).

I used the map function to map the FSR values (range: 0-1023) to a new range of 0-255 and also print the value to serial
monitor just as a gut check.

```
int led = 9;           // the PWM pin the LED is attached to
int brightness = 0;    // how bright the LED is

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // set the brightness of pin 9:
  brightness = map(analogRead(A0),0,1023,0,255);
  Serial.println(map(analogRead(A0),0,1023,0,255));
  analogWrite(led, brightness);

  // wait for 30 milliseconds to see the dimming effect
  delay(30);
}
```

**d. What resistance do you need to have in series to get a reasonable range of voltages from each sensor?**



**e. What kind of relationship does the resistance have as a function of stimulus? (e.g., linear?)**



### 2. Accelerometer
 
**a. Include your accelerometer read-out code in your write-up.**

### 3. IR Proximity Sensor

**a. Describe the voltage change over the sensing range of the sensor. A sketch of voltage vs. distance would work also. Does it match up with what you expect from the datasheet?**

**b. Upload your merged code to your lab report repository and link to it here.**

## Optional. Graphic Display

**Take a picture of your screen working insert it here!**

## Part D. Logging values to the EEPROM and reading them back
 
### 1. Reading and writing values to the Arduino EEPROM

**a. Does it matter what actions are assigned to which state? Why?**

**b. Why is the code here all in the setup() functions and not in the loop() functions?**

**c. How many byte-sized data samples can you store on the Atmega328?**

**d. How would you get analog data from the Arduino analog pins to be byte-sized? How about analog data from the I2C devices?**

**e. Alternately, how would we store the data if it were bigger than a byte? (hint: take a look at the [EEPROMPut](https://www.arduino.cc/en/Reference/EEPROMPut) example)**

**Upload your modified code that takes in analog values from your sensors and prints them back out to the Arduino Serial Monitor.**

### 2. Design your logger
 
**a. Insert here a copy of your final state diagram.**

### 3. Create your data logger!
 
**a. Record and upload a short demo video of your logger in action.**
