#define PIN_LED 7

int ReverseToggle(int toggle){
  return !toggle;
}

void setup() {
  pinMode(7, OUTPUT);
  Serial.begin(115200);
  while(!Serial){
    ;
  }
  int blinkPerSec = 5, toggle = 0;

  Serial.println("Start.");
  digitalWrite(PIN_LED, toggle);
  delay(1000);

  for(int i = 0;i<blinkPerSec * 2 + 1;i++){
    toggle = ReverseToggle(toggle);
    digitalWrite(PIN_LED, toggle);
    delay(1000 / (blinkPerSec * 2 + 1));
  }

  Serial.println("Done.");
}

void loop() {
  

}
