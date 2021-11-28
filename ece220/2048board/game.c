//partners: ronitk2, ddamani2

/*This mp8 essentially runs a board of 2048. The game is about how we can combine blocks strategically to make the largest numbers, and we use special functions to do it. Move functions using wsad are used to move the board around, the getcell function gets that particular cell, and we use checking functions to ensure the code works.
*/
#include "game.h"
game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure)
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));
    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct
    mygame->rows = rows;  // rows initialized
    mygame->cols = cols;  // cols initialized
    mygame->score = 0;    // score initialized
    for (int i = 0; i < rows; i++){      // cells initialized
      for (int j = 0; j < cols; j++)
        mygame->cells[i * cols + j] = -1; //make the entire board empty (-1)
    }
    return mygame;
}
void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
game structure to have the given number of rows and columns. Initialize
the score and all elements in the cells to -1. Make sure that any
memory previously allocated is not lost in this function.
*/
{
/*Frees dynamically allocated memory used by cells in previous game,
then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
free((*_cur_game_ptr)->cells);
(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));
//YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct
        (*_cur_game_ptr)->rows = new_rows;  // rows initialized
        (*_cur_game_ptr)->cols = new_cols;  // cols initialized
        (*_cur_game_ptr)->score = 0;         // score initialized
        for (int i = 0; i < new_rows; i++){     // cells initialized
          for (int j = 0; j < new_cols; j++)
            (*_cur_game_ptr)->cells[i * new_cols + j] = -1; //make the new reallocated board empty with value -1
}
return;
}
void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}
cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
if the row and col coordinates do not exist.
*/
{
    //YOUR CODE STARTS HERE
  if (row < cur_game->rows && col < cur_game->cols)  // checks if cell exists
    return &cur_game->cells[row * cur_game->cols + col];  // pointer returned
  return NULL;
}
int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can
   not merge twice in one turn. If sliding the tiles up does not cause any
   cell to change value, w is an invalid move and return 0. Otherwise, return 1.
*/
{
    //YOUR CODE STARTS HERE
    
    //initialize variables
  int rowc = 0;
  int rowt = 0;
  int rowa = 0;
  int moves = 0;
  for (int j = 0; j < cur_game->cols; j++){    // goes through columns
    for (int i = 0; i < cur_game->rows; i++){     // goes through rows
      if (cur_game->cells[i * cur_game->cols + j] != -1){
        rowc = i;   // current row
        for (int k = 0; k < cur_game->rows; k++){
          if (cur_game->cells[k * cur_game->cols + j] == -1 && k < rowc){
   rowt = k;  // target row
            cur_game->cells[rowt * cur_game->cols + j] = cur_game->cells[rowc * cur_game->cols + j];    // target row value changed
            cur_game->cells[rowc * cur_game->cols + j] = -1;  //empty the current val (-1)
            moves++; //just confirms that we have made a move
 }
}
      }
    }
  }
  for (int j = 0; j < cur_game->cols; j++){
    for (int i = 1; i < cur_game-> rows; i++){
      if (cur_game->cells[i * cur_game->cols + j] != -1){ //while not empty
        rowa = i - 1;
        if (cur_game->cells[i * cur_game->cols + j] == cur_game->cells[rowa * cur_game->cols + j]){
 cur_game->cells[rowa * cur_game->cols + j] = cur_game->cells[rowa * cur_game->cols + j] * 2;   // merges cells
           cur_game->cells[i * cur_game->cols + j] = -1; //make the cell empty (-1)
           cur_game->score = cur_game->score + cur_game->cells[rowa * cur_game->cols + j]; // updates score
        }
      }
    }
  }
  for (int j = 0; j < cur_game->cols; j++){
    for (int i = 0; i < cur_game->rows; i++){
      if (cur_game->cells[i * cur_game->cols + j] != -1){
        rowc = i; //curr row
        for (int k = 0; k < cur_game->rows; k++){
          if (cur_game->cells[k * cur_game->cols + j] == -1 && k < rowc){
   rowt = k; //target row
            cur_game->cells[rowt * cur_game->cols + j] = cur_game->cells[rowc * cur_game->cols + j];
            cur_game->cells[rowc * cur_game->cols + j] = -1; //makes the current cell empty (-1)
            moves++;
 }
}
      }
    }
  }
  if (moves == 0)  // checks if any values are changed
    return 0;
  return 1;
};
int move_s(game * cur_game) //slide down, it works the same way as slide up.
{
    //YOUR CODE STARTS HERE
  int rowc = 0;
  int rowt = 0;
  int rowa = 0;
  int moves = 0;
  for (int j = 0; j < cur_game->cols; j++){     // goes through columns
    for (int i = cur_game->rows - 1; i >= 0; i--){    // goes through rows
      if (cur_game->cells[i * cur_game->cols + j] != -1){
        rowc = i;  // current row
        for (int k = cur_game->rows - 1; k >= 0; k--){
          if (cur_game->cells[k * cur_game->cols + j] == -1 && k > rowc){
   rowt = k;
            cur_game->cells[rowt * cur_game->cols + j] = cur_game->cells[rowc * cur_game->cols + j];
            cur_game->cells[rowc * cur_game->cols + j] = -1;
            moves++;
 }
}
      }
    }
  }
  for (int j = 0; j < cur_game->cols; j++){
    for (int i = cur_game->rows - 2; i >= 0; i--){
      if (cur_game->cells[i * cur_game->cols + j] != -1){
        rowa = i + 1;
        if (cur_game->cells[i * cur_game->cols + j] == cur_game->cells[rowa * cur_game->cols + j]){
           cur_game->cells[rowa * cur_game->cols + j] = cur_game->cells[rowa * cur_game->cols + j] * 2;
           cur_game->cells[i * cur_game->cols + j] = -1; //empty ceell
           cur_game->score = cur_game->score + cur_game->cells[rowa * cur_game->cols + j];
        }
      }
    }
  }
  for (int j = 0; j < cur_game->cols; j++){
    for (int i = cur_game->rows - 1; i >= 0; i--){
      if (cur_game->cells[i * cur_game->cols + j] != -1){
        rowc = i; //curr row
        for (int k = cur_game->rows - 1; k >= 0; k--){
          if (cur_game->cells[k * cur_game->cols + j] == -1 && k > rowc){
   rowt = k; //target row
            cur_game->cells[rowt * cur_game->cols + j] = cur_game->cells[rowc * cur_game->cols + j];
            cur_game->cells[rowc * cur_game->cols + j] = -1;
            moves++; // moves were made
 }
}
      }
    }
  }
  if (moves == 0)
    return 0;
  return 1;
};
int move_a(game * cur_game) //slide left, works similarly to slide up/down
{
  //YOUR CODE STARTS HERE
  int colc = 0;
  int colt = 0;
  int cola = 0;
  int moves = 0;
  for (int i = 0; i < cur_game->rows; i++){
    for (int j = 0; j < cur_game->cols; j++){
      if (cur_game->cells[i * cur_game->cols + j] != -1){
        colc = j;
        for (int k = 0; k < cur_game->cols; k++){
          if (cur_game->cells[i * cur_game->cols + k] == -1 && k < colc){
            colt = k;
            cur_game->cells[i * cur_game->cols + colt] = cur_game->cells[i * cur_game->cols + colc];
            cur_game->cells[i * cur_game->cols + colc] = -1;
            moves++; //moves were made
 }
}
      }
    }
  }
  for (int i = 0; i < cur_game->rows; i++){
    for (int j = 0; j < cur_game->cols; j++){
      if (cur_game->cells[i * cur_game->cols + j] != -1){
        cola = j - 1;
        if (cur_game->cells[i * cur_game->cols + j] == cur_game->cells[i * cur_game->cols + cola]){
          cur_game->cells[i * cur_game->cols + cola] = cur_game->cells[i * cur_game->cols + cola] * 2;
          cur_game->cells[i * cur_game->cols + j] = -1;
          cur_game->score = cur_game->score + cur_game->cells[i * cur_game->cols + cola];
}
      }
    }
  }
  for (int i = 0; i < cur_game->rows; i++){
    for (int j = 0; j < cur_game->cols; j++){
      if (cur_game->cells[i * cur_game->cols + j] != -1){
        colc = j;
        for (int k = 0; k < cur_game->cols; k++){
          if (cur_game->cells[i * cur_game->cols + k] == -1 && k < colc){
            colt = k;
            cur_game->cells[i * cur_game->cols + colt] = cur_game->cells[i * cur_game->cols + colc];
            cur_game->cells[i * cur_game->cols + colc] = -1;
            moves++; //move was made
 }
}
      }
    }
  }
  if (moves == 0) //if no moves were made, then we return 0
    return 0;
  return 1;
};
int move_d(game * cur_game){ //slide to the right, works similarly to slide left
  //YOUR CODE STARTS HERE
int colc = 0;
  int colt = 0;
  int cola = 0;
  int moves = 0;
  for (int i = 0; i < cur_game->rows; i++){
    for (int j = cur_game->cols - 1; j >= 0; j--){
      if (cur_game->cells[i * cur_game->cols + j] != -1){
        colc = j; //curr coloumns
        for (int k = cur_game->cols - 1; k >= 0; k--){
          if (cur_game->cells[i * cur_game->cols + k] == -1 && k > colc){
            colt = k; //target column
            cur_game->cells[i * cur_game->cols + colt] = cur_game->cells[i * cur_game->cols + colc];
            cur_game->cells[i * cur_game->cols + colc] = -1;
            moves++; //move was made
 }
}
      }
    }
  }
  for (int i = 0; i < cur_game->rows; i++){
    for (int j = cur_game->cols - 2; j >= 0; j--){
      if (cur_game->cells[i * cur_game->cols + j] != -1){
        cola = j + 1;
        if (cur_game->cells[i * cur_game->cols + j] == cur_game->cells[i * cur_game->cols + cola]){
          cur_game->cells[i * cur_game->cols + cola] = cur_game->cells[i * cur_game->cols + cola] * 2;
          cur_game->cells[i * cur_game->cols + j] = -1;
          cur_game->score = cur_game->score + cur_game->cells[i * cur_game->cols + cola];
}
      }
    }
  }
  for (int i = 0; i < cur_game->rows; i++){
    for (int j = cur_game->cols - 1; j >= 0; j--){
      if (cur_game->cells[i * cur_game->cols + j] != -1){
        colc = j; //curr column
        for (int k = cur_game->cols - 1; k >= 0; k--){
          if (cur_game->cells[i * cur_game->cols + k] == -1 && k > colc){
            colt = k; //target col
            cur_game->cells[i * cur_game->cols + colt] = cur_game->cells[i * cur_game->cols + colc];
            cur_game->cells[i * cur_game->cols + colc] = -1;
            moves++;
 }
}
      }
    }
  }
  if (moves == 0) //if the move was not made return 0
    return 0;
  return 1;
};
int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    //YOUR CODE STARTS HERE
   
  game *copyofgame = make_game(cur_game->rows, cur_game->cols); //making a copy to test on
int ret=0;
for (int i=0; i< ( (cur_game->rows) * (cur_game->cols)); i++)
copyofgame->cells[i] = cur_game->cells[i]; //initializing copy to the actual game
if (move_w(copyofgame) + move_s(copyofgame) + move_a(copyofgame) + move_d(copyofgame) !=0) //if the sum of the  moves is 1, then we return a 1
ret = 1;
return ret;
}
/*! code below is provided and should not be changed */
void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
cell * cell_ptr;
    cell_ptr = cur_game->cells;
    if (cell_ptr == NULL){
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
//check for an empty cell
int emptycheck = 0;
int i;
for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
if ((*cell_ptr) == -1){
emptycheck = 1;
break;
}
        cell_ptr += 1;
}
if (emptycheck == 0){
printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
exit(0);
}
    int ind,row,col;
