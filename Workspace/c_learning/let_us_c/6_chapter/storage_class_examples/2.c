#include <stdio.h>
//float x = 4.5 ;
float f(float *);
main( )
{
const float x=4.5;
    float y; 
    //x *= 2.0 ;//9
    //y=f(&x);
y=f(&x);
    printf ( "\n%f %f\n", x, y ) ;
}

float f ( float *a )
{
      
    *a=10;
printf(" in function %f\n",*a);
return *a;
}



