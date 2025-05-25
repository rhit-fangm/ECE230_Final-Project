/*
File: cubeAnimationFunctions
Author(s): Chase Robinson
Purpose:
  Do operations on the global 3D matrix
  variable to control LEDs using for loops
  and math.
*/

// "run" a single "blip" through every LED
void setImpulseMatrix(){
  endFrame = 125;
  currentFrameDelay = 100;
    zeroMatrix();
    for (int z = 0 ; z < 5 ; z++){
      for (int x = 0 ; x < 5 ; x++){
        for (int y = 0 ; y < 5 ; y++){
          if (z*25+x*5+y == currentFrame){
            cubeMatrix[z][x][y] = 1;
          }
        }
      }
    }
    updateFrame();
}

//increments the frame
void updateFrame(){
  currentFrame = (currentFrame+1)%endFrame;
}

// set all bits in stored matrix to zero
void zeroMatrix(){
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