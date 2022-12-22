#include <CapacitiveSensor.h>

/*
 * CapitiveSense Library Demo Sketch
  * Paul Badger 2008
 * Uses a high value resistor e.g. 10 megohm between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50 kilohm - 50 megohm. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 * Best results are obtained if sensor foil and wire is covered with an insulator such as paper or plastic sheet
 */

CapacitiveSensor   cs_4_2 = CapacitiveSensor(11,12);        // 10 megohm resistor between pins 4 & 2, pin 2 is sensor pin, add wire, foil
// CapacitiveSensor   cs_4_5 = CapacitiveSensor(4,5);        // 10 megohm resistor between pins 4 & 6, pin 6 is sensor pin, add wire, foil
// CapacitiveSensor   cs_4_8 = CapacitiveSensor(4,8);        // 10 megohm resistor between pins 4 & 8, pin 8 is sensor pin, add wire, foil

const int ledPin = 2;    // switch input
const int motor1Pin = 3;    // Motor driver leg 1 (pin 3, AIN1)
const int motor2Pin = 4;    // Motor driver leg 2 (pin 4, AIN2)
const int pwmPin = 5;       // Motor driver PWM pin
int initial = 0;

void setup()                    
{
  // set the switch as an input:
  pinMode(ledPin, OUTPUT); 

  // set all the other pins you're using as outputs:
  // pinMode(motor1Pin, OUTPUT);
  // pinMode(motor2Pin, OUTPUT);
  // pinMode(pwmPin, OUTPUT);

  // set PWM enable pin high so that motor can turn on:
  // digitalWrite(pwmPin, HIGH);

  // set capacitive sensor timing
  cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
  Serial.begin(9600);
  digitalWrite(ledPin, HIGH);
}

void loop() {
  long start = millis();
  long total1 =  cs_4_2.capacitiveSensor(30);
  // long total2 =  cs_4_5.capacitiveSensor(30);
  // long total3 =  cs_4_8.capacitiveSensor(30);、

  // Serial.println("total1: "+ total1);

  // Serial.print(millis() - start);        // check on performance in milliseconds
  // Serial.print("\t");                    // tab character for debug window spacing

  // Serial.print("INITIAL,");
  // Serial.println(initial);

  if (total1 > (initial * 4.5)) { // when touched, it spikes to roughly 5x of the initial setting (with 50m ohm resistance)
    // if the switch is high, motor will turn on one direction:
    // Serial.println("HI");
    // digitalWrite(motor1Pin, LOW);   // set leg 1 of the motor driver low
    // digitalWrite(motor2Pin, HIGH);  // set leg 2 of the motor driver high
    digitalWrite(ledPin, HIGH);
    // Serial.println(1);
  } else {
    digitalWrite(ledPin, LOW);
    // digitalWrite(motor1Pin, LOW);  // set leg 1 of the motor driver high
    // digitalWrite(motor2Pin, HIGH);   // set leg 2 of the motor driver low
    // Serial.println(0);
  }
  // Serial.print("TOTAL,");
  Serial.println(total1);                  // print sensor output 1
  delay(10);                             // arbitrary delay to limit data to serial port 
}