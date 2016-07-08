#include "trinket_tone.h"
#include "pitches.h"

void setup() {
 pinMode(1, OUTPUT);
}

void loop() {
  chime();
}

void chime() {
  TrinketTone(NOTE_CS6, 100);
  delay(100);
  TrinketTone(NOTE_GS6, 200);
  delay(200);
  delay(3000);
}

