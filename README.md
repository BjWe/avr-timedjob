# avr-timedjob
Timed code execution of procedures.

Need **Timer1** to run. (Compare Match A)

### Basic usage
1. include timedjob.h
2. initialize timedjob
3. add jobs

### Config
- You'll have to make sure that TIMER1 COMP_A matches every 100ms.
- This is a basic example:
- #define `TIMER1_PRESCALER`  0x03
- #define `TIMER1_COMPA_VAL`  0x61A7  (for 16MHz)
- #define `TIMER1_COMPA_VAL`  0x30D3  (for 8MHz)
- (This should work for most setups)
- For other frequencies: value = (freq / 10 / prescaler) - 1
- Example for 4MHz: (4000000 / 10 / 64) - 1 = 6249 = 0x1869

### Examles
- See examples directory

### Todo's
- Add compiler directives for AVR registers
(TIMSK1 / TIMSK are not present on every µC)