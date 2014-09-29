#include <stdio.h>
main( )
{
    int i = 0 , j = 1 ;
    while ( i<= 5 )
    {
  if(i==2) {
	i++;
	continue;
	}
//else
printf("i=%d\n",i);
i++;
    }
}

// continue means stop executing  for that value and take the execution to starting of the loop. 
///*
/*#include <stdio.h>
main( )
{
    int i = 0 , j = 1 ;
    for(i=0;i<10;i++)
    {
  if(i==8)
continue;
//else
printf("i=%d\n",i);

    }
}*/
//*/
// continue and break is usually asociated with a if loop.
// continue , once this satisfies dont execute further, instead take the control to the starting of the loop.
