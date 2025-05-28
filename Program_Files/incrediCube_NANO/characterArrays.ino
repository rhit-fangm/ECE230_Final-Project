/*
File: characterArrays
Author(s): Chase Robinson
Purpose:
  used for functions displaying DHT11 values
  onto the cube.
*/

/*
Function: setCharArrayBool
Returns: nothing
Arguments: int number, bool modifyingArray[5][5]
Purpose: 
  Given an integer from 0 to 9 and a pointer to a
  5x5 array of booleans as arguments, set each index
  in the array equal to that of the corresponding
  character array for the integer.
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

/*
Function: copyBoolArray
Returns: nothing
Arguments: bool modif[5][5], bool refer[5][5]
Purpose: 
  given two 5x5 arrays of booleans, one a reference and
  another to make the same as that reference, iterate
  through all indicies and set those of the non-reference
  array equal to those of the reference array.
*/
void copyBoolArray(bool modif[5][5], bool refer[5][5]){
  for(int i = 0 ; i < 5 ; ++i){
    for(int j = 0 ; j < 5 ; ++j){
      modif[i][j] = refer[i][j];
    }
  }
}


