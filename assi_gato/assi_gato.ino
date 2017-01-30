#include "program.h"
#include "robot.h"

void setup() {
  Serial.begin(9600);
  Serial.println("BEGIN");

  program::setup();
  robot::setup();

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
}

program::program_t rest = {
  {0, &robot::right_arm, -100},
  {0, &robot::left_arm, -100},
  {0, &robot::head, 0},
};

program::program_t eat = {
  {1000, &robot::right_arm, -100},
  {1000, &robot::left_arm, 100},
  {2000, &robot::right_arm, 100},
  {2000, &robot::left_arm, -100},

  {3000, &robot::right_arm, -100},
  {3000, &robot::left_arm, 100},
  {4000, &robot::right_arm, 100},
  {4000, &robot::left_arm, -100},

  {5000, &robot::right_arm, -100},
  {5000, &robot::left_arm, 100},
  {6000, &robot::right_arm, 100},
  {6000, &robot::left_arm, -100},

  {7000, &robot::play_tone, 80},
  {7500, &robot::stop_tone, 0},

  {8000, &robot::noop, 0},
};

void loop() {
  /*
  program::run(rest, PROGRAM_LENGTH(rest));

  while (true) {
    program::run(eat, PROGRAM_LENGTH(eat));
  }
  */
}
