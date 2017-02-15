#include "robot.h"

Adafruit_PWMServoDriver robot::pwm = Adafruit_PWMServoDriver();

robot::robot() :
    left_arm(servo(1, left_arm_min, left_arm_min + arm_range)),
    right_arm(servo(0, right_arm_min, right_arm_min - arm_range)),
    head(servo(2, head_center - head_range, head_center + head_range)),
    torso(servo(3, torso_center - torso_range, torso_center + torso_range)),
    left_eye(rgb_led(4)),
    right_eye(rgb_led(8)),
    chest(led_grid(2, 3, 4, 5)),
    voice(speaker(9)){ }

void robot::setup() {
  Serial.println("Hello!");
  pwm.begin();
  pwm.setPWMFreq(60);
  left_arm.setup();
  right_arm.setup();
  head.setup();
  torso.setup();
  left_eye.setup();
  right_eye.setup();
  chest.setup();
  voice.setup();

  head.set(0);
  torso.set(0);
  left_eye.set(0, 0, 0);
  right_eye.set(0, 0, 0);
}

void robot::step() {
  left_arm.step();
  right_arm.step();
  head.step();
  torso.step();
  left_eye.step();
  right_eye.step();
}

robot::servo::servo(int channel, int min, int max) : _channel(channel), _min(min), _max(max) { }

void robot::servo::setup() {
  _current = -100;
  _target = -100;
  pwm.setPWM(_channel, 0, _min);
}

void robot::servo::step() {
  if (_current > _target) {
    _current = max(_target, _current - _speed);
  } else if (_current < _target) {
    _current = min(_target, _current + _speed);
  }

  pwm.setPWM(_channel, 0, map(_current, -100, 100, _min, _max));
}

void robot::servo::set(int target, int speed) {
  _target = target;
  _speed = speed;
}

int robot::servo::get() {
  return _current;
}

robot::rgb_led::rgb_led(int channel) : _channel(channel), _color({0,0,0}), _target_color({0,0,0}) { }

void robot::rgb_led::setup() {
  for (int i = 0; i < 3; i++) {
    pwm.setPWM(_channel+i, 0, 0);
  }
}

void robot::rgb_led::step() {
  for (int i = 0; i < 3; i++) {
    if (_color[i] > _target_color[i]) {
      _color[i] = max(_target_color[i], _color[i] - _speed);
    } else if (_color[i] < _target_color[i]) {
      _color[i] = min(_target_color[i], _color[i] + _speed);
    }
    pwm.setPWM(_channel+i, 0, _color[i]);
  }
}

void robot::rgb_led::set(int r, int g, int b, int speed) {
  _target_color[0] = r;
  _target_color[1] = g;
  _target_color[2] = b;
  _speed = speed;
}

robot::led_grid::led_grid(int c1, int d1, int c2, int d2) : _c1(c1), _d1(d1), _c2(c2), _d2(d2) {
  pinMode(_c1, OUTPUT);
  pinMode(_d1, OUTPUT);
  pinMode(_c2, OUTPUT);
  pinMode(_d2, OUTPUT);
}

void robot::led_grid::setup() {
  clear();
}

uint8_t blank[] = {0, 0, 0, 0, 0, 0, 0, 0};
void robot::led_grid::clear() {
  set(blank);
}

void robot::led_grid::set(uint8_t columns[8]) {
  shiftOut(_d1, _c1, LSBFIRST, ~(columns[1] << 4 | columns[0]));
  shiftOut(_d1, _c1, LSBFIRST, ~(columns[3] << 4 | columns[2]));
  shiftOut(_d2, _c2, LSBFIRST, ~(columns[5] << 4 | columns[4]));
  shiftOut(_d2, _c2, LSBFIRST, ~(columns[7] << 4 | columns[6]));
}

robot::speaker::speaker(int pin) : _pin(pin) { }

void robot::speaker::setup() {
  pinMode(_pin, OUTPUT);
}

void robot::speaker::tone(int frequency) {
  ::tone(_pin, frequency);
}

void robot::speaker::tone(int frequency, long duration) {
  ::tone(_pin, frequency, duration);
}

void robot::speaker::noTone() {
  ::noTone(_pin);
}
