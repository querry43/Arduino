#include "robot.h"
#include "program.h"

robot assi_gato;

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

void burp(robot* robot, program::action_args_t args) {
  robot->voice.tone(80, 500);
}

void noop(robot* robot, program::action_args_t args) { }


program::program_t toggle_pattern = {
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
  {8000, &noop, 0},
};

program p(&assi_gato, toggle_pattern, PROGRAM_LENGTH(toggle_pattern));

void setup() {
  Serial.begin(9600);
  assi_gato.setup();
}

void loop() {
  if (p.done())
    p.start();
    
  p.step();
  assi_gato.step();
  
  delay(10);
}
