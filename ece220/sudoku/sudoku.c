//partners: ddamani2, ronitk2
//to create a sudoku puzzle and attempt to solve it with partial sudoku made

#include "sudoku.h"
//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------
// You are free to declare any private functions if needed.
/* This MP was done with gtandon3 and ronitk2
In this MP, we recreated the game of Sudoku by following five provided functions.
Using nested for loops and if statements, we verified whether each sudoku square was empty.
We then assigned numbers to rows and columns in a way of organising them, and then solved the Sudoku.
*/
 
// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {
  assert(i>=0 && i<9);
  // BEG TODO
  for (int j = 0; j < 9; j++){ // Initialising loop to check for val_in_row
    if (sudoku[i][j] == val)   // Check whether val is present
      return 1;
  }
  return 0;
  // END TODO
}
// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {
  assert(j>=0 && j<9);
  // BEG TODO
  for (int i = 0; i < 9; i++){ //Initialising loop to check for val_in_col
    if (sudoku[i][j] == val)   // Check whether val is present
      return 1;
  }
  return 0;
  // END TODO
}
// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
 
  assert(i>=0 && i<9);
 
  // BEG TODO
 int rstart = 0; // Initialising row and column variables
  int cstart = 0;
  if (i <= 2)
    rstart = 0; // Setting [i][0] to [i][2] as the first row- starting at i = 0
  else if (i >= 3 && i <= 5)
    rstart = 3; // Setting [i][3] to [i][5] as the second row- starting at i = 3
  else
    rstart = 6; // Setting everything else as the last row- starting at i = 6
  if (j >= 0 && j <= 2) // Setting [0][j] to [2][j] as the first column- starting at j = 0
    cstart = 0;
  else if (j >= 3 && j <= 5) // Setting [3][j] to [5][j] as the first column- starting at j = 3
    cstart = 3;
  else
    cstart = 6; // Setting everything else as the last column- starting at j = 6
  for (int k = rstart; k <= rstart+2; k++){ // Looping through each row
    for (int m = cstart; m <= cstart+2; m++){ // Looping through each column
      if (sudoku[k][m] == val)
        return 1; // Returning true if value in matrix is equal to val
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
  if (is_val_in_row(val, i, sudoku) == 1) // Return 0 test for if val in row is valid
    return 0;
  if (is_val_in_col(val, j, sudoku) == 1) // Return 0 test for if val in col is valid
    return 0;
  if (is_val_in_3x3_zone(val, i, j, sudoku) == 1)  // Return 0 test for if vals in matrix are valid
    return 0;
  return 1;
  // END TODO
}
// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {
  // BEG TODO.
  int i = 0; //Initialising variables
  int j = 0;
  int filled = 0;
  for (int k = 0; k < 9; k++){  // Loop for columns
    for (int m = 0; m < 9; m++){ // Loop for rows
      if (sudoku[k][m] != 0) // Check to see if val is filled
        filled++;  // increment filled
      }
  }
  if (filled == 81)
    return 1; // Returning 1 if sudoku is full (filled = 81)
  else{
    for (int k = 0; k < 9; k++){ // Loop for columns
      for (int m = 0; m < 9; m++){ // Loop for rows
        if (sudoku[k][m] == 0){ // Check to see if val is empty
          i = k; // Assigning variables if spot is empty
          j = m;
          k = 10;
          m = 10;
}
      }
    }
  }
  for (int num = 1; num <= 9; num++){ // Looping through squares
    if (is_val_valid(num, i, j, sudoku) == 1){
      sudoku[i][j] = num; // Solving sudoku if value is empty
      if (solve_sudoku(sudoku) == 1)
        return 1;
      sudoku[i][j] = 0;
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
