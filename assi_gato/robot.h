#pragma once

#include "program.h"

namespace robot {
  const uint8_t speaker = 9;

  const uint8_t
    dclock1 = 2, ddata1 = 3,
    dclock2 = 4, ddata2 = 5;

  void noop(program::action_args_t pos) {}

  const int arm_range = 300;
  void right_arm(program::action_args_t pos) {
    int bottom = 600;
    program::pwm.setPWM(0, 0, map(pos, -100, 100, bottom, bottom - arm_range));
  }

  void left_arm(program::action_args_t pos) {
    int bottom = 170;
    program::pwm.setPWM(1, 0, map(pos, -100, 100, bottom, bottom + arm_range));
  }

  void head(program::action_args_t pos) {
    int center = 390;
    int range = 120;
    program::pwm.setPWM(2, 0, map(pos, -100, 100, center-range, center+range));
  }

  void play_tone(program::action_args_t freq) {
    tone(9, freq);
  }

  void stop_tone(program::action_args_t freq) {
    noTone(9);
  }

  void eye(uint8_t base, program::action_args_t color) {
    int red = 0, green = 0, blue = 0;
    switch(color) {
      case 1:
        blue = 128;
        break;
    }

    program::pwm.setPWM(base+0, 0, red);
    program::pwm.setPWM(base+1, 0, green);
    program::pwm.setPWM(base+2, 0, blue);
  }

  void left_eye(program::action_args_t color) { eye(4, color); }
  void right_eye(program::action_args_t color) { eye(8, color); }

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
