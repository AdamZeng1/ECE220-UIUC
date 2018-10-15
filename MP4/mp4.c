//This program prints the semiprimes in a given range.
//It reads two inputs a, b, and then prints all the semiprimes in [a,b].
//A semiprime is a positive integer that is a product of two prime numbers.



//program starts here
#include <stdlib.h>
#include <stdio.h>


int is_prime(int number);
int print_semiprimes(int a, int b);


int main(){
   int a, b;
   printf("Input two numbers: ");
   scanf("%d %d", &a, &b);
   if( a <= 0 || b <= 0 ){
     printf("Inputs should be positive integers\n");
     return 1;
   }

   if( a > b ){
     printf("The first number should be smaller than or equal to the second number\n");
     return 1;
   }
   print_semiprimes(a, b);   //calls the print_semiprimes function to print semiprimes in [a,b] (including a and b)
   return 0;
}


/*
 * This function to check the number is prime or not.
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
    if (number == 2){
      return 1;
    }
    else{
      for (int i = 2; i < number; i++){
        if (number % i == 0){
          return 0;
        }
      }
      return 1;
    }
}


/*
 * This function prints all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
  int exist = 0;
  for(int n = a; n <= b; n++){
    int printed = 0;
    for(int k = 2; k < n; k++){
      {
        if ((n % k == 0) && (is_prime(k) + is_prime(n / k) == 2)){
          if (printed == 0){
            printf("%d ", n);
            printed = 1;
          }
        exist = 1;
        }
      }
    }
  }
  return exist;
}
