/*#include <stdio.h>
main( )
{
    int i = 0 , j = 1 ;
    while ( i++<= 5 )
    {
  if(i==2)
break;
else
printf("i=%d\n",i);

    }
}
*/
// break not only breaks the if loop but the entire while loop. Break is often used with if loop/

#include <stdio.h>
main( )
{
	int i = 0 , j = 1 ;
	    for(i=0;i<10;i++)
	    {
	    if(i==8)
	    break;
	else
	printf("i=%d\n",i);

    }
}

// break not only breaks the if loop but the entire while loop. Break is often used with if loop/
// break means come out of the for loop and while loop.
