/*
File: interruptSetupFunctions
Author(s): Chase Robinson
Purpose:
  Functions that run once in setup to configure
  timers and gpio pins to be used as interrupts.
*/

// buttons
void setupButton0(){
  noInterrupts();
  pinMode(button0Pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(button0Pin), button0Flagged, FALLING);

  interrupts();
}
///-----------------------------
//Timers

/*
Sets up Timer2 to run the interrupt to do
cubeCycle every millisecond.

Source: ATmega328P Datasheet
*/
void setupTimer2(){
  // Disable interrupts during setup
  noInterrupts(); // could also use cli()

  // Reset Timer2 control registers
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2  = 0;

  // Set compare match register for 1ms interval
  // Clock = 16 MHz, Prescaler = 64
  // Tick = 4 us → 1 ms = 250 ticks -> OCR2A = 249
  OCR2A = 249;

  // Set Timer2 to CTC (Clear Timer on Compare Match) mode
  TCCR2A |= (1 << WGM21);

  // Set prescaler to 64: CS22=1, CS21=0, CS20=0
  TCCR2B |= (1 << CS22);

  // Enable Timer2 compare match A interrupt
  TIMSK2 |= (1 << OCIE2A);

  // Re-enable interrupts
  interrupts(); // same as using sei()
}

/*
Sets up Timer1 for the dht reading interrupt every 2 seconds

Source: ATmega328P Datasheet
*/
void setupTimer1(){
  noInterrupts(); // Disable interrupts

  // Clear Timer1 control registers
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

  /*
    a 200ms interval:
    - Clock = 16 MHz
    - Use prescaler = 1024 -> tick = 64 us
    - 200 ms = 200,000 us
    - Ticks needed = 200,000 / 64 = 3125

    OCR1A = 3125 - 1 = 3124
  */
  // original wasn't sufficient, so OCR1A = (3125*10 - 1) = 31249
  OCR1A = 31249; //for 2 seconds

  // Set CTC mode (Clear Timer on Compare Match)
  TCCR1B |= (1 << WGM12);

  // Set prescaler to 1024: CS12=1, CS11=0, CS10=1
  TCCR1B |= (1 << CS12) | (1 << CS10);

  // Enable Timer1 Compare Match A interrupt
  TIMSK1 |= (1 << OCIE1A);

  interrupts(); // Re-enable global interrupts
}
//