void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(12, OUTPUT);
  
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);
}

void loop() {
  int pressed;
  if (Serial.read()) {
    int F1 = analogRead(A0);
    int F2 = analogRead(A1);
    int F3 = analogRead(A2);
    int F4 = analogRead(A3);
    int F5 = analogRead(A4);
    int F6 = analogRead(A5);
    int F7 = analogRead(A6);
    int F8 = analogRead(A7);
    analogWrite(12, 100);

    if (F1 > 200) {
      Serial.print(F1);  // print sensor output 1
      pressed = 0;
    } else if (F2 > 200) {
      Serial.print(F2);
      pressed = 1;
    } else if (F3 > 200) {
      Serial.print(F3);
      pressed = 2;
    } else if (F4 > 200) {
      Serial.print(F4);
      pressed = 3;
    } else if (F5 > 750) {
      Serial.print(F5);
      pressed = 4;
    } else if (F6 > 850) {
      Serial.print(F6);
      pressed = 5;
    } else if (F7 > 750) {
      Serial.print(F7);
      pressed = 6;
    }  else if (F8 > 500) {
      Serial.print(F8);
      pressed = 7;
    } 

    if (pressed) {
      Serial.print(",");
      Serial.println(pressed);
    }
  }

  delay(100);  // arbitrary delay to limit data to serial port
}