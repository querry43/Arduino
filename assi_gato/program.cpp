#include "program.h"

program::program(robot* robot, command_t* program, uint32_t num_commands) : _robot(robot), _program(program), _num_commands(num_commands), _pos(num_commands) { }

void program::start() {
  _start = millis();
  _pos = 0;

  Serial.print("Starting program with ");
  Serial.print(_num_commands);
  Serial.print(" commands at time ");
  Serial.println(_start);
  Serial.println("time:command");
}

void program::step() {
  unsigned long now = millis();

  while (true) {
    if (done())
      return;

    if (now - _start >= _program[_pos].time) {
      Serial.print(now);
      Serial.print(":");
      Serial.println(_pos);
  
      (*_program[_pos].action)(_robot, _program[_pos].args);
  
      _pos++;
    } else {
      break;
    }
  }
}

bool program::done() {
  return _pos >= _num_commands;
}

