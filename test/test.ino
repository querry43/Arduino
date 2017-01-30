#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();


void setup() {
  Serial.begin(9600);
  Serial.println("BEGIN");

  pwm.begin();
  pwm.setPWMFreq(60);

  pinMode(13, OUTPUT);
  //digitalWrite(13, HIGH);

  yield();
}

void loop() {
  pwm.setPWM(0, 0, 600);
  digitalWrite(13, LOW);
  delay(500);
  digitalWrite(13, HIGH);
  delay(500);
}
