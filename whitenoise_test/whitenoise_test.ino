/* Noise machine using three potentiometers connected to analog inputs
and a piezo or small speaker. A pushbutton turns on the noise, the potentiometers
control the pitch using the Arduino tone() function, and two delay
values which control the length of each tone and length between
each tone. The potentiometers give analog values which are changed
using the map() function into larger or smaller ranges to suit your
musical tastes.
This code is in the public domain.
Matt Thomas 05/04/2019
*/
// const int buttonPin = 2;  // Pushbutton pin 2
const int trigPin = 3;
const int echoPin = 2;
const int speaker = 9;    // Speaker or piezo in pin 9
int buttonState = 0;      // Variables for the button
int potZero;              // and potentiometers
int potOne;
int potTwo;
void setup() {
  pinMode(9, OUTPUT);  // Speaker/piezo output pin
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}
void loop() {
  // buttonState = digitalRead(buttonPin);  // Read the pushbutton state
  potZero = analogRead(A0);              //Variables for reading the analog values
  potOne = analogRead(A1);
  potTwo = analogRead(A2);
  
  int htz = map(potZero, 0, 1023, 0, 8800);  // Map the analog readings into
  int high = map(potOne, 0, 1023, 0, 100);   // new number ranges and create
  int low = map(potTwo, 0, 1023, 0, 100);    // new variables

  // take the trigger pin low to start a pulse:
  digitalWrite(trigPin, LOW);
  // delay 2 microseconds:
  delayMicroseconds(2);
  // take the trigger pin high:
  digitalWrite(trigPin, HIGH);
  // delay 10 microseconds:
  delayMicroseconds(10);
  // take the trigger pin low again to complete the pulse:
  digitalWrite(trigPin, LOW);

  Serial.print(potZero);
  Serial.print(", ");
  Serial.print(potOne);
  Serial.print(", ");
  Serial.print(potTwo);
  Serial.print(", ");
 
  // listen for a pulse on the echo pin:
  long duration = pulseIn(echoPin, HIGH);
  // calculate the distance in cm.
  //Sound travels approx.0.0343 microseconds per cm.,
  // and it's going to the target and back (hence the /2):
  int distance = (duration * 0.0343) / 2;
  Serial.println(distance);

  if (distance < 600) {                 // If the pushbutton is pressed...
    tone(speaker, htz);                      // Sound on
    delay(high);                             // Length of tone
    noTone(speaker);                         // Sound off
    delay(low);                              // Time until next tone
  } else {
    noTone(speaker);  // No tone if the button is released
  }

  // a short delay between readings:
  // delay(10);
}