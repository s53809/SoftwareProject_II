#define PIN_LED 7
#define PERIOD 10000

int _period;
int _duty;

void set_period(int period){
  _period = period;
}

void set_duty(int duty){
  _duty = duty;
}

void PWM(int waitTime){ //waitTime: 1 to (unit : ms)
  long timeChecker = 0;
  while(timeChecker < (long)waitTime * 1000){
    digitalWrite(PIN_LED, 0);
    delayMicroseconds(_period * (_duty / 100));
    digitalWrite(PIN_LED, 1);
    delayMicroseconds(_period * ((100 - _duty) / 100));
  }
}
void setup() {
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(115200);
  while(!Serial){
    ;
  }
  Serial.println("Start.");
  
  set_period(PERIOD);
}

int brightness = 0;
int fadeAmount = 0;
int deltaTime = 30;

void loop() {
  
}
