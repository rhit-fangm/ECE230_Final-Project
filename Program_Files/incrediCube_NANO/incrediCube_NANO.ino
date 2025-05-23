const int inputPin = 3;
const int srclk = 5;
const int orclk = 4;

int currentZ = 0;

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

  // Serial.begin(9600);
  regInit();
  clearShiftRegister(30);

}

void loop() {

  // cubeImpulse();
  matrixToRegister();
  updateRegisterOutput();
  currentZ = (currentZ+1)%5;
}
// end main loop





///-----------------------------
// cube macro control

void cubeImpulse(){
  
}

void matrixToRegister(){
  makeShiftArray();
  setCubeRegister();
}

void makeShiftArray(){
  // fill output array with zeros
  for (int i = 0 ; i < 30 ; i++){
    outputArray[i] = 0;
  }

  //set the current z bit high
  outputArray[25+currentZ] = 1;

  int outputIndex = 0;
  for (int x = 0 ; x < 5 ; x++){ //navigate X values
    for (int y = 0 ; y < 5 ; y++){
      outputArray[outputIndex] = cubeMatrix[currentZ][x][y];
      outputIndex++;
    }
  }
}

// load the shift register with current XY plane
void setCubeRegister(){
  for (int i = 29 ; i > -1 ; i--){
    shiftBitIn(outputArray[i]);
  }
}

// set all bits in stored matrix to zero
void zeroMatrix(){
  for (int i = 0 ; i < 5 ; i++){
    for (int j = 0 ; j < 5 ; j++){
      for (int k = 0 ; k < 5 ; k++){
        cubeMatrix[i][j][k] = 0;
      }
    }
  }

}

// end cube macro control
///-----------------------------





///-----------------------------
// shift register controls

//Initialize register pins
void regInit(){
  pinMode(inputPin, OUTPUT);
  pinMode(srclk, OUTPUT);
  pinMode(orclk, OUTPUT);
  digitalWrite(inputPin, 0);
  digitalWrite(srclk, 0);
  digitalWrite(orclk, 0);
  // Serial.println("regInit");
}

// shift one bit of data into the sr
void shiftBitIn(bool bit){
  digitalWrite(inputPin, bit);
  digitalWrite(srclk, 1);
  delayMicroseconds(1);
  digitalWrite(srclk, 0);
  digitalWrite(inputPin, 0);
}

void shiftFill(bool bit, int count){
  for (int i = 0 ; i < count ; i++){
    shiftBitIn(bit);
  }
}

// load the values of shift registers into output registers
void updateRegisterOutput(){
  digitalWrite(orclk, 1);
  delayMicroseconds(1);
  digitalWrite(orclk, 0);

  // Serial.println("updateOutput");
}

void clearShiftRegister(int numBits){
  for (int i = 0 ; i < numBits ; i++){
    shiftBitIn(0);
  }
  // Serial.println("clearShiftRegister");
}

// end of shift register controls
///-----------------------------


