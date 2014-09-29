#include <stdio.h>
main( )
{
    char c ;
    unsigned char d ;
    int i ;
    unsigned int j ;
    short int k ;
    unsigned short int l ;
    long int m ;
    unsigned long int n ;
    float x ;
    double y ;
    long double z ;
    /* char */
printf("enter char\n");
    scanf ( "%c %c", &c, &d ) ;
    printf ( "%c %c", c, d ) ;
    /* int */
printf("enter int\n");
    scanf ( "%d %u", &i, &j ) ;
    printf ( "%d %u", i, j ) ;
    /* short int */

printf("enter short int\n");    
scanf ( "%d %u", &k, &l ) ;
    printf ( "%d %u", k, l ) ;
    /* long int */

printf("enter longint\n");    
scanf ( "%ld %lu", &m, &n ) ;
    printf ( "%ld %lu", m, n ) ;

    /* float, double, long double */

printf("enter float double long double\n");    
scanf ( "%f %lf %Lf", &x, &y, &z ) ;
    printf ( "%f %lf %Lf", x, y, z ) ;
}


/* for long int use %ld in the same way for double use %lf*/
