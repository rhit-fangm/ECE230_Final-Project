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

/*
Function: cubeCycle  
Returns: nothing  
Arguments: none  
Purpose:  
  update the shift register output to display the  
  current Z-layer of the 3D cube by calling  
  matrixToRegister and updateRegisterOutput,  
  then increment currentZ to cycle to the next  
  Z-layer (modulo 5). Called every millisecond  
  to create a persistence-of-vision effect.
*/
void cubeCycle(){
  matrixToRegister();
  updateRegisterOutput();
  currentZ = (currentZ+1)%5;
}

/*
Function: matrixToRegister  
Returns: nothing  
Arguments: none  
Purpose:  
  convert the current Z-layer of the 3D matrix  
  into a shiftable output array using makeShiftArray,  
  then send that array to the shift register  
  using setCubeRegister.
*/
void matrixToRegister(){
  makeShiftArray();
  setCubeRegister();
}

/*
Function: makeShiftArray  
Returns: nothing  
Arguments: none  
Purpose:  
  convert the XY plane of the 3D array "cubeMatrix"  
  at the current Z level (currentZ) into a linear  
  output array for the shift register. Also sets  
  a marker bit at index 25 + currentZ to indicate  
  the active Z-plane.
*/
void makeShiftArray(){
  // fill output array with zeros
  for (int i = 0 ; i < 30 ; i++){
    outputArray[i] = 0;
  }

  //set the current z bit high with marker bit
  outputArray[25+currentZ] = 1;

  int outputIndex = 0;
  for (int x = 0 ; x < 5 ; x++){ //navigate X values
    for (int y = 0 ; y < 5 ; y++){
      outputArray[outputIndex] = cubeMatrix[currentZ][x][y];
      outputIndex++;
    }
  }
}

/*
Function: setCubeRegister  
Returns: nothing  
Arguments: none  
Purpose:  
  shift the contents of the "outputArray"  
  into the shift register in reverse order,  
  from index 29 down to 0.
*/
void setCubeRegister(){
  for (int i = 29 ; i > -1 ; i--){
    shiftBitIn(outputArray[i]);
  }
}

// end cube register control
///-----------------------------