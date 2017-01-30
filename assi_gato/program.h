#pragma once

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define PROGRAM_LENGTH(p) sizeof(p) / sizeof(program::command_t)

namespace program {
  Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

  typedef int8_t action_args_t;
  
  typedef void (*action_t)(int8_t);
  
  struct command_t {
    uint64_t time;
    action_t action;
    action_args_t args;
  };
  
  typedef command_t program_t[];

  void setup() {
    pwm.begin();
    pwm.setPWMFreq(60);
  }
  
  void run(program_t program, uint32_t num_commands) {
    Serial.print("Executing ");
    Serial.print(num_commands);
    Serial.println(" commands");
  
    Serial.println();
    Serial.println("time:command");
  
    uint32_t i = 0;
    unsigned long start = millis();
    while (true) {
      unsigned long now = millis();
      if (now - start >= program[i].time) {
        Serial.print(now);
        Serial.print(":");
        Serial.println(i);
  
        (*program[i].action)(program[i].args);
        i++;
      }
      if (i == num_commands)
        break;
    }
  
    Serial.println();
    Serial.println("Program complete");
  }
}
