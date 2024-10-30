#include <Servo.h>

// Arduino pin assignment

#define PIN_IR    0         // IR sensor at Pin A0
#define PIN_LED   9
#define PIN_SERVO 10

#define _DUTY_MIN 550   // servo full clock-wise position (0 degree)
#define _DUTY_NEU 1000  // servo neutral position (90 degree)
#define _DUTY_MAX 2400  // servo full counter-clockwise position (180 degree)

#define _DIST_MIN  100.0   // minimum distance 100mm
#define _DIST_MAX  250.0   // maximum distance 250mm

#define EMA_ALPHA  0.5      // for EMA Filter

#define LOOP_INTERVAL 40   // Loop Interval (unit: msec)

Servo myservo;
unsigned long last_loop_time;   // unit: msec

float dist_prev = _DIST_MIN;
float dist_ema = _DIST_MIN;

float FilterOfEMA(float raw, float alpha){
  return (alpha * raw) + ((1 - alpha) * dist_prev);
}

float FloatMap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void setup()
{
  pinMode(PIN_LED, OUTPUT);
  
  myservo.attach(PIN_SERVO); 
  myservo.writeMicroseconds(_DUTY_NEU);
  
  Serial.begin(1000000);    // 1,000,000 bps
}

void loop()
{
  unsigned long time_curr = millis();
  int duty;
  float a_value, dist_raw;

  // wait until next event time
  if (time_curr < (last_loop_time + LOOP_INTERVAL))
    return;
  last_loop_time += LOOP_INTERVAL;

  a_value = analogRead(PIN_IR);
  dist_raw = ((6762.0 / (a_value - 9.0)) - 4.0) * 10.0;

  if (dist_raw < _DIST_MIN) dist_raw = _DIST_MIN - 10;
  if (dist_raw > _DIST_MAX) dist_raw = _DIST_MAX + 10;
  // Put range Filter code here (_DIST_MIN ~ _DIST_MAX)
  if (_DIST_MIN <= dist_raw && dist_raw <= _DIST_MAX) {
    digitalWrite(9, 0);
  } else digitalWrite(9, 1);
  // and turn on LED if the distance is in the range 

  dist_ema = FilterOfEMA(dist_raw, EMA_ALPHA);
  dist_prev = dist_ema;
      
  //duty = map(dist_ema, _DIST_MIN, _DIST_MAX, _DUTY_MIN, _DUTY_MAX);
  duty = FloatMap(dist_ema, _DIST_MIN, _DIST_MAX, _DUTY_MIN, _DUTY_MAX);
  
  myservo.writeMicroseconds(duty);

  Serial.print("_DUTY_MIN:");  Serial.print(_DUTY_MIN);
  Serial.print("_DIST_MIN:");  Serial.print(_DIST_MIN);
  Serial.print(",IR:");        Serial.print(a_value);
  Serial.print(",dist_raw:");  Serial.print(dist_raw);
  Serial.print(",ema:");       Serial.print(dist_ema);
  Serial.print(",servo:");     Serial.print(duty);
  Serial.print(",_DIST_MAX:"); Serial.print(_DIST_MAX);
  Serial.print(",_DUTY_MAX:"); Serial.print(_DUTY_MAX);
  Serial.println("");
}
