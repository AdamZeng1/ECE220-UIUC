


 //Introductory paragraph starts here
 //This program is the game of life
 //It uses a 1-D array to represent the game_board
 //The rule of this game is too long, so you can find it online
 //For every element of the board, this program first counts the numbers of live neighbors
 //and decide what it should be on the next step
 //before updating the board, it checks whether the board stays stable, and decide if it should end the program
 //it uses a new compareboard, updates it and compares it with the original board

 //VIEW THIS FILE IN Atom!! The format looks weird on subversion & texteditor



int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
	int livenum = 0;
	int i, j;
	for (i = row - 1; i <= row + 1; i++){																	//count 3 rows, 3 columns
		if ( (i >= 0) && (i <= boardRowSize - 1) ){													//9 elements in total
			for (j = col - 1; j <= col + 1; j++){
				if ( (j >= 0) && (j <= boardColSize - 1)){
					if (*(board + i * boardColSize + j) == 1){
						livenum++;
					}
				}
			}
		}
	}
	livenum = livenum - *(board + row * boardColSize + col);							//finally subtract the result with the analyzed element itself
	return livenum;
}



void updateBoard(int* board, int boardRowSize, int boardColSize) {
	int livenum = 0;
	int newboard[boardRowSize * boardColSize];														//a new board to store the updated result
	int i, j;
	for (i = 0; i <= boardRowSize - 1 ; i++){															//duplicate the original board to the new board
		for (j = 0; j <= boardColSize - 1; j++){
			newboard[i * boardColSize + j] = *(board + i * boardColSize + j);
		}
	}

	for (i = 0; i <= boardRowSize - 1; i++){
		for (j = 0; j <= boardColSize - 1; j++){
			livenum = countLiveNeighbor (board, boardRowSize, boardColSize, i, j);
			if ((livenum < 2) || (livenum > 3)){
				newboard[i * boardColSize + j] = 0;
			}
			if (livenum == 3){
				newboard[i * boardColSize + j] = 1;
			}
		}
	}


	for (i = 0; i <= boardRowSize - 1; i++){															//duplicate new board to original board to update
		for (j = 0; j <= boardColSize - 1; j++){
			*(board+ i * boardColSize + j) = newboard[i * boardColSize + j];
		}
	}
	return;
}


int aliveStable(int* board, int boardRowSize, int boardColSize){
	int alive = 1;
	int livenum = 0;
	int compareboard[boardRowSize * boardColSize];
	int i, j;
	for (i = 0; i <= boardRowSize - 1 ; i++){															//duplicate the original board to the new board
		for (j = 0; j <= boardColSize - 1; j++){
			compareboard[i * boardColSize + j] = *(board + i * boardColSize + j);
		}
	}

	for (i = 0; i <= boardRowSize - 1; i++){															//do the same thing again to get updated result in the new board
		for (j = 0; j <= boardColSize - 1; j++){
			livenum = countLiveNeighbor (board, boardRowSize, boardColSize, i, j);
			if (livenum < 2){
				compareboard[i * boardColSize + j] = 0;
			}
			if (livenum == 3){
				compareboard[i * boardColSize + j] = 1;
			}
			if (livenum > 3){
				compareboard[i * boardColSize + j] = 0;
			}
		}
	}



	for (i = 0; i <= boardRowSize - 1; i++){																								//compare the new board with old board
		for (j = 0; j <= boardColSize - 1; j++){
			if (compareboard[i * boardColSize + j] != *(board + i * boardColSize + j) ){				//if there is one element different, return alive = 0
				alive = 0;
			}
		}
	}
	return alive;
}
