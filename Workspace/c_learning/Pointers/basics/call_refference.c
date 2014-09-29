#include<stdio.h>

swap(int*,int*);

main()
{
int a=20;
int b=30;

swap(&a,&b);

printf("a=%d\n",a);
printf("b=%d\n",b);

}

swap(int *a,int *b)
{
int t;

t=*a;
*a=*b;
*b=t;


}
