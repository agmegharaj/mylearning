main( )
{
   int i, j, k ;
   for ( i = 1 ; i <= 3 ; i++ )
   {
         for ( j = 1 ; j <= 3 ; j++ )
         {
               for ( k = 1 ; k <= 3 ; k++ )
               {
                     if ( i == 1 && j == 2 && k == 1 )
                            goto out ;
                     else
                            printf ( "%d %d %d\n", i, j, k ) ;
               }
         }
   }
   out :
         printf ( "Out of the loop at last!" ) ;
	printf("totally came out of everything\n");
}

// if used goto it comes out of the loop and doesent returns back, it starts executing further.

