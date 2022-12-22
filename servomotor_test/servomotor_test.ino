/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep
*/

#include <Servo.h>
Servo servo1;  // create servo object to control a servo
Servo servo2;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int posA1 = 0;  // variable to store the servo1 position
int posB1 = 0;

int posA2 = 0;  // variable to store the servo2 position
int posB2 = 0;

int mapSpeed1;
int mapSpeed2;

int increasing1 = true;
int increasing2 = true;

void setup() {
  servo1.attach(12);
  servo2.attach(11);
}

void loop() {
  moveTo(servo1, 180, posA1, posB1, mapSpeed1, increasing1);
  moveTo(servo2, 180, posA2, posB2, 28, mapSpeed2, increasing2);
}

void moveTo(Servo myservo, int position, int pos, int pos1, int speed, int mapSpeed, int increasing) {
  mapSpeed = map(speed, 0, 30, 30, 0);
  if (increasing) {
    for (pos = pos1; pos <= position; pos += 1) {
      myservo.write(pos);
      pos1 = pos;
      delay(mapSpeed);
    }
    increasing = false;
  } else {
    for (pos = pos1; pos >= 0; pos -= 1) {
      myservo.write(pos);
      pos1 = pos;
      delay(mapSpeed);
    }
    increasing = true;
  }
}
