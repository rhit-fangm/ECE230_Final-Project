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

/*
Function: regInit
Returns: nothing
Purpose: 
  Correctly initialize control pins:
  Set the pinMode and initial outputs
  of the input and two clock pins for
  the shift registers.
*/
void regInit(){
  pinMode(inputPin, OUTPUT);
  pinMode(srclk, OUTPUT);
  pinMode(orclk, OUTPUT);
  digitalWrite(inputPin, 0);
  digitalWrite(srclk, 0);
  digitalWrite(orclk, 0);
}

/*
Function: shiftBitIn
Returns: nothing
Arguments: bool bit
Purpose: 
  shift one bit of data with value "bit"
  into the shift register.
*/
void shiftBitIn(bool bit){
  digitalWrite(inputPin, bit);
  digitalWrite(srclk, 1);
  delayMicroseconds(1);
  digitalWrite(srclk, 0);
  digitalWrite(inputPin, 0);
}


/*
Function: shiftFill  
Returns: nothing  
Arguments: bool bit, int count  
Purpose:  
  shift the specified bit value "bit"  
  into the shift register "count" times  
  in sequence by calling shiftBitIn.
*/
void shiftFill(bool bit, int count){
  for (int i = 0 ; i < count ; i++){
    shiftBitIn(bit);
  }
}

/*
Function: updateRegisterOutput  
Returns: nothing  
Arguments: none  
Purpose:  
  load the values stored in the shift registers  
  into the output registers by toggling the  
  output register clock (orclk) line.
*/
void updateRegisterOutput(){
  digitalWrite(orclk, 1);
  delayMicroseconds(1);
  digitalWrite(orclk, 0);
}

/*
Function: clearShiftRegister  
Returns: nothing  
Arguments: int numBits  
Purpose:  
  clear the shift register by shifting in  
  "numBits" number of 0s sequentially.
*/
void clearShiftRegister(int numBits){
  for (int i = 0 ; i < numBits ; i++){
    shiftBitIn(0);
  }
}

// end of shift register controls
///-----------------------------