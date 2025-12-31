#include <stdio.h>

/*
  Sudoku puzzle
  0 represents empty cells
*/
int puzzle[9][9] = {
  {3,0,0,0,2,0,0,7,0},
  {9,0,0,5,0,0,0,1,4},
  {0,1,6,3,7,0,0,0,8},
  {2,0,0,8,0,0,0,0,1},
  {5,0,0,0,4,1,8,0,0},
  {0,8,9,0,0,0,0,5,0},
  {0,0,5,0,1,0,2,8,0},
  {0,4,0,0,0,6,0,9,3},
  {7,3,1,0,8,2,0,0,0},
};

/* Function declarations */
void print_puzzle(int puzzle[9][9]);
int valid_move(int puzzle[9][9], int row, int col, int val);
int solve_puzzle(int puzzle[9][9], int row, int col);

int main() {

  /* Display welcome message */
  printf("\n\tWelcome to SUDOKU Solver !!!");

  /* Print original Sudoku puzzle */
  printf("\n\nOriginal Puzzle:");
  print_puzzle(puzzle);

  /* Try solving the puzzle starting from first cell */
  if (solve_puzzle(puzzle, 0, 0)) {
    printf("\n The puzzle is solved:");
    print_puzzle(puzzle);
  } else {
    printf("\n This puzzle is not Solvable\n");
  }

  return 0;
}

/*
  Recursive function to solve Sudoku using backtracking
  row → current row
  col → current column
*/
int solve_puzzle(int puzzle[9][9], int row, int col) {

  /* If column reaches end, move to next row */
  if (col == 9) {
    if (row == 8) {
      return 1;  // All rows completed → puzzle solved
    }
    row++;
    col = 0;
  }

  /* If cell already contains a number, move to next column */
  if (puzzle[row][col] > 0) {
    return solve_puzzle(puzzle, row, col + 1);
  }

  /* Try placing numbers from 1 to 9 */
  for (int i = 1; i <= 9; i++) {

    /* Check if placing i is valid */
    if (valid_move(puzzle, row, col, i)) {

      puzzle[row][col] = i;   // Place number

      /* Recursively solve next cell */
      if (solve_puzzle(puzzle, row, col + 1)) {
        return 1;
      }

      /* Backtrack if solution fails */
      puzzle[row][col] = 0;
    }
  }

  /* No valid number found for this cell */
  return 0;
}

/*
  Function to check whether a value can be placed
  at puzzle[row][col] without violating Sudoku rules
*/
int valid_move(int puzzle[9][9], int row, int col, int val) {

  /* Check row for duplicate */
  for (int i = 0; i < 9; i++) {
    if (puzzle[row][i] == val) {
      return 0;
    }
  }

  /* Check column for duplicate */
  for (int i = 0; i < 9; i++) {
    if (puzzle[i][col] == val) {
      return 0;
    }
  }

  /* Check 3x3 subgrid */
  int r = row - row % 3;
  int c = col - col % 3;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (puzzle[r + i][c + j] == val) {
        return 0;
      }
    }
  }

  /* Value can be placed safely */
  return 1;
}

/*
  Function to print Sudoku puzzle
  Displays grid with row and column separators
*/
void print_puzzle(int puzzle[9][9]) {

  printf("\n+-------+-------+-------+");

  for (int row = 0; row < 9; row++) {

    /* Print horizontal separator after every 3 rows */
    if (row % 3 == 0 && row != 0) {
      printf("\n|-------+-------+-------|");
    }

    printf("\n");

    for (int col = 0; col < 9; col++) {

      /* Print vertical separator after every 3 columns */
      if (col % 3 == 0) {
        printf("| ");
      }

      /* Print number or blank for empty cell */
      if (puzzle[row][col] != 0) {
        printf("%d ", puzzle[row][col]);
      } else {
        printf("  ");
      }
    }
    printf("|");
  }

  printf("\n+-------+-------+-------+\n");
}
