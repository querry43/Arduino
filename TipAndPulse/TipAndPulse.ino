#include <Ports.h>
#include <avr/interrupt.h>

const int pinLed = 4;
const int pinButton = 3;

// 2460ms pulse
const int pulseDelay = 30;
const int fadeChangeRate = 5;

// 5 minutes
const int numPulses = 24 * 5;

int numRemainingPulses = 0;

#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

void setup() {
  pinMode(pinLed, OUTPUT);
  installInterrupt();
}

void loop() {
  activateLedPulses();
  Sleepy::powerDown();
}

void activateLedPulses() {
  while (numRemainingPulses > 0) {
    if (digitalRead(pinButton) == LOW) numRemainingPulses--;
    pulseLed();
  }
  digitalWrite(pinLed, LOW);
}

void pulseLed() {
  for(int fadeValue = 50 ; fadeValue <= 255; fadeValue += fadeChangeRate) { 
    analogWrite(pinLed, fadeValue);         
    delay(pulseDelay);                            
  }
  for(int fadeValue = 255 ; fadeValue >= 50; fadeValue -= fadeChangeRate) { 
    analogWrite(pinLed, fadeValue);         
    delay(pulseDelay);                            
  }
}

void installInterrupt() {
  sbi(PCMSK, pinButton);
  sbi(GIMSK, PCIE);
}

ISR(PCINT0_vect) {
  numRemainingPulses = numPulses;
}
