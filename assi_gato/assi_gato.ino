#include "robot.h"
#include "program.h"

robot assi_gato;

void noop(robot* robot, program::action_args_t args) { }

void set_eye_color(robot* robot, program::action_args_t args) {
  robot->left_eye.set(args.i1, args.i2, args.i3, args.speed);
  robot->right_eye.set(args.i1, args.i2, args.i3, args.speed);
}

void right_arm(robot* robot, program::action_args_t args) {
  robot->right_arm.set(args.i1, args.speed);
}

void left_arm(robot* robot, program::action_args_t args) {
  robot->left_arm.set(args.i1, args.speed);
}

void torso(robot* robot, program::action_args_t args) {
  robot->torso.set(args.i1, args.speed);
}

void head(robot* robot, program::action_args_t args) {
  robot->head.set(args.i1, args.speed);
}


void change_pattern(robot* robot, program::action_args_t args) {
  static int i = 0;
  uint8_t
    pat1[] = {B1100, B1100, B0011, B0011, B1100, B1100, B0011, B0011},
    pat2[] = {B0011, B0011, B1100, B1100, B0011, B0011, B1100, B1100};

  if (i++ % 2 == 0)
    robot->chest.set(pat1);
  else
    robot->chest.set(pat2);
}

void move_arms(robot* robot, program::action_args_t args) {
  static int i = 0;

  if (i++ % 2 == 0) {
    robot->right_arm.set(100);
    robot->left_arm.set(-100);
  } else {
    robot->right_arm.set(-100);
    robot->left_arm.set(100);
  }
}

void wiggle_torso(robot* robot, program::action_args_t args) {
  static int i = 0;

  if (i % 3 == 0)
    robot->torso.set(-100);
  else if (i % 3 == 1)
    robot->torso.set(100);
  else
    robot->torso.set(0);

  i++;
}

void move_head(robot* robot, program::action_args_t args) {
  static int i = 0;

  if (i++ % 2 == 0)
    robot->head.set(25);
  else
    robot->head.set(0);
}

void burp(robot* robot, program::action_args_t args) {
  robot->voice.tone(80, 500);
}

void blue_eyes(robot* robot, program::action_args_t args) {
  robot->left_eye.set(0, 100, 100);
  robot->right_eye.set(0, 100, 100);
}

void toggle_wink(robot* robot, program::action_args_t args) {
  static int i = 0;

  if (i++ % 2 == 0)
    robot->left_eye.set(0, 0, 0);
  else
    robot->left_eye.set(0, 100, 100);
}

program::program_t eat = {
  {0, &blue_eyes, 0},

  {500, &change_pattern, 0},
  {1000, &change_pattern, 0},
  {1000, &move_arms, 0},

  {1500, &change_pattern, 0},
  {2000, &change_pattern, 0},
  {2000, &move_arms, 0},

  {2500, &change_pattern, 0},
  {3000, &change_pattern, 0},
  {3000, &move_arms, 0},

  {3500, &change_pattern, 0},
  {4000, &change_pattern, 0},
  {4000, &move_arms, 0},

  {4500, &change_pattern, 0},
  {5000, &change_pattern, 0},
  {5000, &move_arms, 0},

  {5500, &change_pattern, 0},
  {6000, &change_pattern, 0},
  {6000, &move_arms, 0},
  
  {7000, &burp, 0},

  {8000, &move_head, 0},
  {8500, &toggle_wink, 0},
  {9000, &toggle_wink, 0},
  {9500, &move_head, 0},

  {10000, &wiggle_torso, 0},
};

program p(&assi_gato, eat, PROGRAM_LENGTH(eat));


program::program_t pulse_eyes = {
  {0, &set_eye_color, {100, 0, 300, 300}},
  {10, &set_eye_color, {1, 0, 100, 100}},
  {1000, &noop},
};

//program p(&assi_gato, dance, PROGRAM_LENGTH(dance));

void setup() {
  Serial.begin(9600);
  assi_gato.setup();
}

void loop() {
  if (p.done())
    p.start();
    
  p.step();
  assi_gato.step();
}
