/*
File: helpfulFunctions
Author(s): Chase Robinson
Purpose:
  A collection of functions that aren't really
  related to the hardware and don't have any specialization
  to hardware control functions, but do have use
  in some algorithms for displaying neat stuff
  on the cube or doing other calculations.

  Post project note: I'm leaving this code here, even though we didn't end up using it.
  Thanks for all the hard work and showing me shift registers. :>
*/


//edit one of the 5x5x5 3D matrices without running into an out of bounds error
void safeMatrixEdit(bool matrix[5][5][5], int z, int x, int y, bool value){
  if (0 <= z <= 4 && 0 <= x <= 4 && 0 <= y <= 4){
    matrix[z][x][y] = value;
  }
}