#include <Servo.h>

// Arduino pin assignment
#define PIN_SERVO 10
#define PIN_IR    A0

#define _DUTY_MIN 550  // servo full clock-wise position (0 degree)
#define _DUTY_NEU 1600 // servo neutral position (90 degree)
#define _DUTY_MAX 2400 // servo full counter-clockwise position (180 degree)

#define _INTERVAL_DIST    20 // distance sensor interval (unit: ms)
#define _INTERVAL_SERIAL  20 // serial interval (unit: ms)

#define _EMA_ALPHA 0.2    // EMA weight of new sample (range: 0 to 1)



Servo myservo;

void setup()
{
  myservo.attach(PIN_SERVO); 
  myservo.writeMicroseconds(_DUTY_NEU);
  
  Serial.begin(57600);
}

void loop(){
  
}
