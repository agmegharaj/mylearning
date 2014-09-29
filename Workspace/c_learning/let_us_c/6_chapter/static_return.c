#include <stdio.h>

void fun(int *);

int main()
{
	int i = 23;
	fun(&i);
	printf("\n");
	printf(" i new value is %d\n",i);
	
}

void fun(int *j)
{
	printf("\n");
	printf(" j new value is %d\n",*j);
	*j = 334;
}	
