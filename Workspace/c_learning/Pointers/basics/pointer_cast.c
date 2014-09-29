#include <stdio.h>

main()
{
int i=54213;
float f=3.14;
char *ii,*ff;

ii= (char *) &i;
ff= (char *) &f;

printf(" addreess at ii %u\n", ii);
printf(" addreess at ff %u\n", ff);

printf(" value at ii %d\n", *ii);
printf(" value at ff %d\n", *ff);

}
 
// this one was to understand base address
