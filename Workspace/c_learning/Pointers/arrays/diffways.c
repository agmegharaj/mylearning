#include<stdio.h>

display(int *,int);
 
main()
{
int a[5]={0,1,2,3,4};
int n=5;
display(a,n);

}

display(int *j,int n)
{
int i=0;
while(i<n)
{

printf(" address of of element = %u\t",j);
printf(" value of element of of element = %d\n",*j);
i++;
j++;
}
}
