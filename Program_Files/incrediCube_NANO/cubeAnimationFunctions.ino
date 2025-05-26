/*
File: cubeAnimationFunctions
Author(s): Chase Robinson
Purpose:
  Do operations on the global 3D matrix
  variable to control LEDs using for loops
  and math.
*/

// oscillating display
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
      cubeMatrix[2][0][0] = 1;
      cubeMatrix[2][0][4] = 1;
      cubeMatrix[2][4][0] = 1;
      cubeMatrix[2][4][4] = 1;
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

// update cube with temperature values
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

// update cube with humidity values
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

// display randomized LEDs lighting up and going out in a 4x4x4 chunk
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



// "run" a single "blip" through every LED
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


// set all bits in stored matrix to zero
void zeroCubeMatrix(){
  for (int z = 0 ; z < 5 ; z++){
    for (int x = 0 ; x < 5 ; x++){
      for (int y = 0 ; y < 5 ; y++){
        cubeMatrix[z][x][y] = 0;
      }
    }
  }

}

void oneMatrix(){
  for (int z = 0 ; z < 5 ; z++){
    for (int x = 0 ; x < 5 ; x++){
      for (int y = 0 ; y < 5 ; y++){
        cubeMatrix[z][x][0] = 1;
      }
    }
  }

}