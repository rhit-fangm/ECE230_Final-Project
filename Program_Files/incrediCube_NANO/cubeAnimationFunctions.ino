/*
File: cubeAnimationFunctions
Author(s): Chase Robinson
Purpose:
  Do operations on the global 3D matrix
  variable to control LEDs using for loops
  and math.
*/

/*
Function: displayLayerOn  
Returns: nothing  
Arguments: int layer  
Purpose:  
  turn on a centered 3×3 section of the specified  
  Z-layer "layer" in the cubeMatrix by setting  
  cubeMatrix[layer][x][y] to 1 for x and y in [1, 3].
*/
void displayLayerOn(int layer){
  for (int x = 1 ; x < 4 ; x++){
    for (int y = 1 ; y < 4 ; y++){
      cubeMatrix[layer][x][y] = 1;
    }
  }
}

/*
Function: displayOscillatingFrame  
Returns: nothing  
Arguments: none  
Purpose:  
  generate an oscillating 3D frame animation pattern  
  in cubeMatrix based on the value of loopCounter.  
  Clears the matrix with zeroCubeMatrix before selectively  
  lighting voxels across different cases to simulate  
  expansion and contraction centered around the cube’s core.  
  Each case corresponds to a different frame in the animation.
*/
void displayOscillatingFrame(){
  zeroCubeMatrix();
  switch(loopCounter){
    case 0:
      cubeMatrix[2][2][2] = 1;
    break;
    case 1:
      cubeMatrix[1][1][1] = 1;
      cubeMatrix[1][1][3] = 1;
      cubeMatrix[1][3][1] = 1;
      cubeMatrix[1][3][3] = 1;

      cubeMatrix[3][1][1] = 1;
      cubeMatrix[3][1][3] = 1;
      cubeMatrix[3][3][1] = 1;
      cubeMatrix[3][3][3] = 1;
    break;
    case 2:

    break;
    case 3:
      cubeMatrix[1][0][0] = 1;
      cubeMatrix[1][0][4] = 1;
      cubeMatrix[1][4][0] = 1;
      cubeMatrix[1][4][4] = 1;

      cubeMatrix[3][0][0] = 1;
      cubeMatrix[3][0][4] = 1;
      cubeMatrix[3][4][0] = 1;
      cubeMatrix[3][4][4] = 1;
    break;
    case 4:
      cubeMatrix[1][1][1] = 1;
      cubeMatrix[1][1][3] = 1;
      cubeMatrix[1][3][1] = 1;
      cubeMatrix[1][3][3] = 1;

      cubeMatrix[3][1][1] = 1;
      cubeMatrix[3][1][3] = 1;
      cubeMatrix[3][3][1] = 1;
      cubeMatrix[3][3][3] = 1;
    break;
    default:
    break;
  }

}

/*
Function: displayTemperatureFrame  
Returns: nothing  
Arguments: none  
Purpose:  
  update cubeMatrix to display a temperature frame.  
  Clears the cube using zeroCubeMatrix, converts  
  numeric temperature digits in tempNums[0] and tempNums[1]  
  to 5×5 boolean arrays via setCharArrayBool, and stores  
  them in currentCharArray0 and currentCharArray1.  
  Writes a static 'T' character on the top Z-layer using tArray.  
  Displays one of the two digits on the side of the cube  
  depending on loopCounter:  
    - First digit shown on X=4 layer if loopCounter < 50  
    - Second digit shown on X=3 layer otherwise.
*/
void displayTemperatureFrame(){
  zeroCubeMatrix();
  setCharArrayBool(tempNums[0], currentCharArray0);
  setCharArrayBool(tempNums[1], currentCharArray1);

  
  for (int x = 0 ; x < 4 ; x++){
    for (int y = 0 ; y < 4 ; y++){
      // write "T" on top to indicate temperature being displayed
      cubeMatrix[4][x][y] = tArray[x][y];
      // write characters
      if (loopCounter < 50){
        cubeMatrix[x][4][y] = currentCharArray0[4-x][4-y];
      } else {
        cubeMatrix[x][3][y] = currentCharArray1[4-x][4-y];
      }
      
    }
  }
}

