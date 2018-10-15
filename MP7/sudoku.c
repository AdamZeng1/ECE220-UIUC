#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.


//Introductory paragraph starts here
//This program solves the Sudoku puzzle using recursive backtracking
//It makes sure that every cell with new number is valid
//which means each number can only occur once in each 3x3 zone,
//row, and column of the grid
//please open the program in Atom, because the format might look weird in other editors





// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
  int col;
  for (col = 0; col <= 8; col++){                   //easy, clear one for loop, no comment
    if (val == sudoku[i][col]){
      return 1;
    }
  }
  return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO
  int row;
  for (row = 0; row <= 8; row++){                   //same thing again
    if (val == sudoku[row][j]){
      return 1;
    }
  }
  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9);
  int row, col;
  int startrow = 3 * int(i / 3);                      //here I divide the whole sudoku into 9 3x3 blocks,
  int startcol = 3 * int(j / 3);                      //and start from the top left corner cell of the block
  // BEG TODO
  for(row = startrow; row <= startrow + 2; row++){
    for(col = startcol; col <= startcol + 2; col++){
        if(val == sudoku[row][col]){
          return 1;
        }
      }
    }
  return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO
  if((is_val_in_row(val, i, sudoku) == 1) || (is_val_in_col(val, j, sudoku) == 1) || (is_val_in_3x3_zone(val, i, j, sudoku) == 1)){
    return 0;               //simply combine three functions
  }
  return 1;
  // END TODO
}

//This is a new function that checks if every cell in the sudoku has been assigned a number
//It returns 1/true if every cell is assigned
//This helps me write solve_sudoku in a more compact way similar to the pseudocode provided
int allassigned(int sudoku[9][9]){
  int i, j;
  for (i = 0; i <= 8; i++){
    for (j = 0; j <= 8; j++){
      if (sudoku[i][j] == 0){
        return 0;
      }
    }
  }
  return 1;
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
  int i, j, row, col, num;
  if (allassigned(sudoku) == 1){              //In this function I simply copied the pseudocode provided
    return 1;
  }
  else{
    for (i = 0; i <= 8; i++){
      for (j = 0; j <= 8; j++){
        if (sudoku[i][j] == 0){
          row = i;                            //store the current i, j value,
          col = j;
          i = 9;                              //break the nested for loops
          j = 9;
        }
      }
    }
  }
  for (num = 1; num <= 9; num++){
    if (is_val_valid(num, row, col, sudoku) == 1){
      sudoku[row][col] = num;
      if (solve_sudoku(sudoku) == 1){
        return 1;
      }
      sudoku[row][col] = 0;
    }
  }
  return 0;
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}
