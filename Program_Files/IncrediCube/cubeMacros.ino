/*
File: cubeMacros
Author(s): Chase Robinson, Michael Fang
Purpose: run LED sequences using functions from shiftControl
*/

void registerImpulse(){
  shiftInBit(1);
  for (int i = 0 ; i < 25 ; i++){
    loadShiftOutput();
    shiftStep();
    delay(shiftPeriod);
  }
}

void registerFill(){
  shiftInBit(1);
  for (int i = 0 ; i < 25 ; i++){
    loadShiftOutput();
    shiftInBit(1);
    delay(shiftPeriod);
  }
  shiftInBit(0);
  for (int i = 0 ; i < 25 ; i++){
    loadShiftOutput();
    shiftStep();
    delay(shiftPeriod);
  }
}

void registerFillLength(int length){
  shiftInBit(1);
  for (int i = 0 ; i < length ; i++){
    loadShiftOutput();
    shiftInBit(1);
    delay(shiftPeriod);
  }
  shiftInBit(0);
  for (int i = 0 ; i < length ; i++){
    loadShiftOutput();
    shiftStep();
    delay(shiftPeriod);
  }
}