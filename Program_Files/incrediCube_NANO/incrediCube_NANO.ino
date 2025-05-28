/*
File: incrediCube_NANO
Author(s): Chase Robinson, Michael Fang
Purpose:
  run a 5x5 LED cube using the Arduino NANO
  development board connected to shift
  registers.
*/

#include "DHT.h"
#define DHT11_PIN 7
#define DHT_TYPE DHT11
DHT dht11(DHT11_PIN, DHT_TYPE);

#define button0Pin 3

// dht value and display variables
int temperature = 0;
int humidity = 0;

int tempNums[] = {0,0};
int humNums[] = {0,0};
//

// interrupt boolean flags to run in main loop
bool readDHTFlag = 0;
bool button0Flag = 0;
//

// shift register pins
const int inputPin = 6;
const int srclk = 5;
const int orclk = 4;
//

// variables for cube display interrupt
bool cubeFlag = 0; // flag set by interrupt
int currentZ = 0; // current Z level to display
//

// Frame Animation Variables
int currentFrame = 0;
int loopCounter = 0;
int loopCounterInitial = loopCounter;

long int currentFrameDelay = 2000; //in cycle
int previousFrame = 0;

int animationOption = 0;
#define maxAnimationOption 6

bool cycleAnimations = 0;
//

// debouncing stuff
const int debounceTime = 3000;
long int timeSincePress = 0;
//

bool cubeMatrix[5][5][5] = {
  {{0, 0, 0, 0, 0},{0, 0, 0, 0, 0},{0, 0, 0, 0, 0},{0, 0, 0, 0, 0},{0, 0, 0, 0, 0}},
  {{0, 0, 0, 0, 0},{0, 0, 0, 0, 0},{0, 0, 0, 0, 0},{0, 0, 0, 0, 0},{0, 0, 0, 0, 0}},
  {{0, 0, 0, 0, 0},{0, 0, 0, 0, 0},{0, 0, 0, 0, 0},{0, 0, 0, 0, 0},{0, 0, 0, 0, 0}},
  {{0, 0, 0, 0, 0},{0, 0, 0, 0, 0},{0, 0, 0, 0, 0},{0, 0, 0, 0, 0},{0, 0, 0, 0, 0}},
  {{0, 0, 0, 0, 0},{0, 0, 0, 0, 0},{0, 0, 0, 0, 0},{0, 0, 0, 0, 0},{0, 0, 0, 0, 0}}
};

bool outputArray[30];
/*
Implementation: ZXY order. 
1st dimension = Z coordinate of the active layer
2nd dimension = X coordinate of the activated column
3rd dimension = Y coordinate of the activated column

Let each register be an X coordinate, with each bit
position on that register (0-4) be a Y coordinate.
*/

/*
setup function description: 
void setup() is responsible for setting up timer control registers,
timer interrupts, and configuring gpio inputs with interrupts.
Furthermore, it initializes the serial monitor, dht11 sensor, and
the pins necessary to control the shift register. Calls functions
to fill the shift register with zeros and turn off all LEDs.
*/
void setup() {
  // set up timer-based & other interrupts
  setupTimer2();
  setupTimer1();
  setupButton0();

  Serial.begin(9600);
  dht11.begin();

  regInit();
  clearShiftRegister(30);
  zeroCubeMatrix();

}


void loop() {
  timeSincePress++;

  //
  if (readDHTFlag){
    readDHTFlag = 0;
    updateDHTValues();
    dhtConvertIntArray();
    Serial.println(temperature*100+humidity);
  }

  // button was pushed, go to next animation
  if (button0Flag){
    button0Flag = 0;
    if (timeSincePress > debounceTime){
      timeSincePress = 0;
      Serial.println("BF");
      animationOption = (animationOption+1)%(maxAnimationOption);
      loopCounter = 0;
      Serial.println(animationOption);
      zeroCubeMatrix();
    }
  }

  
  // switch case selects the current animation to do
  switch(animationOption){
    case 0:
      currentFrameDelay = 5*2000;
      previousFrame++;
      if (previousFrame >= currentFrameDelay){
        previousFrame = 0;
        loopCounter = (loopCounter+1)%125;
        impulseFrame();
      }
    break;
    case 1:
      currentFrameDelay = 1000;
      previousFrame++;
      if (previousFrame >= currentFrameDelay){
        previousFrame = 0;
        droplets(50);
      }
    break;
    case 2:
      currentFrameDelay = 2000;
      previousFrame++;
      if (previousFrame >= currentFrameDelay){
        previousFrame = 0;
        loopCounter = (loopCounter+1)%100;
        displayTemperatureFrame();
      }
    break;
    case 3:
      currentFrameDelay = 2000;
      previousFrame++;
      if (previousFrame >= currentFrameDelay){
        previousFrame = 0;
        loopCounter = (loopCounter+1)%100;
        displayHumidityFrame();
      }
    case 4:
      currentFrameDelay = 10000;
      previousFrame++;
      if (previousFrame >= currentFrameDelay){
        previousFrame = 0;
        loopCounter = (loopCounter+1)%5; //loopCounter will go from 0 to 4 and then back to 0
        displayOscillatingFrame();
      }
    break;
    case 5:
      currentFrameDelay = 10000;
      previousFrame++;
      if (previousFrame >= currentFrameDelay){
        previousFrame = 0;
        loopCounter = (loopCounter+1)%3;
        zeroCubeMatrix();
        displayLayerOn(loopCounter+1);
      }
    break;
    default:
      currentFrameDelay = 5*2000;
      previousFrame++;
      if (previousFrame >= currentFrameDelay){
        previousFrame = 0;
        loopCounter = (loopCounter+1)%125;
        impulseFrame();
      }
    break;

  }

  delayMicroseconds(2);
}
// end main loop




