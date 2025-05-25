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

int temperature = 0;
int humidity = 0;

// interrupt boolean flags to run in main loop
bool readDHTFlag = 0;
bool button0Flag = 0;



const int inputPin = 6;
const int srclk = 5;
const int orclk = 4;

// 
bool cubeFlag = 0;
int currentZ = 0;
//

// Frame Animation Variables
int currentFrame = 0;
int endFrame = 0;
int currentFrameDelay = 10;
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


void setup() {
  // set up timer-based & other interrupts
  setupTimer2();
  setupTimer1();
  setupButton0();

  Serial.begin(9600);
  dht11.begin();

  regInit();
  clearShiftRegister(30);
  zeroMatrix();

}


void loop() {
  // Serial.println(temperature);
  if (readDHTFlag){
    readDHTFlag = 0;
    updateDHTValues();

  }

  if (button0Flag){
    button0Flag = 0;
    Serial.println("button flagged");
    dhtValuesToSerial();
  }

  if (cubeFlag){
    cubeFlag = 0;
    cubeCycle();
  }

  setImpulseMatrix();
  // oneMatrix();
  delay(currentFrameDelay);
  
}
// end main loop







// Timer based interrupt to flash the cube
ISR(TIMER2_COMPA_vect) {
  noInterrupts();
  // Serial.println("timer2");
  cubeCycle();  // flash a level of the cube
  interrupts();
}

ISR(TIMER1_COMPA_vect) {
  // noInterrupts();
  // Serial.println("timer1");
  readDHTFlag = 1;
  // Serial.println(temperature);
  // interrupts();
}

void button0Flagged(){
  button0Flag = 1;
}



//character arrays

bool currentCharArray[5][5]{
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
  {0,1,1,1,0},
  {0,1,0,1,0},
  {0,1,0,1,0},
  {0,1,0,1,0},
  {0,1,1,1,0}
};

bool oneArray[5][5] = {
  {0,0,1,0,0},
  {0,1,1,0,0},
  {0,0,1,0,0},
  {0,0,1,0,0},
  {0,1,1,1,0}
};

bool twoArray[5][5] = {
  {0,1,1,1,0},
  {0,0,0,1,0},
  {0,0,1,0,0},
  {0,1,0,0,0},
  {0,1,1,1,0}
};

bool threeArray[5][5] = {
  {0,1,1,1,0},
  {0,0,0,1,0},
  {0,0,1,1,0},
  {0,0,0,1,0},
  {0,1,1,1,0}
};

bool fourArray[5][5] = {
  {0,1,0,1,0},
  {0,1,0,1,0},
  {0,1,1,1,0},
  {0,0,0,1,0},
  {0,0,0,1,0}
};

bool fiveArray[5][5] = {
  {0,1,1,1,1},
  {0,1,0,0,0},
  {0,1,1,1,0},
  {0,0,0,1,0},
  {0,1,1,1,0}
};

bool sixArray[5][5] = {
  {0,0,1,1,0},
  {0,1,0,0,0},
  {0,1,1,1,0},
  {0,1,0,1,0},
  {0,1,1,1,0}
};

bool sevenArray[5][5] = {
  {0,1,1,1,0},
  {0,0,0,1,0},
  {0,0,1,0,0},
  {0,1,0,0,0},
  {0,1,0,0,0}
};

bool eightArray[5][5] = {
  {0,1,1,1,0},
  {0,1,0,1,0},
  {0,1,1,1,0},
  {0,1,0,1,0},
  {0,1,1,1,0}
};

bool nineArray[5][5] = {
  {0,1,1,1,0},
  {0,1,0,1,0},
  {0,1,1,1,0},
  {0,0,0,1,0},
  {0,1,1,0,0}
};
