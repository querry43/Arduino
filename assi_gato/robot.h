#pragma once

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

class robot {
public:
  robot();
  void setup();
  void step();

  static Adafruit_PWMServoDriver pwm;

private:
  class servo {
  public:
    servo(int channel, int min, int max);
    void setup();
    void step();
    void set(int target, int speed = 100);
    int get();

  private:
    int _channel, _min, _max;
    int _current, _target, _speed;
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
    head_range = 120;

public:
  servo
    left_arm,
    right_arm,
    head;

  rgb_led
    right_eye,
    left_eye;

  led_grid
    chest;

  speaker
    voice;
};




/*

namespace robot {
  const uint8_t speaker = 9;

  const uint8_t
    dclock1 = 2, ddata1 = 3,
    dclock2 = 4, ddata2 = 5;

  void play_tone(program::action_args_t freq) {
    tone(9, freq);
  }

  void stop_tone(program::action_args_t freq) {
    noTone(9);
  }

  void display_pattern(program::action_args_t pattern) {
    switch (pattern) {
      case 0:
        shiftOut(ddata1, dclock1, LSBFIRST, 0);
        shiftOut(ddata1, dclock1, LSBFIRST, 0);
        shiftOut(ddata2, dclock2, LSBFIRST, 0);
        shiftOut(ddata2, dclock2, LSBFIRST, 0);
        break;

      case 1:
        shiftOut(ddata1, dclock1, LSBFIRST, B11001100);
        shiftOut(ddata1, dclock1, LSBFIRST, B00110011);
        shiftOut(ddata2, dclock2, LSBFIRST, B11001100);
        shiftOut(ddata2, dclock2, LSBFIRST, B00110011);
        break;

      case 2:
        shiftOut(ddata1, dclock1, LSBFIRST, B00110011);
        shiftOut(ddata1, dclock1, LSBFIRST, B11001100);
        shiftOut(ddata2, dclock2, LSBFIRST, B00110011);
        shiftOut(ddata2, dclock2, LSBFIRST, B11001100);
        break;
    }
  }

  void setup() {
    // spare ground for speaker
    pinMode(8, OUTPUT);
    digitalWrite(8, LOW);

    pinMode(speaker, OUTPUT);

    pinMode(dclock1, OUTPUT);
    pinMode(ddata1, OUTPUT);
    pinMode(dclock2, OUTPUT);
    pinMode(ddata2 , OUTPUT);

    display_pattern(0);
  }
};
*/
