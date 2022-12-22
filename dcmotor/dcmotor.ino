const int motor1Pin = 3;  // Motor driver leg 1 (pin 3, AIN1)
const int motor2Pin = 4;  // Motor driver leg 2 (pin 4, AIN2)
const int pwmPin = 5;     // Motor driver PWM pin

void setup() {
  // set all the other pins you're using as outputs:
  pinMode(motor1Pin, OUTPUT);
  pinMode(motor2Pin, OUTPUT);
  pinMode(pwmPin, OUTPUT);

  // set PWM enable pin high so that motor can turn on:
  digitalWrite(pwmPin, HIGH);
}

void loop() {
  digitalWrite(motor1Pin, HIGH);  // set leg 1 of the motor driver high
  digitalWrite(motor2Pin, LOW);   // set leg 2 of the motor driver low
}