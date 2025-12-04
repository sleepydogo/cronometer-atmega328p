/*
 * Single Digit Counter with 7-Segment Display
 * Button-controlled counter from 0-9
 */

#include <avr/io.h>
#include <stdint.h>
#define F_CPU 16000000UL
#include <util/delay.h>

// Counter variable
uint8_t counter = 0;

// Bit mapping for 7-segment display

const uint8_t segment_map[] = {
	0b00111111, // 0
	0b00000110, // 1
	0b01011011, // 2
	0b01001111, // 3
	0b01100110, // 4
	0b01101101, // 5
	0b01111101, // 6
	0b00000111, // 7
	0b01111111, // 8
	0b01101111  // 9
};

void update_display() {
  // Get counter value (0-9)
  uint8_t value = counter % 10;
  // Map value to 7-segment pattern
  uint8_t segments = segment_map[value];
  // Output to display
  PORTB = segments;
}

int main(void) {
  // Configure PORTB pins 0-6 as output, pin 7 as input (button)
  DDRB = 0x7F;
  PORTB = segment_map[0];

  while (1) {
    // Check if button is pressed (with debouncing)
    if ((PINB & (1 << PINB7))) {
      _delay_ms(25);
      while((PINB & (1 << PINB7)));
      _delay_ms(25);
      counter++;
      update_display();
    }
  }
}