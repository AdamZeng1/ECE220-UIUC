//This program prints the Pascal's triangle
//Enter the row number as input,
//the program will output the numbers at that row
//Row number starts from 0

#include <stdio.h>

int main()
{
  unsigned long row;

  printf("Enter a row index: ");              //get input
  scanf("%lu",&row);

  // Write your code here
  unsigned long k;
  unsigned long i;
  unsigned long ans;                         //define variables needed
  for (k = 0; k <= row; k++)
    {
      ans = 1;                               //set the first number to be 1
    for (i = 1; i <= k; i++){
      ans = (ans * (row + 1 - i)) / i;
    }
    printf ("%lu ", ans);                    //output the number
    }


  return 0;
}
