#include <Servo.h>

Servo servo;
int light_sensor_pin = A0;
int light_threshold = 400;
int pos = 0;

void setup() {
  Serial.begin(9600);
  pinMode(light_sensor_pin, INPUT);
  servo.attach(13);
  servo.write(90);
}

void loop() {
  int light_level = analogRead(light_sensor_pin);

  if (light_level < light_threshold) {
    servo.write(0);
    pos++;
  } else if (pos > 0) {
    servo.write(180);
    pos--;
  } else {
    servo.write(90)
  }

  Serial.print("pos: ");
  Serial.print(pos);
  Serial.print(" sensor: ");
  Serial.print(light_level < light_threshold);
  Serial.print(" (");
  Serial.print(light_level);
  Serial.println(")");
}
