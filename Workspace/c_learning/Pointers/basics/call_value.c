#include<stdio.h>

swap(int,int);

main()
{
int a=20;
int b=30;

swap(a,b);

printf("a=%d\n",a);
printf("b=%d\n",b);

return 0;
}

swap(int x,int y)
{
int t;

t=x;
x=y;
y=t;

printf("a=%d\n",x);
printf("b=%d\n",y);

}

