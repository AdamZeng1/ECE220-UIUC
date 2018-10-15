#include "game.h"

//Introductory paragraph starts HERE!!!!!!!!!!

//The game begins with a random value tile of either 2 or 4 placed at a random location on the board
//The player controls the game using the directional keys w,a,s,d
//As they slide, if two numbers of the same value collide
//they merge into a single tile whose value is the sum of of the two values
//This program has 4 moving functions to 4 different directions
//It also checks if the game is over by trying to move the game in 4 directions
//Please read the codes in Atom! The format looks weird in other editors.



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
    int i = 0;

    for(i = 0; i <= ((rows * cols) - 1); i++){                //initialize every cell to -1
      *((*mygame).cells + i) = -1;
    }

    (*mygame).rows = rows;
    (*mygame).cols = cols;                                    //store rows and cols to mygame

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
   int i = 0;

   for(i = 0; i <= ((new_rows * new_cols) - 1); i++){         //reinitialize every cell to -1
     *((**_cur_game_ptr).cells + i) = -1;
   }

   (** _cur_game_ptr).rows = new_rows;                       //store new rows and cols to current game
   (** _cur_game_ptr).cols = new_cols;

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
    if(row < 0 || row >= (* cur_game).rows){
      return NULL;
    }
    if(col < 0 || col >= (* cur_game).cols){
      return NULL;
    }
    return (*cur_game).cells + row * (* cur_game).cols + col;
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


    int i = 0;
    int j = 0;
    int last_combined_row = -1;
    int target_row = -1;
    int targetfound = 0;
    int moved = 0;
    for(j = 0; j <= (*cur_game).cols - 1; j++){

      last_combined_row = -1;                              //reset last_combined_row

      for(i = 0; i <= (*cur_game).rows - 1; i++){

        if(*((*cur_game).cells + i * (* cur_game).cols + j) != -1){   //If the current row value is not empty

          targetfound = 0;                  //set initial value of targetfound to 0

          for(target_row = 0; target_row < i; target_row++){        //find target_row
            if(*((*cur_game).cells + target_row * (* cur_game).cols + j) == -1){
              targetfound = 1;
              break;
            }
          }

          if (targetfound == 1){
            *((*cur_game).cells + target_row * (* cur_game).cols + j) = *((*cur_game).cells + i * (* cur_game).cols + j);  //copy
            *((*cur_game).cells + i * (* cur_game).cols + j) = -1;  //clear current row contents
            moved = 1;
          }

          if ( (target_row - 1) != last_combined_row){
            //if same number
            if(*((*cur_game).cells + (target_row - 1) * (* cur_game).cols + j) == *((*cur_game).cells + target_row * (* cur_game).cols + j)){
              //row above target row value is assigned the sum
              *((*cur_game).cells + (target_row - 1) * (* cur_game).cols + j) *= 2;
              //add Score
              (* cur_game).score += *((*cur_game).cells + (target_row - 1) * (* cur_game).cols + j);
              //target row value is assigned as empty
              *((*cur_game).cells + target_row * (* cur_game).cols + j) = -1;
              //last_combined_row is assigned as row above target_row
              last_combined_row = target_row - 1;
              moved = 1;
            }
          }
        }
      }
    }

    return moved;
};

int move_s(game * cur_game) //slide down
{
    //YOUR CODE STARTS HERE
    int i = 0;
    int j = 0;
    int last_combined_row = -1;
    int target_row = -1;
    int targetfound = 0;
    int moved = 0;
    for(j = 0; j <= (*cur_game).cols - 1; j++){

      last_combined_row = -1;                              //reset last_combined_row

      for(i = (*cur_game).rows - 1; i >= 0 ; i--){

        if(*((*cur_game).cells + i * (* cur_game).cols + j) != -1){   //If the current row value is not empty

          targetfound = 0;

          for(target_row = (*cur_game).rows - 1; target_row > i; target_row--){        //find target_row
            if(*((*cur_game).cells + target_row * (* cur_game).cols + j) == -1){
              targetfound = 1;
              break;
            }
          }

          if (targetfound == 1){
            *((*cur_game).cells + target_row * (* cur_game).cols + j) = *((*cur_game).cells + i * (* cur_game).cols + j);  //copy
            *((*cur_game).cells + i * (* cur_game).cols + j) = -1;  //clear current row contents
            moved = 1;
          }

          if ( (target_row + 1) != last_combined_row){
            //if same number
            if(*((*cur_game).cells + (target_row + 1) * (* cur_game).cols + j) == *((*cur_game).cells + target_row * (* cur_game).cols + j)){
              //row below target row value is assigned the sum
              *((*cur_game).cells + (target_row + 1) * (* cur_game).cols + j) *= 2;
              //add Score
              (* cur_game).score += *((*cur_game).cells + (target_row + 1) * (* cur_game).cols + j);
              //target row value is assigned as empty
              *((*cur_game).cells + target_row * (* cur_game).cols + j) = -1;
              //last_combined_row is assigned as row below target_row
              last_combined_row = target_row + 1;
              moved = 1;
            }
          }
        }
      }
    }
    return moved;
};

