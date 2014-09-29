#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BITS_IN_BYTE 8
#define INTEGRAL_TYPE unsigned int

void showbits(INTEGRAL_TYPE x) {
    int i,andmask = 0,k = 0;;
    static int intSizeInBits = sizeof(INTEGRAL_TYPE) * BITS_IN_BYTE;


    for (i=intSizeInBits; i >=0; i--) {
    	andmask = 1<<i;
	k = x & andmask;
	k = 0 ? printf("0") : printf("1");
    }

}

int main ()
{
	int j = 0, k = 0;
	for(j=0;j<5;j++) {
		printf("the deimal value of %d is same as bits as\n ",j);
		showbits(j);
		/*k = ~j;
		printf("the deimal value of %d is same as bits as ",k);
		showbits(k);*/
	}
return 0;
}
