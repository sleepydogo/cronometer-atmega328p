/*
 * Basic LED Control Example
 * Simple program to control LEDs on PORTB
 */

#include <avr/io.h>

int main(void)
{
  // Configure PORTB as output
  DDRB = 0xFF;

  // Turn on all LEDs
  PORTB = 0xFF;

  while (1) {
    // Main loop
  }
}

