# ATmega328P Digital Stopwatch

A collection of progressive examples demonstrating digital display control and stopwatch functionality using the ATmega328P microcontroller.

## Overview

This project showcases embedded programming techniques for the ATmega328P, featuring:
- 7-segment display control
- Multi-digit multiplexing
- Button debouncing algorithms
- Real-time counter implementation
- Start/Stop/Reset functionality

## Hardware Requirements

- ATmega328P microcontroller
- 4x 7-segment common cathode displays
- Push buttons (for examples 2 and 4)
- Current-limiting resistors
- 16MHz crystal oscillator
- Power supply (5V)

## Project Structure

```
cronometer-atmega328p/
├── examples/
│   ├── 01-basic-led/          # Basic LED control on PORTB
│   ├── 02-single-digit-counter/  # Button-controlled 0-9 counter
│   ├── 03-multi-digit-display/   # 4-digit auto-incrementing counter
│   └── 04-stopwatch/          # Full stopwatch with start/stop/reset
├── proteus/                   # Proteus simulation files
└── README.md
```

## Examples

### 01 - Basic LED Control
Simple demonstration of GPIO output configuration and LED control using PORTB.

**Features:**
- Port configuration
- Basic output control
- Foundation for display control

### 02 - Single Digit Counter
Button-controlled counter displaying values 0-9 on a single 7-segment display.

**Features:**
- 7-segment display encoding
- Button input with debouncing
- Modular display update function

### 03 - Multi-Digit Display
Auto-incrementing counter (0-9999) using display multiplexing to control four 7-segment displays.

**Features:**
- 4-digit multiplexing technique
- Digit decomposition algorithm
- Persistence of vision display

### 04 - Digital Stopwatch
Complete stopwatch implementation with start, stop, and reset functionality.

**Features:**
- Time measurement (hundredths to tens of seconds)
- Three-button control (START/STOP/RESET)
- Advanced debouncing algorithm
- State machine implementation

**Pin Configuration:**
- PORTB[0-6]: 7-segment display segments
- PORTB[7]: RESET button (input)
- PORTC[0-3]: Digit selection (multiplexing)
- PORTC[4]: START button (input)
- PORTC[5]: STOP button (input)

## Building and Flashing

### Using AVR-GCC

```bash
# Navigate to desired example
cd examples/04-stopwatch

# Compile
avr-gcc -mmcu=atmega328p -DF_CPU=16000000UL -Os -o stopwatch.elf stopwatch.c -lm

# Create hex file
avr-objcopy -O ihex -R .eeprom stopwatch.elf stopwatch.hex

# Flash to microcontroller
avrdude -c usbasp -p atmega328p -U flash:w:stopwatch.hex
```

### Using Atmel Studio

1. Open the `.cproj` file in Atmel Studio
2. Build the project (F7)
3. Program the device (Ctrl+Alt+F5)

## Simulation

Proteus simulation files are included in the `proteus/` directory. Each example has a corresponding `.pdsprj` file that can be opened with Proteus Design Suite.

## Technical Details

### 7-Segment Display Encoding

The segment mapping follows standard 7-segment display configuration:

```
 Bit:  6 5 4 3 2 1 0
Segment: G F E D C B A

  AAA
 F   B
  GGG
 E   C
  DDD
```

### Debouncing Algorithm

The stopwatch example implements a robust debouncing algorithm using circular buffers:
- 5-sample moving average
- Button must be stable for 5 consecutive reads
- Prevents false triggering from mechanical bounce

### Multiplexing Technique

The multi-digit examples use time-division multiplexing:
- Each digit is activated sequentially
- Display refresh rate: ~100Hz (2.5ms per digit × 4 digits)
- Creates illusion of all digits being simultaneously lit

## Code Structure

All examples follow clean coding practices:
- Clear function naming
- Comprehensive comments
- Modular design
- Consistent formatting

## Applications

This codebase can be adapted for:
- Digital clocks
- Kitchen timers
- Sports timing systems
- Industrial counters
- Educational demonstrations

## Contributing

Contributions are welcome! Areas for enhancement:
- Additional display patterns
- Interrupt-driven timing
- EEPROM state persistence
- Alarm functionality
- Multiple timing modes

## Collaborators

- Tomas E. Schattmann
- Mariano A. Rodriguez Mesa

## License

This project is open source and available under the MIT License.

## Resources

- [ATmega328P Datasheet](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf)
- [AVR Libc Documentation](https://www.nongnu.org/avr-libc/)
- [7-Segment Display Tutorial](https://www.electronics-tutorials.ws/blog/7-segment-display-tutorial.html)

---

Built with ATmega328P and AVR-GCC
