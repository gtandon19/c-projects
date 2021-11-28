#include <stdlib.h>
#include <stdio.h>
// No semicolon in line 26 of main.c - lines 26 and beyond don't run
// semiprime.c:
// return 1 in line 18 - declares "non-prime" numbers as "prime"
// return 0 in line 22 - declares "prime" numbers as "non-prime"
// is_prime(j) in line 41 - is_prime does not return boolean
// k=i%j in line 42 - k will always be 0 so it will never be prime
// is_prime(k) in line 43 - is_prime does not return boolean
// need to set ret=1 at line 47 if there is a semiprime number
// need to set j=i to exit loop to avoid printing same number more than once
/*
 * is_prime: determines whether the provided number is prime or not
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
    int i;
    if (number == 1) {return 0;}
    for (i = 2; i < number; i++) { //for each number smaller than it
        if (number % i == 0) { //check if the remainder is 0
            return 0;
        }
    }
    return 1;
}
/*
 * print_semiprimes: prints all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
    int i, j, k;
    int ret = 0;
    for (i = a; i <=b; i++) { //for each item in interval
        //check if semiprime
        for (j = 2; j < i; j++) {
            if (i%j == 0) {
                if (is_prime(j) == 1) {
                    k = i/j;
                    if (is_prime(k) == 1) {
                        printf("%d ", i);
ret = 1;
j = i;
                    }
                }
            }
        }
    }
    printf("\n");
    return ret;
}
