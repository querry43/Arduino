#pragma once

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define PROGRAM_LENGTH(p) sizeof(p) / sizeof(program::command_t)
#define RUN_PROGRAM(p) {\
  Serial.println(); \
  Serial.print("Executing "); \
  Serial.print(#p); \
  Serial.print( " with "); \
  Serial.print(PROGRAM_LENGTH(p)); \
  Serial.println(" commands"); \
  program::run(p, PROGRAM_LENGTH(p)); \
}


namespace program {
  Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

  typedef int8_t action_args_t;

  typedef void (*action_t)(int8_t);

  struct command_t {
    unsigned long time;
    action_t action;
    action_args_t args;
  };

  typedef command_t program_t[];

  void setup() {
    pwm.begin();
    pwm.setPWMFreq(60);
  }

  void run(program_t program, uint32_t num_commands) {
    Serial.println("now:time:command");

    uint32_t i = 0;
    unsigned long start = millis();
    while (true) {
      unsigned long now = millis();
      if (now - start >= program[i].time) {
        Serial.print(now);
        Serial.print(":");
        Serial.print(program[i].time);
        Serial.print(":");
        Serial.println(i);

        (*program[i].action)(program[i].args);
        i++;
      }
      if (i == num_commands)
        break;
    }
  }
}
