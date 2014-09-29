#include <stdio.h>
int i ;
main( )
{
      printf ( "\ni = %d", i ) ;
      increment( ) ;
      increment( ) ;
      decrement( ) ;
      decrement( ) ;
}
increment( )
{
      i=i+1;
      printf ( "\non incrementing i = %d", i ) ;
}
decrement( )
{
      i=i-1;
      printf ( "\non decrementing i = %d", i ) ;
}

