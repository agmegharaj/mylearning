#include<stdio.h>

main()
{
int a[5]={0,1,2,3,4},i=0,*j;

j=a;

while(i<5)
{
printf("addreess %u\n",&a[i]);
printf("value at adreess %d\n",*j);
i++;
j++;
}
}


