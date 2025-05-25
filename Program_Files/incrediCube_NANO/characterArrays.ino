void setCurrentCharArray(int number) {
  if (number >= 0 && number <= 9)
    switch(number){
      case 0:copyBoolArray(currentCharArray, zeroArray);break;
      case 1:copyBoolArray(currentCharArray, oneArray);break;
      case 2:copyBoolArray(currentCharArray, twoArray);break;
      case 3:copyBoolArray(currentCharArray, threeArray);break;
      case 4:copyBoolArray(currentCharArray, fourArray);break;
      case 5:copyBoolArray(currentCharArray, fiveArray);break;
      case 6:copyBoolArray(currentCharArray, sixArray);break;
      case 7:copyBoolArray(currentCharArray, sevenArray);break;
      case 8:copyBoolArray(currentCharArray, eightArray);break;
      case 9:copyBoolArray(currentCharArray, nineArray);break;
      default:copyBoolArray(currentCharArray, emptyArray);break;
    }
}

void copyBoolArray(bool modif[5][5], bool refer[5][5]){
  for(int i = 0 ; i < 5 ; ++i){
    for(int j = 0 ; j < 5 ; ++j){
      modif[i][j] = refer[i][j];
    }
  }
}


