#include <Servo.h>
#define PIN_SERVO 10

Servo myservo;

int angle[5] = {0,90,180,90,0};

void setup() {
  myservo.attach(PIN_SERVO); 
  myservo.write(90);
  delay(1000);
}

void loop() {
    for(int i = 0;i<5;i++){
      myservo.write(angle[i]);
      delay(500);
    }
}
