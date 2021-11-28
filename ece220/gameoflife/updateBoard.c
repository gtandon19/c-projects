/*
partners: ronitk2, ddamani2

In this MP we recreated the game of life on a game board. Using nested loops we created three functions, where we counted the number of live neighbors, updated the game board to the next step using counters that incremented every time we went through the nested loop. Lastly we checked the number of cells alive by looking at the spaces near the current one.
*/


 
/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */
int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
  int liveNeighbors = 0; //counter for live neighbors
  for (int i=row-1; i<=row+1; i++){ //outer loop
    if (i>=0 && i<boardRowSize){
      for (int j=col-1; j<=col+1; j++){ //inner loop
        if (j>=0 && j<boardColSize){
          if (i==row && j==col)
            continue;
          if (board[i*boardColSize+j] == 1)
   liveNeighbors++; //incremented if conditions met
}
      }
    }
  }
  return liveNeighbors;
}
/*
 * Update the game board to the next step.
 * Input:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
  int newDead[boardRowSize*boardColSize]; //array initialized
  int newDeadCounter = 0; //counter for dead
  int newAlive[boardRowSize*boardColSize]; //array initialized
  int newAliveCounter = 0; //counter for aliv
  for (int i = 0; i < boardRowSize; i++){
    for (int j = 0; j < boardColSize; j++){
      if (board[i*boardColSize+j] == 1){
        if (countLiveNeighbor(board,boardRowSize,boardColSize,i,j) < 2 ||
   countLiveNeighbor(board,boardRowSize,boardColSize,i,j) > 3){
          newDead[newDeadCounter] = i*boardColSize+j;
          newDeadCounter++; //incremented once conditions met
}
      }
      else {
        if (countLiveNeighbor(board,boardRowSize,boardColSize,i,j) == 3){
          newAlive[newAliveCounter] = i*boardColSize+j;
          newAliveCounter++; //incremented
}          
      }
    }
  }
  for (int i = 0; i < newDeadCounter; i++)
    board[newDead[i]] = 0; 
  for (int j = 0; j < newAliveCounter; j++)
    board[newAlive[j]] = 1;
}
/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){
  for (int i = 0; i < boardRowSize; i++){ //outer loop
    for (int j = 0; j < boardColSize; j++){ //inner loop
      if (board[i*boardColSize+j] == 1){
        if (countLiveNeighbor(board,boardRowSize,boardColSize,i,j) < 2 ||
   countLiveNeighbor(board,boardRowSize,boardColSize,i,j) > 3)
          return 0; //return if the alive cells change
      }
      else {
        if (countLiveNeighbor(board,boardRowSize,boardColSize,i,j) == 3)
          return 0; //return if alive cells chanfe
      }
    }
  }
  return 1; //no alive cells / next is identical
}