int num;
    do{
ind = rand()%((cur_game->rows)*(cur_game->cols));
col = ind%(cur_game->cols);
row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
num = rand()%20;
if(num <= 1){
*get_cell(cur_game, row, col) = 4; // 1/10th chance
}
else{
*get_cell(cur_game, row, col) = 2;// 9/10th chance
}
}
int print_game(game * cur_game)
{
    cell * cell_ptr;
    cell_ptr = cur_game->cells;
    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
printf("\n\n\nscore:%d\n",cur_game->score);
printf("\u2554"); // topleft box char
for(i = 0; i < cols*5;i++)
printf("\u2550"); // top box char
printf("\u2557\n"); //top right char
    for(i = 0; i < rows; i++){
printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  ");
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
default:
printf("  X  ");
                }
            }
            cell_ptr++;
        }
printf("\u2551\n"); //print right wall and newline
    }
printf("\u255A"); // print bottom left char
for(i = 0; i < cols*5;i++)
printf("\u2550"); // bottom char
printf("\u255D\n"); //bottom right char
    return 0;
}
int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{
int rows,cols;
char buf[200];
char garbage[2];
    int move_success = 0;
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
case 'n':
//get row and col input for new game
dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
while (NULL == fgets(buf,200,stdin)) {
printf("\nProgram Terminated.\n");
return 0;
}
if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
rows < 0 || cols < 0){
printf("Invalid dimensions.\n");
goto dim_prompt;
}
remake_game(&cur_game,rows,cols);
move_success = 1;
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game);
print_game(cur_game);
    }
    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
