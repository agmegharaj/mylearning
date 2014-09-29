main( )
{
   static int count = 5 ;
   printf ( "\ncount = %d", count-- ) ;// first it prints that value than it decrements
   //printf ( "\ncount = %d", --count ) ;// first it decrements that value than it prints
   if ( count != 0 )
         main( ) ;
}

