#define PIN_LED 7
#define PERIOD 10000

int _period;
int _duty;

unsigned long nextLoopTime;

int brightness = 0;
int deltaTime = 30;
float fadeAmount = (101 * deltaTime) / 500.0;

void set_period(int period){
  _period = period;
}

void set_duty(int duty){
  _duty = duty;
}

void PWM(){
  digitalWrite(PIN_LED, 0);
  delayMicroseconds(_period * (_duty / 100.0));
  digitalWrite(PIN_LED, 1);
  delayMicroseconds(_period * ((100 - _duty) / 100.0));
}

void setup() {
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(115200);
  while(!Serial){
    ;
  }
  Serial.println(fadeAmount);
  set_period(PERIOD);
  set_duty(brightness);
  nextLoopTime = millis() + deltaTime;
}

void loop() {
  if(nextLoopTime <= millis()){
    set_duty(brightness);
    brightness = brightness + fadeAmount;
    if(brightness <= 0){
      Serial.println("BrightNess == 0");
      brightness = 0;
      fadeAmount = -fadeAmount;
    }
    if(brightness >= 100){
      Serial.println("BrightNess == 100");
      brightness = 100;
      fadeAmount = -fadeAmount;
    }
    nextLoopTime = millis() + deltaTime;
  }
  PWM();
}
