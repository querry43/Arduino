#pragma once

#include "program.h"
  
namespace robot {
  void setup() {
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);

    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
  }

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
};






/*

namespace eyes {
  // max intensity = 4095
  void leftEye(int red, int green, int blue) {
    pwm.setPWM(4, 0, red);
    pwm.setPWM(5, 0, green);
    pwm.setPWM(6, 0, blue);
  }
  
  void rightEye(int red, int green, int blue) {
    pwm.setPWM(8, 0, red);
    pwm.setPWM(9, 0, green);
    pwm.setPWM(10, 0, blue);
  }
  
  void green() {
    leftEye(0, 128, 32);
    rightEye(0, 128, 32);
  }
  
  void purple() {
    leftEye(128, 0, 128);
    rightEye(128, 0, 128);
  }
  
  void red() {
    leftEye(128, 0, 0);
    rightEye(128, 0, 0);
  }
  
  void blue() {
    leftEye(0, 0, 128);
    rightEye(0, 0, 128);
  }
}
*/
