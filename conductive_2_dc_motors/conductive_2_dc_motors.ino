#include <CapacitiveSensor.h>
#include "Statistic.h"

#define PWM1 9
#define AIN1 7
#define AIN2 8
#define PWM2 6
#define BIN1 4
#define BIN2 5
#define LEDpin 2

Statistic data;
CapacitiveSensor cs_4_2 = CapacitiveSensor(11, 12);  // 10 megohm resistor between pins 4 & 2, pin 2 is sensor pin, add wire, foil

int speed1 = 70;    // speed of the motor (0-255):
int speed2 = 106;    // speed of the motor (0-255):
float lastDev = 0;  // previous standard deviation

void setup(void) {
  data.clear();  // explicitly start clean

  pinMode(LEDpin, OUTPUT);
  digitalWrite(LEDpin, LOW);

  pinMode(PWM1, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWM2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  // set capacitive sensor timing
  cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);  // turn off autocalibrate on channel 1 -
}

void loop(void) {
  long start = millis();
  long total = cs_4_2.capacitiveSensor(30);
  data.add(total);

  float currentDev = data.pop_stdev();

  if (currentDev >= lastDev) {
    // Serial.println("HI");
    digitalWrite(LEDpin, HIGH);

    digitalWrite(AIN1, HIGH);  //Motor A Rotate Clockwise
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, HIGH);  //Motor B Rotate Clockwise
    digitalWrite(BIN2, LOW);

    analogWrite(PWM1, speed1);  //Speed control of Motor A
    analogWrite(PWM2, speed2);  //Speed control of Motor B
  } else {
    // Serial.println("LO");
    digitalWrite(LEDpin, LOW);

    digitalWrite(AIN1, LOW);  //Motor A Rotate Clockwise
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW);  //Motor B Rotate Clockwise
    digitalWrite(BIN2, LOW);

    analogWrite(PWM1, 0);  //Speed control of Motor A
    analogWrite(PWM2, 0);  //Speed control of Motor B
  }

  lastDev = currentDev;
  delay(10);  // arbitrary delay to limit data to serial port
}