/*
Aside from the timer2 interrupt that switches the
current level of the cube turned on every millisecond,
interrupts are used to set global boolean "flag"
variables that are checked by conditionals in the
main loop.
*/

// Timer based interrupt to flash the cube
ISR(TIMER2_COMPA_vect) {
  noInterrupts();
  cubeCycle();  // flash a level of the cube
  interrupts();
  /*
  turning off other interrupts while this
  interrupt vector is called is necessary
  so that the cube maintains consistent
  and fast demultiplexing.
  */
}

ISR(TIMER1_COMPA_vect) {
  readDHTFlag = 1;
  /*
  because this flag is only for
  fetching DHT11 readings every
  2 seconds, this is not critical
  enough to turn off other interrupts
  for it to function 100.00% of the time.
  */
}

/*
the function that runs when the interrupt
for the button pin is triggered.
*/
void button0Flagged(){
  button0Flag = 1;
}



//character arrays

bool currentCharArray0[5][5]{
  {0,0,0,0,0},
  {0,0,0,0,0},
  {0,0,0,0,0},
  {0,0,0,0,0},
  {0,0,0,0,0}
};

bool currentCharArray1[5][5]{
  {0,0,0,0,0},
  {0,0,0,0,0},
  {0,0,0,0,0},
  {0,0,0,0,0},
  {0,0,0,0,0}
};

bool emptyArray[5][5]{
  {0,0,0,0,0},
  {0,0,0,0,0},
  {0,0,0,0,0},
  {0,0,0,0,0},
  {0,0,0,0,0}
};

bool zeroArray[5][5]{
  {0,0,0,0,0},
  {0,0,1,0,0},
  {0,1,0,1,0},
  {0,1,0,1,0},
  {0,0,1,0,0}
};

bool oneArray[5][5] = {
  {0,0,0,0,0},
  {0,1,1,0,0},
  {0,0,1,0,0},
  {0,0,1,0,0},
  {0,1,1,1,0}
};

bool twoArray[5][5] = {
  {0,0,0,0,0},
  {0,1,1,0,0},
  {0,0,0,1,0},
  {0,0,1,0,0},
  {0,1,1,1,0}
};

bool threeArray[5][5] = {
  {0,0,0,0,0},
  {0,1,1,1,0},
  {0,0,1,1,0},
  {0,0,0,1,0},
  {0,1,1,1,0}
};

bool fourArray[5][5] = {
  {0,0,0,0,0},
  {0,1,0,1,0},
  {0,1,1,1,0},
  {0,0,0,1,0},
  {0,0,0,1,0}
};

bool fiveArray[5][5] = {
  {0,0,0,0,0},
  {0,1,1,1,0},
  {0,1,0,0,0},
  {0,0,1,0,0},
  {0,1,1,1,0}
};

bool sixArray[5][5] = {
  {0,0,0,0,0},
  {0,1,0,0,0},
  {0,1,1,0,0},
  {0,1,0,1,0},
  {0,1,1,0,0}
};

bool sevenArray[5][5] = {
  {0,0,0,0,0},
  {0,1,1,1,0},
  {0,0,0,1,0},
  {0,0,0,1,0},
  {0,0,0,1,0}
};

bool eightArray[5][5] = {
  {0,0,1,0,0},
  {0,1,0,1,0},
  {0,0,1,0,0},
  {0,1,0,1,0},
  {0,0,1,0,0}
};

bool nineArray[5][5] = {
  {0,0,0,0,0},
  {0,1,1,1,0},
  {0,1,1,1,0},
  {0,0,0,1,0},
  {0,1,1,0,0}
};

bool tArray[5][5] = {
  {0,0,0,0,0},
  {0,1,1,1,0},
  {0,0,1,0,0},
  {0,0,1,0,0},
  {0,0,0,0,0}
};

bool hArray[5][5] = {
  {0,0,0,0,0},
  {0,1,0,1,0},
  {0,1,1,1,0},
  {0,1,0,1,0},
  {0,0,0,0,0}
};
