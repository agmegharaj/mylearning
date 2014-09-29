/*
#include <stdio.h>
main ( int argc, int *argv[] )
{
     int c,a,b;
a=argv[1];
b=argv[2];
c=a+b;
printf("c=%d\n",c);
}
*/


#include <stdio.h>
main ( int argc, int *argv[] )
{
     int c,a,b;
a=atoi(&argv[1]);
b=atoi(&argv[2]);
c=a+b;
printf("c=%d\n",c);
}


/* argv i mean argument received will be in string format. */
