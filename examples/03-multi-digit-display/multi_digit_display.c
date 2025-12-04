/*
 * Multi-Digit Display Counter
 * 4-digit auto-incrementing counter with multiplexing
 */

#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>

// Counter for 4 digits
uint8_t counter[4] = {0, 0, 0, 0};

// Control bit masks for digit selection
const uint8_t display[] = {
  0b0001000,
  0b0000100,
  0b0000010,
  0b0000001,
};

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

// Time unit variable
int uni = 0;
int aux = 0;

int main(void)
{
  // Configure ports: PORTB for segments, PORTC for digit control
  DDRB = 0xFF;
  DDRC = 0x0F;
  PORTB = segment_map[uni];

  while (1) {
    // Display units digit
    PORTB = segment_map[uni % 10];
    PORTC = 0b00001000;

    // Display tens digit
    aux = uni / 10;
    PORTB = segment_map[aux % 10];
    PORTC = 0b00000100;

    // Display hundreds digit
    aux = uni / 100;
    PORTB = segment_map[aux % 10];
    PORTC = 0b00000010;

    // Display thousands digit
    aux = uni / 1000;
    PORTB = segment_map[aux % 10];
    PORTC = 0b00000001;
    _delay_ms(1);

    // Increment counter
    uni++;
    PORTC = 0b00000000;
  }
}