#include <stdio.h>
main( )
{
    static int i = 1 ;

    {
                                 
       static int i = 2 ;
       {
             static int i = 3 ;
             printf ( "\n%d ", i ) ;
       }
       printf ( "%d ", i ) ;
  }
  printf ( "%d", i ) ;
}
