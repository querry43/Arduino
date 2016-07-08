//
// --------- TTone, a "Trinket" tone generator --------------
//
// Author: Bruce E. Hall <bhall66@gmail.com>
// Date: 29 Dec 2013
// Hardware: Trinket, using AVR ATtiny85
// Software: Arduino 1.0.5
// Size: 2352 bytes
//
// This small application uses Timer1 on the ATtiny85
// to implement a tone generator & play some music.

#include <arduino.h>

volatile uint32_t toggle_count;

void TrinketTone(uint16_t frequency, uint32_t duration)
{
  uint32_t ocr = F_CPU/frequency/2;
  uint8_t prescalarBits = 1;
  while (ocr>255) {
    prescalarBits++;
    ocr /= 2;
  }
 
  TCCR1 = 0x90 | prescalarBits;

  toggle_count = frequency * duration / 500;
  OCR1C = ocr-1; // Set the OCR
  bitWrite(TIMSK, OCIE1A, 1); // enable interrupt
}

ISR(TIMER1_COMPA_vect)
{
  if (toggle_count != 0)
    toggle_count--;
  else
    TCCR1 = 0x90;
}
