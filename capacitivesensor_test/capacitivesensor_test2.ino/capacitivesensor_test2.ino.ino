#include <CapacitiveSensor.h>
#include "Statistic.h"

Statistic data;
CapacitiveSensor cs_4_2 = CapacitiveSensor(11, 12);  // 10 megohm resistor between pins 4 & 2, pin 2 is sensor pin, add wire, foil
const int LEDpin = 2;
const int motor1Pin = 5;  // H-bridge leg 1 (pin 6, 1A)
const int motor2Pin = 6;  // H-bridge leg 2 (pin 7, 2A)
const int pwmPin = 5;     // Motor driver PWM pin

int speed = 127; // speed of the motor (0-255):
float lastDev = 0;        // previous standard deviation

void setup(void) {
  // Serial.begin(9600);
  data.clear();  // explicitly start clean

  pinMode(LEDpin, OUTPUT);
  digitalWrite(LEDpin, LOW);

  // set all the other pins you're using as outputs:
  pinMode(motor1Pin, OUTPUT);
  pinMode(motor2Pin, OUTPUT);

  // set capacitive sensor timing
  cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);  // turn off autocalibrate on channel 1 - 
}

void loop(void) {
  long start = millis();
  long total = cs_4_2.capacitiveSensor(30);
  data.add(total);

  float currentDev = data.pop_stdev();

  // Serial.print(lastDev, 2);
  // Serial.print("\t");
  // Serial.println(currentDev, 2);

  if (currentDev >= lastDev) {
    // Serial.println("HI");
    digitalWrite(LEDpin, HIGH);
    digitalWrite(motor1Pin, LOW);
    // set leg 2 of the H-bridge high:
    analogWrite(motor2Pin, speed);
  } else {
    // Serial.println("LO");
    digitalWrite(LEDpin, LOW);
    digitalWrite(motor1Pin, LOW);
    // set leg 2 of the H-bridge high:
    analogWrite(motor2Pin, 0);
  }

  lastDev = currentDev;
  delay(10);  // arbitrary delay to limit data to serial port
}