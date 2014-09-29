#include <stdio.h>

main()
{

int a[5][2]={
 
{1,2},
{3,4},
{5,6},
{7,8},
{9,10}

};
int i,j;
for(i=0;i<5;i++)
{
printf("\n");

for(j=0;j<2;j++)

printf("\t%d",*(*(a+i)+j));
}
}
