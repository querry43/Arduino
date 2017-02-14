#pragma once

#include "robot.h"

#define PROGRAM_LENGTH(p) sizeof(p) / sizeof(program::command_t)

class program {
public:
  typedef int8_t action_args_t;
  typedef void (*action_t)(robot*, action_args_t);

  struct command_t {
    uint64_t time;
    action_t action;
    action_args_t args;
  };

  typedef command_t program_t[];

  program(robot* robot, command_t* program, uint32_t num_commands);
  void start();
  void step();
  bool done();

private:
  robot* _robot;
  command_t* _program;
  uint32_t _num_commands;
  uint32_t _pos;
  unsigned long _start;
};

