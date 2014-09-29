#include <stdio.h>
//float x = 4.5 ;

main( )
{
const float x=4.5;
    float y=10; 
const float *b;
b=&x;
//&x=&y;
//*b=10;
    printf ( "\n%f %f\n", x, *b ) ;
}


