#include <stdio.h>
int *fun();

main()
{
 int *p;
p=fun();
printf(" hi world \n");
// this is just super even when function returns address it will be on stack so it displays the value ,
// by adding another printf function stack changes now it prints garbage values
printf(" value at address is =%d\n",*p);
}

int *fun()
{
 static int i=20;
return (&i);
}
