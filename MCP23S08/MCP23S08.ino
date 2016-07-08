#include <SPI.h>

const int slaveSelectPin = 10;

#define IODIR 0x00
#define GPIO 0x09

void send(uint8_t address, uint8_t data) {
  // 01000 + hardware address + R/W
  // 01000 + 00 + 0
  uint8_t opcode = 0b01000000;

  digitalWrite(slaveSelectPin, LOW);

  SPI.transfer(opcode);
  SPI.transfer(address);
  SPI.transfer(data);

  digitalWrite(slaveSelectPin, HIGH);
}

void setup() {
  pinMode (slaveSelectPin, OUTPUT);
  SPI.begin();
  send(IODIR, 0x00); // all outputs
}

void loop() {
  send(GPIO, 0b01);
  delay(200);
  send(GPIO, 0);

  delay(1000);

  send(GPIO, 0b10);
  delay(200);
  send(GPIO, 0);

  delay(1000);
}
