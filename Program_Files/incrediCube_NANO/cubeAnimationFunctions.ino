


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

void updateFrame(){
  currentFrame = (currentFrame+1)%endFrame;
}