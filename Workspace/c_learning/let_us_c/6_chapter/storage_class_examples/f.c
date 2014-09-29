main( )
{
   int i, j ;
   for ( i = 1 ; i < 5 ; i++ )
   {
         j=g(i);
         printf ( "\n%d", j ) ;
   }
                                
}

   g ( int x )
   {
        static int v = 1 ;
        int b = 3 ;
        v += x ;
        return ( v + x + b ) ;//6(2),9(4),13(7),18 
   }