int move_a(game * cur_game) //slide left
{
    //YOUR CODE STARTS HERE
    int i = 0;
    int j = 0;
    int last_combined_column = -1;
    int target_column = -1;
    int targetfound = 0;
    int moved = 0;
    for(i = 0; i <= (*cur_game).rows - 1; i++){

      last_combined_column = -1;                              //reset last_combined_column

      for(j = 0; j <= (*cur_game).cols - 1; j++){

        if(*((*cur_game).cells + i * (* cur_game).cols + j) != -1){   //If the current column value is not empty

          targetfound = 0;

          for(target_column = 0; target_column < j; target_column++){        //find target_column
            if(*((*cur_game).cells + i * (* cur_game).cols + target_column) == -1){
              targetfound = 1;
              break;
            }
          }

          if (targetfound == 1){
            *((*cur_game).cells + i * (* cur_game).cols + target_column) = *((*cur_game).cells + i * (* cur_game).cols + j);  //copy
            *((*cur_game).cells + i * (* cur_game).cols + j) = -1;  //clear current row contents
            moved = 1;
          }

          if ( (target_column - 1) != last_combined_column){
            //if same number
            if(*((*cur_game).cells + i * (* cur_game).cols + (target_column - 1)) == *((*cur_game).cells + i * (* cur_game).cols + target_column)){
              //column left to target column value is assigned the sum
              *((*cur_game).cells + i * (* cur_game).cols + (target_column - 1)) *= 2;
              //add Score
              (* cur_game).score += *((*cur_game).cells + i * (* cur_game).cols + (target_column - 1));
              //target column value is assigned as empty
              *((*cur_game).cells + i * (* cur_game).cols + target_column) = -1;
              //last_combined_column is assigned as row above target_row
              last_combined_column = target_column - 1;
              moved = 1;
            }
          }
        }
      }
    }
    return moved;
};

int move_d(game * cur_game){ //slide to the right
    //YOUR CODE STARTS HERE
    int i = 0;
    int j = 0;
    int last_combined_column = -1;
    int target_column = -1;
    int targetfound = 0;
    int moved = 0;
    for(i = 0; i <= (*cur_game).rows - 1; i++){

      last_combined_column = -1;                              //reset last_combined_column

      for(j = (*cur_game).cols - 1; j >= 0; j--){

        if(*((*cur_game).cells + i * (* cur_game).cols + j) != -1){   //If the current column value is not empty

          targetfound = 0;

          for(target_column = (*cur_game).cols - 1; target_column >= j; target_column--){        //find target_column
            if(*((*cur_game).cells + i * (* cur_game).cols + target_column) == -1){
              targetfound = 1;
              break;
            }
          }

          if (targetfound == 1){
            *((*cur_game).cells + i * (* cur_game).cols + target_column) = *((*cur_game).cells + i * (* cur_game).cols + j);  //copy
            *((*cur_game).cells + i * (* cur_game).cols + j) = -1;  //clear current row contents
            moved = 1;
          }

          if ( (target_column + 1) != last_combined_column){
            //if same number
            if(*((*cur_game).cells + i * (* cur_game).cols + (target_column + 1)) == *((*cur_game).cells + i * (* cur_game).cols + target_column)){
              //column right to target column value is assigned the sum
              *((*cur_game).cells + i * (* cur_game).cols + (target_column + 1)) *= 2;
              //add Score
              (* cur_game).score += *((*cur_game).cells + i * (* cur_game).cols + (target_column + 1));
              //target column value is assigned as empty
              *((*cur_game).cells + i * (* cur_game).cols + target_column) = -1;
              //last_combined_column is assigned as column above target_column
              last_combined_column = target_column + 1;
              moved = 1;
            }
          }
        }
      }
    }
    return moved;
};

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    //YOUR CODE STARTS HERE
    game * copy_game = make_game((*cur_game).rows,(*cur_game).cols); //make a copy game entity to test on
    int result = 0;
    int i;
    for (i = 0; i <= (((* cur_game).rows * (* cur_game).cols) - 1); i++){
      *((*copy_game).cells + i) = *((*cur_game).cells + i);
    }
    if((move_w(copy_game)+move_a(copy_game)+move_s(copy_game)+move_d(copy_game))!= 0){    //check if moving is possible
      result = 1;
    }
    return result;
}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{

	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

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
    cell_ptr = 	cur_game->cells;

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
