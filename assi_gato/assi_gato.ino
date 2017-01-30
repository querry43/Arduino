#include "program.h"
#include "robot.h"

void setup() {
  Serial.begin(9600);
  Serial.println("BEGIN");

  program::setup();
  robot::setup();
}

program::program_t rest = {
  {0, &robot::right_arm, -100},
  {0, &robot::left_arm, -100},
  {0, &robot::head, 0},
  {0, &robot::left_eye, 1},
  {0, &robot::right_eye, 1},
};

program::program_t eat = {
  {1000, &robot::display_pattern, 1},
  {1000, &robot::right_arm, -100},
  {1000, &robot::left_arm, 100},

  {2000, &robot::display_pattern, 2},
  {2000, &robot::right_arm, 100},
  {2000, &robot::left_arm, -100},
};

program::program_t burp = {
  {1000, &robot::play_tone, 80},
  {1500, &robot::stop_tone, 0},

  {2000, &robot::noop, 0},
};

void loop() {
  RUN_PROGRAM(rest);

  while (true) {
    for (int i = 0; i < 3; i++)
      RUN_PROGRAM(eat);
    RUN_PROGRAM(burp);
  }
}
