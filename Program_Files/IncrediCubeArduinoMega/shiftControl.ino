/*
File: shiftControl
Author(s): Chase Robinson, Michael Fang
Purpose: Collection of functions for controlling 
a shift register without shift clear pin used
*/

//start clockPin low, toggle 1-0 to shift out, outEnable = active-low, regClearPin = active-low
void shiftInBit(bool bit){
  digitalWrite(shiftInputPin, bit);
  digitalWrite(srclkPin, HIGH);
  delayMicroseconds(shiftDelay);
  digitalWrite(srclkPin, LOW);
  digitalWrite(shiftInputPin, LOW);
}

//shifts registers by one
void shiftStep(){
  digitalWrite(srclkPin, HIGH);
  delayMicroseconds(shiftDelay);
  digitalWrite(srclkPin, LOW);
}

void loadShiftOutput(){
  digitalWrite(orclkPin, HIGH);
  delayMicroseconds(shiftDelay);
  digitalWrite(orclkPin, LOW);
}

void shiftInit(){
  pinMode(srclkPin, OUTPUT);
  pinMode(orclkPin, OUTPUT);
  pinMode(shiftInputPin, OUTPUT);
  pinMode(outEnable, OUTPUT);
  //make sure clockPin is low initially
  digitalWrite(srclkPin, LOW);
  digitalWrite(orclkPin, LOW);
  digitalWrite(shiftInputPin, LOW);
  digitalWrite(outEnable, LOW);
}