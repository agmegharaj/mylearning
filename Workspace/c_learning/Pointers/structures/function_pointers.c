#include<stdio.h>

int square(int n) {
  return n*n;
}


int main()
{
int square(int);
int (*pf)(int);
pf = square;   // pf now points to the f() function
int i = square(4); // call f() using the function name
printf("i = %d\n",i);
int j = (*pf)(5); // call f() using the pointer pf
printf("i = %d\n",j);
int k = pf(6); // also call f() using the pointer pf
printf("i = %d\n",k);
}
