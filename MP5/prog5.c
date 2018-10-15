/*
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


//Introductory paragraph:
//This program is a codebreaking game.
//The user first enters a seed value, which initializes a pseudo-random number generator.
//A solution code sequence of four numbers from 1 to 8 is chosen, and the player has 12 guesses to get the sequence.
//After each guess, the program gives feedback on the number of perfect matches and misplaced matches, and print them to the screen.
//This program uses arrays to conveniently compare the guess number and solutions,
//and uses pointers to connect the variables in subroutine with those in the main function



#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"


static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid.
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int
set_seed (const char seed_str[])
{

    int seed = 0;
    char post[2];
    int check = sscanf (seed_str, "%d%1s", &seed, post);
    if (check != 1){
      printf ("set_seed: invalid seed\n");
      return 0;
    }
    srand (seed);
    return 1;
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above.
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 * INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 1 and 8)
 *          *two -- the second solution value (between 1 and 8)
 *          *three -- the third solution value (between 1 and 8)
 *          *four -- the fourth solution value (between 1 and 8)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void
start_game (int* one, int* two, int* three, int* four)
{
    solution1 = rand() % 8 + 1;
    solution2 = rand() % 8 + 1;
    solution3 = rand() % 8 + 1;
    solution4 = rand() % 8 + 1;
    guess_number = 1;
    *one = solution1;
    *two = solution2;
    *three = solution3;
    *four = solution4;
}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str.
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 integers, within the range 1-8). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
 *          *one -- the first guess value (between 1 and 8)
 *          *two -- the second guess value (between 1 and 8)
 *          *three -- the third guess value (between 1 and 8)
 *          *four -- the fourth color value (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 1 and 8), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess)
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int make_guess (const char guess_str[], int* one, int* two,
	    int* three, int* four)
{
    int perfect = 0;
    int misplaced = 0;
    int i;
    char post [2];
    int solution[4];                                        //make an array of 4 solution numbers for future use
    solution[0] = solution1;
    solution[1] = solution2;
    solution[2] = solution3;
    solution[3] = solution4;
    int paired[8] = {0, 0, 0, 0, 0, 0, 0, 0};              //0-3 for solution numbers, 4-7 for guess numbers, 0 means not paired, 1 paired

    int check = sscanf (guess_str, "%d%d%d%d%1s", one, two, three, four, post);
    if (check != 4){
      printf("make_guess: invalid guess\n");
      return 0;
    }
    if (! (*one <= 8 && *one >= 1 && *two <= 8 && *two >= 1 && *three <= 8 && *three >= 1 && *four <= 8 && *four >= 1) ){
      printf("make_guess: invalid guess\n");
      return 0;
    }
//Check perfect matches
    if (solution1 == *one){
      perfect++;
      paired[0] = 1;
      paired[4] = 1;
    }
    if (solution2 == *two){
      perfect++;
      paired[1] = 1;
      paired[5] = 1;
    }
    if (solution3 == *three){
      perfect++;
      paired[2] = 1;
      paired[6] = 1;
    }
    if (solution4 == *four){
      perfect++;
      paired[3] = 1;
      paired[7] = 1;/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 */
    }

//check misplaced matches
    if (paired[4] == 0){
      for (i = 0; i <= 3; i++){
        if ((solution[i] == *one) && (paired[i] == 0)){
          misplaced++;
          paired[i] = 1;
          paired[4] = 1;
          i = i + 4;      //skip the rest
        }
      }
    }
    if (paired[5] == 0){
      for (i = 0; i <= 3; i++){
        if ((solution[i] == *two) && (paired[i] == 0)){
          misplaced++;
          paired[i] = 1;
          paired[5] = 1;
          i = i + 4;
        }
      }
    }
    if (paired[6] == 0){
      for (i = 0; i <= 3; i++){/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 */
        if ((solution[i] == *three) && (paired[i] == 0)){
          misplaced++;
          paired[i] = 1;
          paired[6] = 1;
          i = i + 4;
        }
      }
    }
    if (paired[7] == 0){
      for (i = 0; i <= 3; i++){
        if ((solution[i] == *four) && (paired[i] == 0)){
          misplaced++;
          paired[i] = 1;
          paired[7] = 1;
          i = i + 4;
        }
      }
    }
    printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n", guess_number, perfect, misplaced);
    guess_number++;
    return 1;
}
