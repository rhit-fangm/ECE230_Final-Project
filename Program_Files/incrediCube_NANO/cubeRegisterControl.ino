/*
File: cubeRegisterControl
Author(s): Chase Robinson
Purpose:
  A collection of functions that act as intermediaries
  between functions controlling the shift register directly
  and functions dealing with the 3D cube matrix stored in
  memory and ways to animate it.
*/


///-----------------------------
// cube register control

void cubeCycle(){
  matrixToRegister();
  updateRegisterOutput();
  currentZ = (currentZ+1)%5;
}

// converts the full matrix to 
// necessary output for currentZ layer
// and then shifts it out
void matrixToRegister(){
  makeShiftArray();
  setCubeRegister();
}

// convert the XY plane
// of the current zValue
// to the shift register output
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

// outputArray into shift registers
void setCubeRegister(){
  for (int i = 29 ; i > -1 ; i--){
    shiftBitIn(outputArray[i]);
  }
}

// end cube register control
///-----------------------------