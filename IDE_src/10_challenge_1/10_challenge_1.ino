/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/faq/how-to-control-speed-of-servo-motor
 */

#include <Servo.h>

#define PIN_SERVO 10

Servo myServo;
unsigned long MOVING_TIME = 3000; // moving time is 3 seconds
unsigned long moveStartTime;
int startAngle = 30; // 30°
int stopAngle  = 90; // 90°
float startX = -6.0;
float endX = 6.0;


float Sigmoid(float x){
  return 1 / (1 + exp(-x));
}

float MapForFloat(float x, float in_min, float in_max, float out_min, float out_max){
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void setup() {
  myServo.attach(PIN_SERVO);
  moveStartTime = millis(); // start moving

  myServo.write(startAngle); // Set position
  delay(500);
}

void loop() {
  unsigned long progress = millis() - moveStartTime;

  if (progress <= MOVING_TIME) {
    float sigX = MapForFloat(progress, 0, MOVING_TIME, startX, endX);
    float sigY = Sigmoid(sigX);
    float angle = MapForFloat(sigY, 0, 1, startAngle, stopAngle);
    myServo.write(angle); 
  }
}
