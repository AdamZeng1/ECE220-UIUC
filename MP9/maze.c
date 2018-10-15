#include <stdio.h>
#include <stdlib.h>
#include "maze.h"


//introductory paragraph starts here
//This program is a maze solver using a recursive depth-first search,
//as well as a couple of functions that can be used to verify a correct solution.
//The first two numbers in the output are the width and height of the maze,
//followed by the structure of the maze.
//‘%’ represent walls within the maze while a space represents an empty cell.
//‘S’ indicates the start of the maze and ‘E’ indicates the end of the maze.
//Please read the program in Atom, or the format might look weird in other editors.






maze_t * createMaze(char * fileName)
{
    int i, j, rows, cols;
    char c;
    FILE *reader = fopen(fileName, "r");                                    //create a stream

    fscanf(reader, "%d %d", &cols, &rows);
    maze_t *mazecreated = malloc(sizeof(maze_t));                           //allocate memory for the maze_t structure
    mazecreated -> height = rows;
    mazecreated -> width = cols;
    mazecreated -> cells = (char **)malloc(rows * sizeof(char *));          //allocate memory for the cells
    for (i = 0; i < rows; i++){
      mazecreated -> cells[i] = (char *)malloc(cols * sizeof(char));
    }
    for (i = 0; i < rows; i++){
      for (j = 0; j < cols; j++){
        c = fgetc(reader);                                                  //duplcate the maze in the file
        if (c != '\n'){
          mazecreated -> cells[i][j] = c;
        }
        else{                                                               //if it's a newline character
            j--;                                                            //do not save, and loop once more
        }
        if (j >= 0){                                                        //without this line there will be an error accessing cells[i][-1]
          if (mazecreated -> cells[i][j] == START){                         //record the start point
            mazecreated -> startRow = i;
            mazecreated -> startColumn = j;
          }
          if (mazecreated -> cells[i][j] == END){                           //record the end point
            mazecreated -> endRow = i;
            mazecreated -> endColumn = j;
          }
        }
      }
    }
    fclose(reader);                                                         //close the stream

    return mazecreated;
}





void destroyMaze(maze_t * maze)
{
    int i;
    for (i = 0; i < maze -> height; i++){
      free(maze -> cells[i]);                               //simply free all the mallocs used in createMaze
    }
    free(maze -> cells);
    free(maze);
    maze = NULL;
}




void printMaze(maze_t * maze)
{
    int i, j;
    printf("%d %d\n", maze -> width, maze -> height);
    for (i = 0; i < maze -> height; i++){
      for (j = 0; j < maze -> width; j++){
        printf("%c", maze -> cells[i][j]);
      }
      printf("\n");                                         //print a newline after each row
    }
}




int solveMazeManhattanDFS(maze_t * maze, int col, int row)
{

    //false if out of bounds
    if (col < 0 || col >= maze -> width || row < 0 || row >= maze -> height){
      return 0;
    }

    //false if not an empty cell
    if (maze -> cells[row][col] == WALL || maze -> cells[row][col] == PATH || maze -> cells[row][col] == VISITED){
      return 0;
    }

    //true if reach the end
    if (col == maze -> endColumn && row == maze -> endRow){
      //restore the starting point before reaching the end (VERY IMPORTANT!!!)
      maze -> cells[maze -> startRow][maze -> startColumn] = START;
      return 1;
    }

    //set (col, row) as part of the solution path in the maze
    if (maze -> cells[row][col] != END){          //this part writes PATH at starting point, but will be restored at last
      maze -> cells[row][col] = PATH;
    }

    //true if left (or other direction) true
    if (solveMazeManhattanDFS(maze, col - 1, row)){
      return 1;
    }
    if (solveMazeManhattanDFS(maze, col, row - 1)){
      return 1;
    }
    if (solveMazeManhattanDFS(maze, col + 1, row)){
      return 1;
    }
    if (solveMazeManhattanDFS(maze, col, row + 1)){
      return 1;
    }
    //unmark (col, row) as part of solution and mark as visited
    if (maze -> cells[row][col] != START && maze -> cells[row][col] != END){
      maze -> cells[row][col] = VISITED;
    }

    return 0;
}
