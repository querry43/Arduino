#pragma once

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

class robot {
public:
  robot();
  void setup();
  void step();

  static Adafruit_PWMServoDriver pwm;
  static float speed_divider;

private:
  class servo {
  public:
    servo(int channel, int min, int max);
    void setup();
    void step();
    void set(int target, int speed = 100);
    int get();
    void idle();

  private:
    int _channel, _min, _max;
    float _current, _target;
    int _speed;
  };

  class rgb_led {
  public:
    rgb_led(int channel);
    void setup();
    void step();
    void set(int r, int g, int b, int speed = 100);

  private:
    int _channel, _speed;
    int _color[3];
    int _target_color[3];
  };

  class led_grid {
  public:
    led_grid(int c1, int d1, int c2, int d2);
    void setup();
    void clear();
    void set(uint8_t columns[8]);
  private:
    int _c1, _d1, _c2, _d2;
  };

  class speaker {
  public:
    speaker(int pin);
    void setup();
    void tone(int frequency);
    void tone(int frequency, long duration);
    void noTone();
  private:
    int _pin;
  };

  const int
    arm_range = 300,
    left_arm_min = 170,
    right_arm_min = 600,
    head_center = 390,
    head_range = 120,
    torso_center = 320,
    torso_range = 120,

    tilt_center = 412, // 365 - 450
    tilt_range = 37;

public:
  servo
    left_arm,
    right_arm,
    head,
    torso,
    tilt;

  rgb_led
    right_eye,
    left_eye;

  led_grid
    chest;

  speaker
    voice;
};
