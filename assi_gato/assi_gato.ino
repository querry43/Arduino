#include "robot.h"
#include "program.h"

robot assi_gato;

void doit(program::action_args_t) { }

program::program_t rest = {
  {0, &doit, 0},
};

program p(&assi_gato, rest, PROGRAM_LENGTH(rest));

void setup() {
  Serial.begin(9600);

  assi_gato.setup();

  uint8_t pat1[] = {B1000, B0100, B0010, B0001, B0001, B0010, B0100, B1000};
  assi_gato.chest.set(pat1);

  p.start();
}



void loop() {
  p.step();
  assi_gato.step();
  delay(10);
}
