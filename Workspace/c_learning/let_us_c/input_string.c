#include <stdio.h>
#include <string.h>
main( )
{
     FILE *fp ;
     char s[80] ;
                                          
  fp = fopen ( "4-7_1.txt", "w" ) ;

  printf ( "\nEnter a few lines of text:\n" ) ;
  while ( strlen ( gets ( s ) ) > 0 )
  {
         fputs ( s, fp ) ;
         fputs ( "\n", fp ) ;
  }
  fclose ( fp ) ;
}

