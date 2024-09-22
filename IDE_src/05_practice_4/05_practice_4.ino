#define PIN_LED 7
#define PERIOD 10000

int _period;
int _duty;

unsigned long nextLoopTime;

int brightness = 0;
int deltaTime = 30;
int fadeAmount = (101 * deltaTime) / 500;

void set_period(int period){
  _period = period;
}

void set_duty(int duty){
  _duty = duty;
}

void PWM(){
  digitalWrite(PIN_LED, 0);
  delayMicroseconds(_period * (_duty / 100));
  digitalWrite(PIN_LED, 1);
  delayMicroseconds(_period * ((100 - _duty) / 100));
}

void setup() {
  //pinMode(PIN_LED, OUTPUT);
  Serial.begin(115200);
  while(!Serial){
    ;
  }
  Serial.println("Start. d");
  
  set_period(PERIOD);
  nextLoopTime = millis() + deltaTime;

  //set_duty(100);
  digitalWrite(PIN_LED, 0);
}

void loop() {
  if(nextLoopTime > millis()){
    /*
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
    nextLoopTime = millis() + deltaTime;*/
  }
  //PWM();
}