/*
Function: displayHumidityFrame  
Returns: nothing  
Arguments: none  
Purpose:  
  update cubeMatrix to display a humidity frame.  
  Clears the cube using zeroCubeMatrix, converts  
  numeric humidity digits in humNums[0] and humNums[1]  
  to 5×5 boolean arrays via setCharArrayBool, and stores  
  them in currentCharArray0 and currentCharArray1.  
  Writes a static 'H' character on the top Z-layer using hArray.  
  Displays one of the two digits on the side of the cube  
  depending on loopCounter:  
    - First digit shown on X=4 layer if loopCounter < 50  
    - Second digit shown on X=3 layer otherwise.
*/
void displayHumidityFrame(){
  zeroCubeMatrix();
  setCharArrayBool(humNums[0], currentCharArray0);
  setCharArrayBool(humNums[1], currentCharArray1);

  
  for (int x = 0 ; x < 4 ; x++){
    for (int y = 0 ; y < 4 ; y++){
      // write "H" on top to indicate temperature being displayed
      cubeMatrix[4][x][y] = hArray[x][y];
      // write characters
      if (loopCounter < 50){
        cubeMatrix[x][4][y] = currentCharArray0[4-x][4-y];
      } else {
        cubeMatrix[x][3][y] = currentCharArray1[4-x][4-y];
      }
      
    }
  }
}

/*
Function: droplets  
Returns: nothing  
Arguments: int probLimit  
Purpose:  
  simulate a randomized droplet effect within a 4×4×4 region  
  of the cubeMatrix. With probability 1/probLimit, sets several  
  LED voxels to 1 at randomly chosen edge positions across  
  multiple axes to simulate droplets forming. Independently,  
  randomly turns off one voxel to simulate a droplet vanishing.
*/
void droplets(int probLimit){
    // add droplets to start at random points from bottom
    int prob = random(0,probLimit);
    int xRand = random(0,4);
    int yRand = random(0,4);
    int zRand = random(0,4);
    if(prob == 1){
      cubeMatrix[zRand][0][yRand] = 1;
      cubeMatrix[zRand][3][xRand] = 1;
      cubeMatrix[zRand][xRand][0] = 1;
      cubeMatrix[zRand][yRand][3] = 1;
      cubeMatrix[0][zRand][xRand] = 1;
      cubeMatrix[3][yRand][zRand] = 1;
    }
    cubeMatrix[random(0,4)][random(0,4)][random(0,4)] = 0;
}



/*
Function: impulseFrame  
Returns: nothing  
Arguments: none  
Purpose:  
  create an impulse animation by turning on a single  
  voxel in cubeMatrix based on the loopCounter value.  
  Clears the cube using zeroCubeMatrix, then lights  
  exactly one LED such that it appears to move sequentially  
  through all 125 positions in Z-X-Y order.
*/
void impulseFrame(){
    zeroCubeMatrix();
    for (int z = 0 ; z < 5 ; z++){
      for (int x = 0 ; x < 5 ; x++){
        for (int y = 0 ; y < 5 ; y++){
          if (z*25+x*5+y == loopCounter){
            cubeMatrix[z][x][y] = 1;
          }
        }
      }
    }
}


/*
Function: zeroCubeMatrix  
Returns: nothing  
Arguments: none  
Purpose:  
  clear the entire cubeMatrix by setting every voxel  
  at all Z, X, and Y positions to 0.
*/
void zeroCubeMatrix(){
  for (int z = 0 ; z < 5 ; z++){
    for (int x = 0 ; x < 5 ; x++){
      for (int y = 0 ; y < 5 ; y++){
        cubeMatrix[z][x][y] = 0;
      }
    }
  }
}

/*
Function: oneMatrix  
Returns: nothing  
Arguments: none  
Purpose:  
  set the first Y-column (y = 0) of every X and Z position  
  in cubeMatrix to 1, creating vertical planes of lit voxels  
  on one side of the cube.
*/
void oneMatrix(){
  for (int z = 0 ; z < 5 ; z++){
    for (int x = 0 ; x < 5 ; x++){
      for (int y = 0 ; y < 5 ; y++){
        cubeMatrix[z][x][0] = 1;
      }
    }
  }
}