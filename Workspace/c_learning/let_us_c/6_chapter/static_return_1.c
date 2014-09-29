#include <stdio.h>

int *fun();

void main()
{
	int *i;
	i = fun();
	printf("\n");
	printf(" i new value is %d\n",*i);
	
}

int *fun()
{
	int j = 23;
	return &j;
}	

/*to ask on stackoverflow*/
