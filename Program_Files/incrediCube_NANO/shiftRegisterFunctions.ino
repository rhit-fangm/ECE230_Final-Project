/*
File: shiftRegisterFunctions
Author(s): Chase Robinson
Purpose: 
  control 4 8bit SN74H595 shift registers
  in a daisy-chain configuration.

Bit Connections:

  D4 ----> ORCLK (output register clock)
  D5 ----> SRCLK (shift register clock)
  D6 ----> [][][][][]|[][][] [][]|[][][][][]|[] [][][][]|[][][][] []|   [] [] [] [] []     [] []             (output register pins / bits)
 shift in:{                     XY plane bits                       }  {Z control bits}   {unused}

*/

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