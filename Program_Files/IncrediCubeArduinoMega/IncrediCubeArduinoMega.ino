// Shift Register Pins
const int srclkPin = 6;
const int orclkPin = 5;
const int shiftInputPin = 4;
const int outEnable = 3; //active low
///

// Shift Register Variables
const int shiftDelay = 1; //us
bool outputEnable = true;
///

// Debugging Values
const int shiftPeriod = 100;
///

bool cubeMatrix[5][5][5] = {
  {{0, 0, 0, 0, 0},{0, 0, 0, 0, 0},{0, 0, 0, 0, 0},{0, 0, 0, 0, 0},{0, 0, 0, 0, 0}},
  {{0, 0, 0, 0, 0},{0, 0, 0, 0, 0},{0, 0, 0, 0, 0},{0, 0, 0, 0, 0},{0, 0, 0, 0, 0}},
  {{0, 0, 0, 0, 0},{0, 0, 0, 0, 0},{0, 0, 0, 0, 0},{0, 0, 0, 0, 0},{0, 0, 0, 0, 0}},
  {{0, 0, 0, 0, 0},{0, 0, 0, 0, 0},{0, 0, 0, 0, 0},{0, 0, 0, 0, 0},{0, 0, 0, 0, 0}},
  {{0, 0, 0, 0, 0},{0, 0, 0, 0, 0},{0, 0, 0, 0, 0},{0, 0, 0, 0, 0},{0, 0, 0, 0, 0}}
};
/*
Implementation: ZXY order. 
1st dimension = Z coordinate of the active layer
2nd dimension = X coordinate of the activated column
3rd dimension = Y coordinate of the activated column

Let each register be an X coordinate, with each bit
position on that register (0-4) be a Y coordinate.
*/

void setup() {
  // put your setup code here, to run once:
  shiftInit();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  // registerImpulse();
  // registerFill();
  registerFillLength(5);
  delay(100);
  Serial.println("registercycled");
}
