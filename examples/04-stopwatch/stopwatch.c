/*
 * Digital Stopwatch with Start/Stop/Reset
 * 4-digit display showing centiseconds to tens of seconds
 * Features: Start, Stop, Reset buttons with debouncing
 */

#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <math.h>

// Control bit masks for digit selection
const uint8_t display[] = {
  0b0001000, // Tens of seconds
  0b0000100, // Seconds
  0b0000010, // Tenths of seconds
  0b0000001, // Hundredths of seconds
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

// State variables
// uni: time units (increments every 10ms)
// aux: temporary copy for division/modulo operations
// stop: 1 = stopped, 0 = running
// reset: 1 = reset counter to zero
uint16_t uni = 0, aux = 0, stop = 1, reset = 0;

// Debounce control arrays
uint8_t debounceStart[] = {0, 0, 0, 0, 0};
uint8_t debounceStop[] = {0, 0, 0, 0, 0};
uint8_t debounceReset[] = {0, 0, 0, 0, 0};

// Display a value on digit n
void updateDisplay(int value, int ndigit)
{
  PORTB = segment_map[value % 10];
  PORTC = display[ndigit];
}

// Display all digits and optionally increment counter
// count: if 1, increment time units; if 0, just display current value
void showDigits(uint8_t count)
{
  aux = uni;
  for (int i = 0; i <= 3; i++)
  {
    updateDisplay(aux % 10, i);
    _delay_ms(2.5);
    if (i != 3)
    {
      aux = uni / (pow(10, i + 1));
    }
  }
  if (count == 1)
  {
    uni++;
  }
}

// Check if button on PINX_X of port PINX is pressed
int checkButton(uint8_t PINX, uint8_t PINX_X)
{
  if ((PINX & (1 << PINX_X)) == 0)
  {
    return 0;
  }
  return 1;
}

// Handle button presses with debouncing
// value: index [0-4] used circularly for debounce arrays
// If sum equals 5, button has been pressed long enough (not a bounce)
void buttonControl(uint8_t value)
{
  int totalStop = 0, totalReset = 0, totalStart = 0;

  // Read button states
  debounceStart[value] = checkButton(PINC, PINC4); // START button
  debounceStop[value] = checkButton(PINC, PINC5);  // STOP button
  debounceReset[value] = checkButton(PINB, PINB7); // RESET button

  // Sum debounce arrays
  for (int i = 0; i < 5; i++)
  {
    totalStart += debounceStart[i];
    totalStop += debounceStop[i];
    totalReset += debounceReset[i];
  }

  // START button logic
  if (totalStart == 5)
  {
    while (checkButton(PINC, PINC4) == 1);
    for (int i = 0; i < 5; i++)
    {
      debounceStart[i] = 0;
      debounceStop[i] = 0;
    }
    stop = 0;
  }

  // STOP button logic
  if (totalStop == 5)
  {
    for (int i = 0; i < 5; i++)
    {
      debounceStop[i] = 0;
    }
    stop = 1;
  }

  // RESET button logic
  if (totalReset == 5)
  {
    while (checkButton(PINB, PINB7) == 1);
    for (int i = 0; i < 5; i++)
    {
      debounceStop[i] = 0;
    }
    reset = 1;
    stop = 1;
    uni = 0;
  }
}

int main(void)
{
  // Configure ports
  DDRB = 0x7F; // PORTB: pins 0-6 output (segments), pin 7 input (button)
  DDRC = 0x0F; // PORTC: pins 0-3 output (digit control), pins 4-5 input (buttons)
  PORTB = segment_map[uni];
  uint8_t controlValue = 0; // Circular counter for buttonControl()

  while (1)
  {
    // Running state: display and increment counter
    while (stop == 0)
    {
      showDigits(1);
      buttonControl(uni % 5);
    }

    // Stopped state: display current value without incrementing
    while (stop == 1)
    {
      if (controlValue == 6) {
        controlValue = 0;
      }
      showDigits(0);
      buttonControl(controlValue);
      controlValue++;
    }
  }
}