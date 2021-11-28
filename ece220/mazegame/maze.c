//partners: ronitk2, ddamani2

/* in this mp we shall attempt to solve a maze using recursive 
backtracking. by working on files, we shall attempt to 
show the solving of this maze. in our four functions, we shall
try to work on files by doing the basics of creating the maze
on the file, then destroying the maze on the file, printing the maze in a human readable format, and most importantly 
solving the maze in a way that uses depth-first-search
algorithm, where we move one cell at a time trying to reach
the end from start.
*/


#include <stdio.h>
#include <stdlib.h>
#include "maze.h"


/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
	int i, j; //loop variables
	int row,col;
	char c;
	FILE *fileread = fopen(fileName, "r");
	
	fscanf(fileread, "%d %d", &col, &row);
	maze_t *newmaze = malloc(sizeof(maze_t));
	newmaze->height = row;
	newmaze->width  = col;
	newmaze->cells = (char **)malloc(row*sizeof(char *));
	
	for (i = 0; i < row; i++){
      newmaze->cells[i] = (char *)malloc(col * sizeof(char));
    } //initialize the rows using malloc - automaticallly creates the columns too
	
	for ( i=0; i<row; i++)
	{
		for ( j=0; j<col; j++)
		{
		c=fgetc(fileread); //get the next character coming in
		if (c!='\n')
			newmaze->cells[i][j]=c; //new maze's value at row, col will get the character from file
		else
			j--;
			
		if (j>=0)
			{	
			if (newmaze->cells[i][j]==START)
				{ //if we are at the start
				newmaze->startRow=i; //assign start row/col the correct number
				newmaze->startColumn=j;
				}
			if (newmaze->cells[i][j]==END)
				{ //if we are at the end
				newmaze->endRow=i;//assign end row/col the correct number
				newmaze->endColumn=j;
				}
			}
		}
	}
	fclose(fileread); //close the file
	return newmaze;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
	int i; //loop variables
    for ( i=0; i< maze->height; i++)
    	free(maze->cells[i]); //free all the mallocs in createmaze
    	
    	free(maze->cells); //free the cells array
    	free(maze); //finally free the entire maze
    	maze=NULL; //make the maze pointer point to null
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
	int i, j; //loop variables
   // printf("%d %d\n", maze->width, maze->height); //prints size of maze
    for ( i=0; i<maze->height; i++) 
    {	//runs through rows
    	for ( j=0; j<maze->width;j++)
    	{ //runs through cols
    		printf("%c", maze->cells[i][j]); //printing each char
       	}
       	printf("\n"); //newline after each row.
    }
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{

     

    //1. if the maze cell is out of bounds:
    if (row<0 || maze->height<=row || col<0 || maze->width<=col)
    return 0;
    
    
    //2. if the maze cell is not an empty cell:
    if (maze->cells[row][col]==WALL || maze->cells[row][col]==VISITED || maze->cells[row][col]==PATH)
	return 0;

	//3. if end of the maze return true
    if (maze->endRow==row && maze->endColumn==col)
    	{
    	maze->cells[maze->startRow][maze->startColumn] = START;
    	//this puts us back on starting point so we dont lose the maze pointer
    	return 1;
	}

    //4. setting row and column as part of solution in the maze.
    if (maze-> cells[row][col]!=END)
   	 maze->cells[row][col]=PATH;
    
    //5. solving maze on left cell
    //for left we need to decrease our column by 1, keep row same
    if (solveMazeDFS(maze, col-1, row))
    	return 1;
    	
    //6. solving maze on right cell
    //for right we increase col by 1, same row
     if (solveMazeDFS(maze, col+1, row))
    	return 1;
    	
    //7. solving maze on up cell
    //for up we decrease row by 1, same col
     if (solveMazeDFS(maze, col, row-1))
    	return 1;
    	
    //8. solving maze on down cell
    //for down we increase row by 1, same col
     if (solveMazeDFS(maze, col, row+1))
    	return 1;
    	
    //9. unmark cell as solution, mark it as visited
    if (maze->cells[row][col]!=START && maze-> cells[row][col]!=END)
    maze->cells[row][col]=VISITED; //changed the char to '~'
    
    return 0; //return false
    	
    	
    
    
}   
    
    

