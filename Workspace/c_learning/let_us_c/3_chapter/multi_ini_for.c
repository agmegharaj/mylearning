/*#include <stdio.h>
main()
{
int i,j,k;

for(i=0,j=0,k=0;j<10 || i<6 ||k<5;i++,j++,k++)

printf("i=%d\n j=%d\n k=%d\n",i,j,k);
}*/
// in the above code instead of three condition I have made it one condition, even this can be made.

#include <stdio.h>
main()
{
int i,j,k;

for(i=0,j=0,k=0;j<10,i<6,k<5;i++,j++,k++)

printf("i=%d\n j=%d\n k=%d\n",i,j,k);
}



// we can use as many initializations and comparisions and increments but even one breaks the condition the loop will come out
