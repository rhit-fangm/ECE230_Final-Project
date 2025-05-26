/*
File: characterArrays
Author(s): Chase Robinson
Purpose:
  used for functions displaying DHT11 values
  onto the cube.
*/


void setCharArrayBool(int number, bool modifyingArray[5][5]) {
  if (number >= 0 && number <= 9)
    switch(number){
      case 0:copyBoolArray(modifyingArray, zeroArray);break;
      case 1:copyBoolArray(modifyingArray, oneArray);break;
      case 2:copyBoolArray(modifyingArray, twoArray);break;
      case 3:copyBoolArray(modifyingArray, threeArray);break;
      case 4:copyBoolArray(modifyingArray, fourArray);break;
      case 5:copyBoolArray(modifyingArray, fiveArray);break;
      case 6:copyBoolArray(modifyingArray, sixArray);break;
      case 7:copyBoolArray(modifyingArray, sevenArray);break;
      case 8:copyBoolArray(modifyingArray, eightArray);break;
      case 9:copyBoolArray(modifyingArray, nineArray);break;
      default:copyBoolArray(modifyingArray, emptyArray);break;
    }
}

void copyBoolArray(bool modif[5][5], bool refer[5][5]){
  for(int i = 0 ; i < 5 ; ++i){
    for(int j = 0 ; j < 5 ; ++j){
      modif[i][j] = refer[i][j];
    }
  }
}


