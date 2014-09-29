#include <stdio.h>

main()
{
int i=3,*j;
j=&i;

printf("i=%d\n",i);
printf("i=%u\n",&i);
printf("i=%d\n",*(&i));
printf("i=%u\n",j);
printf("i=%d\n",*j);
}

