int greenLED = 9;
int redLED = 10;
int sensor = A0;
int timesUp = 10000;
long starting = 0;
long countDown = 0;
boolean LEDOn = false;
boolean blinking = false;

void setup() {
  Serial.begin(9600);
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
}

void loop() {
  int reading = analogRead(sensor);
  Serial.println(reading);
  delay(10);
  if (reading <= 600 || blinking == true) {
    digitalWrite(greenLED, LOW);
    LEDOn = false;
  }
  if (blinking == false || reading <= 600) {
    digitalWrite(redLED, LOW);
    LEDOn = false;
    blinking = false;
  }
  if (reading > 600 && blinking == false) {
    digitalWrite(greenLED, HIGH);
    LEDOn = true;
    blinking = false;
  }
  if (LEDOn == true && millis() - starting > timesUp) {
    digitalWrite(greenLED, LOW);
    delay(100);
    digitalWrite(greenLED, HIGH);
    delay(100);
    starting = millis();
    blinking = true;
    LEDOn = true;
  }
  if ( blinking == true && micros() - countDown > 2*timesUp) {
    digitalWrite(redLED, HIGH);
    countDown = micros();
    LEDOn = false;
  }
}
