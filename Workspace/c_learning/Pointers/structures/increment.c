#include<stdio.h>

int main()
{	
	int write_pointer = 0;
	if(++write_pointer >= 2) {
		printf("write_pointer is dead \n");
	}
	printf("printing the write pointer = %d\n",write_pointer);
}

/*this way of increment shocked me, i thought it will not be incremented but to my shocking this was incremented,
the output was 1*/
