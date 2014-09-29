#include<stdio.h>
#define INT 1
#define FLOAT 2

void absolute_value ( void *j, int *n)
{
	if ( *n == INT) {
		if ( *((int*)j) < 0 )
			*((int*)j) = *((int*)j) * (-1);
	}
	if ( *n == FLOAT ) {
		if ( *((float*)j) < 0 )
			*((float*)j) = *((float*)j) * (-1);
	}
}


int main()
{
	int i = 0,n=0;
	float f = 0;
	printf("Press 1 to enter integer or 2 got float then enter the value to get absolute value\n");
	scanf("%d",&n);
	printf("\n");
	if( n == 1) {
		scanf("%d",&i);
		printf("value entered before absolute function exec = %d \n",i);
		absolute_value(&i,&n);
		printf("value entered after absolute function exec = %d \n",i);
	}
	else if( n == 2) {
		scanf("%f",&f);
		printf("value entered before absolute function exec = %f \n",f);
		absolute_value(&f,&n);
		printf("value entered after absolute function exec = %f \n",f);
	}
	else
	printf("unknown entry try again\n");
	return 0;
}
